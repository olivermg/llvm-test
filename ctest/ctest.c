#include <llvm-c/Core.h>

int main(int argc, char* argv[]) {
	LLVMContextRef context = LLVMGetGlobalContext();
	LLVMModuleRef module = LLVMModuleCreateWithNameInContext("mytop", context);
	LLVMBuilderRef builder = LLVMCreateBuilderInContext(context);

	// get some types:
	LLVMTypeRef i8Type = LLVMInt8TypeInContext(context);
	LLVMTypeRef i8PtrType = LLVMPointerType(i8Type, 0);
	LLVMTypeRef i32Type = LLVMInt32TypeInContext(context);

	// declare puts:
	LLVMTypeRef putsParams[] = { i8PtrType };
	LLVMTypeRef putsFuncType = LLVMFunctionType(i32Type, putsParams, 1, 0);
	LLVMValueRef putsFunc = LLVMAddFunction(module, "puts", putsFuncType);

	// define myadd:
	LLVMTypeRef addParams[] = { i32Type, i32Type };
	LLVMTypeRef addFuncType = LLVMFunctionType(i32Type, addParams, 2, 0);
	LLVMValueRef addFunc = LLVMAddFunction(module, "myadd", addFuncType);
	LLVMBasicBlockRef addEntry = LLVMAppendBasicBlockInContext(context, addFunc, "myentry");
	LLVMPositionBuilderAtEnd(builder, addEntry);
	LLVMValueRef addParam0 = LLVMGetParam(addFunc, 0);
	LLVMValueRef addParam1 = LLVMGetParam(addFunc, 1);
	LLVMValueRef sum = LLVMBuildAdd(builder, addParam0, addParam1, "");
	LLVMBuildRet(builder, sum);

	// define main:
	LLVMTypeRef mainFuncType = LLVMFunctionType(i32Type, 0, 0, 0);
	LLVMValueRef mainFunc = LLVMAddFunction(module, "main", mainFuncType);

	LLVMBasicBlockRef mainEntry = LLVMAppendBasicBlockInContext(context, mainFunc, "myentry");
	LLVMPositionBuilderAtEnd(builder, mainEntry);

	// define global vars:
	LLVMValueRef helloWorld = LLVMBuildGlobalStringPtr(builder, "hello world in c!\n", "");

	// call puts:
	LLVMValueRef putsArgs[] = { helloWorld };
	LLVMValueRef putsResult = LLVMBuildCall(builder, putsFunc, putsArgs, 1, "");

	// call myadd:
	LLVMValueRef addArg0 = LLVMConstInt(i32Type, 34, 0);
	LLVMValueRef addArg1 = LLVMConstInt(i32Type, 11, 0);
	LLVMValueRef addArgs[] = { addArg0, addArg1 };
	LLVMValueRef addResult = LLVMBuildCall(builder, addFunc, addArgs, 2, "");

	LLVMValueRef retVoid = LLVMBuildRet(builder, addResult);

	LLVMDumpModule(module);

	return 0;
}

