#include <map>
#include <string>
#include "llvm/ADT/StringRef.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/InstrTypes.h"
#include "llvm/IR/Instruction.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Verifier.h"
#include "llvm/Pass.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Transforms/IPO/PassManagerBuilder.h"
#include "llvm/Transforms/Utils/BasicBlockUtils.h"

using namespace llvm;

namespace {
struct CountDynamicPass : public ModulePass {
  static char ID;

  CountDynamicPass() : ModulePass(ID) {}

  StringRef getPassName() { return "CountDynamicPass"; }

  virtual bool runOnModule(Module &M) {
    // Get the function to call from our runtime library.
    LLVMContext &Ctx = M.getContext();
    Constant *logFunc = M.getOrInsertFunction(
        "_Z9logCountsi", Type::getVoidTy(Ctx), Type::getInt32Ty(Ctx), NULL);
    Constant *printCounts = M.getOrInsertFunction(
        "_Z11printCountsi", Type::getVoidTy(Ctx), Type::getInt32Ty(Ctx), NULL);
    int phiOp = 49;

    for (auto &F : M) {
      if (std::string(F.getName()) == "logCounts") {
        continue;
      }
      // errs() << "inserting calls in func " << std::string(F.getName()) <<
      // "\n";
      for (auto &B : F) {
        int phis = 0;
        for (auto &I : B) {
          if (std::string(I.getOpcodeName()) == "phi") {
            phis++;
          } else {
            // Insert before instruction.
            IRBuilder<> builder(&I);
            builder.SetInsertPoint(&B, builder.GetInsertPoint());
            auto *opcode = builder.getInt32(I.getOpcode());

            // Insert a call to our function.
            Value *args[] = {opcode};
            builder.CreateCall(logFunc, args);
            while (phis > 0) {
              // errs() << "Adding phi\n";
              auto *opcode = builder.getInt32(phiOp);
              // Insert a call to our function.
              Value *args[] = {opcode};
              builder.CreateCall(logFunc, args);
              phis--;
            }
          }

          // Check if instruction is return stmt in main.
          if (std::string(F.getName()) == "main" &&
              std::string(I.getOpcodeName()) == "ret") {
            errs() << "Calling print function"
                   << "\n";
            // Insert before instruction.
            IRBuilder<> builder(&I);
            builder.SetInsertPoint(&B, builder.GetInsertPoint());
            auto *opcode = builder.getInt32(I.getOpcode());

            // Insert a call to our function.
            Value *args[] = {opcode};
            builder.CreateCall(printCounts, args);
          }
        }
      }
    }
    return true;
  }
};  // namespace
}  // namespace

char CountDynamicPass::ID = 0;
static RegisterPass<CountDynamicPass> X("countDynamic",
                                        "Count Dynamic Instructions", false,
                                        false);