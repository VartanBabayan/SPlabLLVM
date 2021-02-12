#include "llvm/Pass.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Function.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/Instruction.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/Support/raw_ostream.h"

#include "llvm/IR/IRBuilder.h"

using namespace llvm;

namespace {
	
struct ir_instrumentation : public ModulePass 
{
    static char ID;

    Function *monitor;

    ir_instrumentation() : ModulePass(ID) {}

    virtual bool runOnModule(Module &M)
    {
	int counter = 0;

        errs() << "Inside Module " << M.getName() << "\n";

        for(Module::iterator F = M.begin(); F != M.end(); ++F)
        {
            errs() << "Hello from: " << F->getName() << ".\n";
            
	    if(F->getName() == "printf")
	    {
                monitor = cast<Function>(F);
                continue;
            }

            for(Function::iterator BB = F->begin(); BB != F->end(); ++BB)
            {
                for(BasicBlock::iterator BI = BB->begin(); BI != BB->end(); ++BI)
                {
                        errs() << "found a brach instruction!\n";
                        
			// const reference to an array
			ArrayRef< Value* > arguments(ConstantInt::get(Type::getInt32Ty(M.getContext()), counter, true));

			++counter;

                        Instruction *newInst = CallInst::Create(cast<Function>(F), arguments, "");

		    	BB->getInstList().insert(BI, newInst); 
                        
		    	errs() << "Inserted the function!\n";
		    	break;
                }
		errs() << "\n";
		break;
            }
        }
	
	// errs() << "invoked printf in " << counter << " functions \n"; 
        return true;
    }
};

}

char ir_instrumentation::ID = 0;
static RegisterPass<ir_instrumentation> X("ir-instrumentation", "LLVM IR Instrumentation Pass");
