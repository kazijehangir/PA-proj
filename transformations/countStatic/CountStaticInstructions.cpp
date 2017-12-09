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
#include <string>

using namespace llvm;

namespace {
struct CountStaticPass : public ModulePass {
  static char ID;
  std::map<std::string, int> counts;

  CountStaticPass() : ModulePass(ID) {}

  StringRef getPassName() { return "CountStaticPass"; }

  virtual bool runOnModule(Module &M) {
    for (auto &F : M) {
      for (auto &B : F) {
        for (auto &I : B) {
          counts[std::string(I.getOpcodeName())]++;
        }
      }
    }
    int total = 0;
    errs() << "Instruction counts:\n";
    for (const auto &op : counts) {
      total += op.second;
      errs() << op.first << " " << op.second << "\n";
    }
    errs() << "TOTAL " << total << "\n";
    return false;
  }
};
}

char CountStaticPass::ID = 0;
static RegisterPass<CountStaticPass> X("countStatic",
                                       "Count Static Instructions", false,
                                       false);