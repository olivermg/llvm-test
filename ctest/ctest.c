#include <llvm-c/Core.h>

int main(int argc, char* argv[]) {
	LLVMContextRef context = LLVMGetGlobalContext();
	LLVMModuleRef module = LLVMModuleCreateWithNameInContext("mytop", context);
	LLVMBuilderRef builder = LLVMCreateBuilderInContext(context);

	// declare puts:
	LLVMTypeRef i8Type = LLVMInt8TypeInContext(context);
	LLVMTypeRef i8PtrType = LLVMPointerType(i8Type, 0);
	LLVMTypeRef putsParams[] = { i8PtrType };
	LLVMTypeRef i32Type = LLVMInt32TypeInContext(context);
	LLVMTypeRef putsFuncType = LLVMFunctionType(i32Type, putsParams, 1, 0);
	LLVMValueRef putsFunc = LLVMAddFunction(module, "puts", putsFuncType);

	// define main:
	LLVMTypeRef mainFuncType = LLVMFunctionType(i32Type, 0, 0, 0);
	LLVMValueRef mainFunc = LLVMAddFunction(module, "main", mainFuncType);

	LLVMBasicBlockRef mainEntry = LLVMAppendBasicBlockInContext(context, mainFunc, "myentry");
	LLVMPositionBuilderAtEnd(builder, mainEntry);
	LLVMValueRef helloWorld = LLVMBuildGlobalStringPtr(builder, "hello world in c!\n", "");

	LLVMValueRef putsArgs[] = { helloWorld };
	LLVMValueRef putsCall = LLVMBuildCall(builder, putsFunc, putsArgs, 1, "");

	LLVMValueRef retVoid = LLVMBuildRetVoid(builder);

	LLVMDumpModule(module);

	return 0;
}

