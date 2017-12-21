#include "llvm/ADT/StringRef.h"
#include "llvm/IR/Function.h"
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
    // Initialize work list with critical instructions.
    for (auto& B : F) {
      for (auto& I : B) {
        if (I.mayHaveSideEffects()) {
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
          marked.insert(d);
          workList.push(d);
        }
      }
      for (auto* b : getRDF(currInst->getParent())) {
        auto* term = b->getTerminator();
        if (term) {
          Instruction* lastInst = dyn_cast<Instruction>(term);
          marked.insert(lastInst);
          workList.push(lastInst);
        }
      }
    }
    // Perform the Sweep phase.
    for (auto& B : F) {
      for (auto& I : B) {
        auto search = marked.find(&I);
        if (search == marked.end()) {
          errs() << "found unmarked inst\n";
        }
      }
    }
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
    std::vector<BasicBlock*> rdf;
    rdf.push_back(b);
    return rdf;
  }
};
}  // namespace

char MarkSweepPass::ID = 0;
static RegisterPass<MarkSweepPass> X("markSweep", "Count Static Instructions",
                                     false, false);