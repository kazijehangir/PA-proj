#include "llvm/ADT/StringRef.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/InstrTypes.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Verifier.h"
#include "llvm/Pass.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Transforms/IPO/PassManagerBuilder.h"

#include <map>
#include <queue>
#include <string>
#include <unordered_set>

using namespace llvm;

namespace {
struct MarkSweepPass : public FunctionPass {
  static char ID;
  std::map<std::string, int> counts;

  MarkSweepPass() : FunctionPass(ID) {}

  StringRef getPassName() { return "MarkSweepPass"; }

  virtual bool runOnFunction(Function& F) {
    F.dump();
    auto workList = std::queue<Instruction*>();
    auto marked = std::unordered_set<Instruction*>();
    // Initialize work list with critical instructions.
    for (auto& B : F) {
      for (auto& I : B) {
        StoreInst* store_inst = dyn_cast<StoreInst>(&I);
        ReturnInst* return_inst = dyn_cast<ReturnInst>(&I);
        if ((I.mayHaveSideEffects() &&  !store_inst) || return_inst) {
        	marked.insert(&I);
        	workList.push(&I);
        }
      }
    }
    errs() << "\nInitialization done.\n";

    // Perform Mark phase.
    while (!workList.empty()) {
      Instruction* currInst = workList.front();
      workList.pop();
      // currInst->dump();
      // errs() << "inst\n";
      for (auto* d : getDefiningOfOps(currInst)) {
        auto search = marked.find(d);
        if (search == marked.end()) {
          // d->dump();
          marked.insert(d);
          workList.push(d);
        }
      }

      for (auto* b : getRDF(currInst->getParent())) {
        auto* term = b->getTerminator();
        if (term) {
          Instruction* lastInst = dyn_cast<Instruction>(term);
          auto search = marked.find(lastInst);
          if (search == marked.end()) {
            marked.insert(lastInst);
            workList.push(lastInst);
          }
        }
      }
      // errs() << "\n";
    }
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
    errs() << "Mark phase done.\n";

    // Perform the Sweep phase.
    auto dead = std::unordered_set<Instruction*>();
    for (auto& B : F) {
      for (auto& I : B) {
        auto search = marked.find(&I);
        if (search == marked.end()) {
          //errs() << "Found unmarked (noncritical) inst: " << I.getOpcodeName() << "\n";
          // I.dump();
          TerminatorInst* termin_inst = dyn_cast<TerminatorInst>(&I);
          CallInst* call_inst = dyn_cast<CallInst>(&I);
          if (termin_inst) {

          } else if (!call_inst) {
            dead.insert(&I);
          }
        }
      }
    }

    //remove dead instructions
    errs() << "Removing these instructions:\n";
    for (auto* I : dead) {
      // if (!(I->getType()->isVoidTy())){
      //   I->replaceAllUsesWith(Constant::getNullValue(I->getType()));
      // }
      // I->dump();
      // I->eraseFromParent();
    }
    errs() << "Sweep phase done.\n\n";

    // F.dump();
    return true;
  }

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

  std::vector<BasicBlock*> getRDF(BasicBlock* b) {
    // std::vector<BasicBlock*> rdf;
    // rdf.push_back(b);
    // return rdf;
    std::map<BasicBlock*,std::vector<BasicBlock*> > rdf;
    rdf[b].push_back(b);
    return rdf[b];
  }
};
}  // namespace

char MarkSweepPass::ID = 0;
static RegisterPass<MarkSweepPass> X("markSweep", "Dead Code Elimination",
                                     false, false);