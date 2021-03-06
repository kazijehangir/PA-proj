#include "llvm/ADT/StringRef.h"
#include "llvm/Analysis/PostDominators.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/InstrTypes.h"
#include "llvm/IR/Instruction.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Verifier.h"
#include "llvm/Pass.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Transforms/IPO/PassManagerBuilder.h"

#include <map>
#include <queue>
#include <stack>
#include <string>
#include <unordered_set>

using namespace llvm;

namespace {
struct MarkSweepPass : public FunctionPass {
  static char ID;
  std::map<std::string, int> counts;

  MarkSweepPass() : FunctionPass(ID) {}

  StringRef getPassName() { return "MarkSweepPass"; }

  virtual void getAnalysisUsage(AnalysisUsage& AU) const override {
    FunctionPass::getAnalysisUsage(AU);
    AU.addRequired<PostDominatorTreeWrapperPass>();
  }

  virtual bool runOnFunction(Function& F) {
    F.dump();
    PostDominatorTree& tree =
        getAnalysis<PostDominatorTreeWrapperPass>().getPostDomTree();
    std::vector<BasicBlock*> bb_list;
    for (auto& B : F) {
      bb_list.push_back(&B);
    }

    // Construct Immediate Post Dominator & Post Doinator trees.
    std::map<BasicBlock*, BasicBlock*> ipdom;
    std::map<BasicBlock*, std::vector<BasicBlock*> > pdomi;
    for (int i = 0; i < bb_list.size(); i++) {
      for (int j = 0; j < bb_list.size(); j++) {
        if (tree.properlyDominates(bb_list[i], bb_list[j])) {
          ipdom[bb_list[j]] = bb_list[i];
          pdomi[bb_list[i]].push_back(bb_list[j]);
        }
      }
    }

    auto workList = std::queue<Instruction*>();
    auto marked = std::unordered_set<Instruction*>();
    auto usefulBlocks = std::unordered_set<BasicBlock*>();

    // Initialize work list with critical instructions.
    for (auto& B : F) {
      for (auto& I : B) {
        if (isCritical(&I)) {
          usefulBlocks.insert(&B);
          marked.insert(&I);
          workList.push(&I);
        }
      }
    }

    // Perform Mark phase.
    while (!workList.empty()) {
      Instruction* currInst = workList.front();
      workList.pop();
      for (auto* d : getDefiningOfOps(currInst)) {
        auto search = marked.find(d);
        if (search == marked.end()) {
          usefulBlocks.insert(d->getParent());
          marked.insert(d);
          workList.push(d);
        }
      }

      for (auto* b : getRDF(currInst->getParent(), ipdom, pdomi)) {
        auto* term = b->getTerminator();
        if (term) {
          Instruction* lastInst = dyn_cast<Instruction>(term);
          auto search = marked.find(lastInst);
          if (search == marked.end()) {
            usefulBlocks.insert(lastInst->getParent());
            marked.insert(lastInst);
            workList.push(lastInst);
          }
        }
      }
    }

    // Mark store instructions whose allocate instructions are already marked
    // critical as critical as well.
    for (auto& B : F) {
      for (auto& I : B) {
        auto search = marked.find(&I);
        StoreInst* store_inst = dyn_cast<StoreInst>(&I);
        if (store_inst && search == marked.end()) {
          for (auto* d : getDefiningOfOps(&I)) {
            auto search = marked.find(d);
            AllocaInst* alloca_inst = dyn_cast<AllocaInst>(d);
            if (alloca_inst && search != marked.end()) {
              marked.insert(&I);
            }
          }
        }
      }
    }
    // errs() << "Mark phase done.\n";

    // Perform the Sweep phase.
    auto dead = std::unordered_set<Instruction*>();
    for (auto& B : F) {
      for (auto& I : B) {
        auto search = marked.find(&I);
        if (search == marked.end()) {
          TerminatorInst* termin_inst = dyn_cast<TerminatorInst>(&I);
          CallInst* call_inst = dyn_cast<CallInst>(&I);
          // Check if the instruction is a branch instruction.
          if (termin_inst) {
            // Ignore jumps.
            if (termin_inst->getNumSuccessors() > 1) {
              if (!addCallToNearestPDom(termin_inst, usefulBlocks, pdomi)) {
                errs() << "Failed to create branch instruction.\n";
              }
              dead.insert(&I);
            }
          } else if (!call_inst) {
            dead.insert(&I);
          }
        }
      }
    }

    // remove dead instructions
    errs() << "Removing these instructions:\n";
    for (auto* I : dead) {
      if (!(I->getType()->isVoidTy())) {
        I->replaceAllUsesWith(Constant::getNullValue(I->getType()));
      }
      I->dump();
      I->eraseFromParent();
    }
    // errs() << "Sweep phase done.\n";
    errs() << "Dead Code Elimination completed using Mark Sweep algorithm.\n";
    return true;
  }

  // Returns a vector of instructions where the operands of the argument
  // where defined.
  std::vector<Instruction*> getDefiningOfOps(Instruction* currInst) {
    std::vector<Instruction*> def;
    for (int i = 0; i < currInst->getNumOperands(); i++) {
      auto* val = currInst->getOperand(i);
      Instruction* inst = dyn_cast<Instruction>(val);
      if (inst) {
        def.push_back(inst);
      }
    }
    return def;
  }

  bool addCallToNearestPDom(
      Instruction* I, std::unordered_set<BasicBlock*>& usefulBlocks,
      std::map<BasicBlock*, std::vector<BasicBlock*> >& pdomi) {
    for (auto* bb : pdomi[I->getParent()]) {
      auto search = usefulBlocks.find(bb);
      if (!(search == usefulBlocks.end())) {
        auto* resBI = BranchInst::Create(bb, I->getParent());
        if (resBI) {
          return true;
        } else {
          return false;
        }
      }
    }
    return false;
  }

  // NOTE: We only need to properly implement the functions below.

  bool isCritical(Instruction* I) {
    StoreInst* store_inst = dyn_cast<StoreInst>(I);
    ReturnInst* return_inst = dyn_cast<ReturnInst>(I);
    return (I->mayHaveSideEffects() && !store_inst) || return_inst;
  }

  std::vector<BasicBlock*> getRDF(
      BasicBlock* b, std::map<BasicBlock*, BasicBlock*> ipdom,
      std::map<BasicBlock*, std::vector<BasicBlock*> > pdomi) {
    std::map<BasicBlock*, std::vector<BasicBlock*> > rdf;
    auto visited = std::unordered_set<BasicBlock*>();
    std::stack<BasicBlock*> workListCurr;
    std::stack<BasicBlock*> workListPrev;

    workListCurr.push(b);
    workListPrev.push(b);

    BasicBlock *currB, *prevB;
    bool visitedPDom;
    while (!workListCurr.empty()) {
      currB = workListCurr.top();
      prevB = workListPrev.top();
      workListCurr.pop();
      workListPrev.pop();

      auto search = visited.find(currB);
      if (search == visited.end()) {
        visited.insert(currB);
        for (BasicBlock* p : predecessors(currB)) {
          if (ipdom[p] != currB) {
            rdf[b].push_back(p);
          }
        }
      }

      visitedPDom = false;
      for (int i = 0; i < pdomi[currB].size(); i++) {
        auto search = visited.find(pdomi[currB][i]);
        if (search == visited.end()) {
          workListCurr.push(pdomi[currB][i]);
          workListPrev.push(currB);
          visitedPDom = true;
        }
      }

      if (!visitedPDom) {
        if (currB == prevB) {
          break;
        }
        for (int i = 0; i < rdf[currB].size(); i++) {
          // is this fine?
          if (ipdom[prevB] != rdf[currB][i]) {
            rdf[prevB].push_back(rdf[currB][i]);
            workListCurr.pop();
            workListPrev.pop();
          }
        }
      }
    }
    return rdf[b];
  }
};
}  // namespace

char MarkSweepPass::ID = 0;
static RegisterPass<MarkSweepPass> X("markSweep",
                                     "Dead Code Elimination using Mark Sweep",
                                     false, false);