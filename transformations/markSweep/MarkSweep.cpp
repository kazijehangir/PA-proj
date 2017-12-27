#include "llvm/ADT/StringRef.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/InstrTypes.h"
#include "llvm/IR/Instruction.h"
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
    // errs() << "Initialization done.\n";

    // Perform Mark phase.
    while (!workList.empty()) {
      Instruction* currInst = workList.front();
      // errs() << "Evaluating instruction: " << currInst->getOpcodeName() << "\n";
      workList.pop();
      // errs() << "Worklist size: " << workList.size() << "\n";
      for (auto* d : getDefiningOfOps(currInst)) {
        auto search = marked.find(d);
        if (search == marked.end()) {
          usefulBlocks.insert(d->getParent());          
          marked.insert(d);
          workList.push(d);
        }
      }
      // errs() << "Added defining instructions for operands.\n";
      // errs() << "Worklist size: " << workList.size() << "\n";

      for (auto* b : getRDF(currInst->getParent())) {
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
      // errs() << "Added term inst from parent rdf BB.\n";
      // errs() << "Worklist size: " << workList.size() << "\n";
    }
    // errs() << "Mark phase done.\n";

    // Perform the Sweep phase.
    for (auto& B : F) {
      for (auto& I : B) {
        auto search = marked.find(&I);
        if (search == marked.end()) {
          if (!removeInst(&I)) {
            errs() << "Failed to remove instruction.\n";
          }
        }
      }
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

  // NOTE: We only need to properly implement the functions below.

  // Returns true if instruction was successfully removed.
  bool removeInst(Instruction* I) {
    errs() << "found unmarked (noncritical) inst\n";
    errs() << "instruction: " << I->getOpcodeName() << "\n";
    return true;
  }

  bool isCritical(Instruction* I) {
    return I->mayHaveSideEffects();
  }

  std::vector<BasicBlock*> getRDF(BasicBlock* b) {
    std::vector<BasicBlock*> rdf;
    rdf.push_back(b);
    return rdf;
  }

};
}  // namespace

char MarkSweepPass::ID = 0;
static RegisterPass<MarkSweepPass> X("markSweep", "Count Static Instructions",
                                     false, false);