#include <llvm/LLVMContext.h>
#include <llvm/Module.h>
#include <llvm/IRBuilder.h>

int main(int argc, char* argv[]) {
	llvm::LLVMContext& context = llvm::getGlobalContext();
	llvm::Module* module = new llvm::Module("topmodule", context);
	llvm::IRBuilder<> builder(context);

	// declare puts:
	std::vector<llvm::Type*> putsArgs;
	putsArgs.push_back(builder.getInt8Ty()->getPointerTo());
	llvm::ArrayRef<llvm::Type*> argsRef(putsArgs);

	llvm::FunctionType *putsType = llvm::FunctionType::get(builder.getInt32Ty(), argsRef, false);
	llvm::Constant *putsFunc = module->getOrInsertFunction("puts", putsType);

	// define main:
	llvm::FunctionType *funcType = llvm::FunctionType::get(builder.getInt32Ty(), false);
	llvm::Function *mainFunc = llvm::Function::Create(funcType, llvm::Function::ExternalLinkage, "main", module);

	llvm::BasicBlock* entry = llvm::BasicBlock::Create(context, "entrypoint", mainFunc);
	builder.SetInsertPoint(entry);
	llvm::Value *helloWorld = builder.CreateGlobalStringPtr("hello world!\n");

	builder.CreateCall(putsFunc, helloWorld);

	builder.CreateRetVoid();

	module->dump();

	return 0;
}

