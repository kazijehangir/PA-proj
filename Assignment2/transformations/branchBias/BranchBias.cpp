#include "llvm/IR/Function.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Pass.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Transforms/IPO/PassManagerBuilder.h"
using namespace llvm;

namespace {
struct BranchBiasPass : public FunctionPass {
  static char ID;
  BranchBiasPass() : FunctionPass(ID) {}

  virtual bool runOnFunction(Function &F) {
    errs() << "I saw a function called " << F.getName() << "!\n";
    return false;
  }
};
}

char BranchBiasPass::ID = 0;

// Automatically enable the pass.
// http://adriansampson.net/blog/clangpass.html
static void registerBranchBiasPass(const PassManagerBuilder &,
                                   legacy::PassManagerBase &PM) {
  PM.add(new BranchBiasPass());
}
static RegisterStandardPasses RegisterMyPass(
    PassManagerBuilder::EP_EarlyAsPossible, registerBranchBiasPass);
