#include <llvm/LLVMContext.h>
#include <llvm/Module.h>
#include <llvm/IRBuilder.h>

int main(int argc, char* argv[]) {
	llvm::LLVMContext& context = llvm::getGlobalContext();
	llvm::Module* module = new llvm::Module("topmodule", context);
	llvm::IRBuilder<> builder(context);

	module->dump();

	return 0;
}

