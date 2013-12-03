#include <llvm-c/Core.h>

LLVMValueRef print(LLVMBuilderRef builder, LLVMValueRef printfRef, LLVMValueRef formatStringRef, LLVMValueRef value) {
	LLVMValueRef printfArgs[] = { formatStringRef, value };
	LLVMValueRef result = LLVMBuildCall(builder, printfRef, printfArgs, 2, "");

	return result;
}

int main(int argc, char* argv[]) {
	LLVMContextRef context = LLVMGetGlobalContext();
	LLVMModuleRef module = LLVMModuleCreateWithNameInContext("mytop", context);
	LLVMBuilderRef builder = LLVMCreateBuilderInContext(context);

	// get some types:
	LLVMTypeRef i8Type = LLVMInt8TypeInContext(context);
	LLVMTypeRef i8PtrType = LLVMPointerType(i8Type, 0);
	LLVMTypeRef i32Type = LLVMInt32TypeInContext(context);
	LLVMTypeRef i32PtrType = LLVMPointerType(i32Type, 0);

	// declare puts:
	LLVMTypeRef putsParams[] = { i8PtrType };
	LLVMTypeRef putsFuncType = LLVMFunctionType(i32Type, putsParams, 1, 0);
	LLVMValueRef putsFunc = LLVMAddFunction(module, "puts", putsFuncType);

	// declare printf:
	LLVMTypeRef printfParams[] = { i8PtrType, i32Type };
	LLVMTypeRef printfFuncType = LLVMFunctionType(i32Type, printfParams, 2, 0);
	LLVMValueRef printfFunc = LLVMAddFunction(module, "printf", printfFuncType);

	// define some aggregate types:
	//LLVMTypeRef struct1Type = LLVMStructTypeInContext(context, struct1Types, 2, 0);
	LLVMTypeRef struct1Types[] = { i8Type, i8PtrType };
	LLVMTypeRef struct1Type = LLVMStructCreateNamed(context, "struct1Type");
	LLVMStructSetBody(struct1Type, struct1Types, 2, 0);

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

	// define mystructfunc:
	LLVMTypeRef structFuncParams[] = { struct1Type };
	LLVMTypeRef structFuncType = LLVMFunctionType(i32Type, structFuncParams, 1, 0);
	LLVMValueRef structFunc = LLVMAddFunction(module, "mystructfunc", structFuncType);
	LLVMBasicBlockRef structFuncEntry = LLVMAppendBasicBlockInContext(context, structFunc, "myentry");
	LLVMPositionBuilderAtEnd(builder, structFuncEntry);
	LLVMValueRef structFuncParam0 = LLVMGetParam(structFunc, 0);
	LLVMValueRef value2p_8 = LLVMBuildExtractValue(builder, structFuncParam0, 1, "");
	LLVMValueRef value2p_32 = LLVMBuildPointerCast(builder, value2p_8, i32PtrType, "");
	LLVMValueRef value2_32 = LLVMBuildLoad(builder, value2p_32, "");
	LLVMBuildRet(builder, value2_32);

	// define main:
	LLVMTypeRef mainFuncType = LLVMFunctionType(i32Type, 0, 0, 0);
	LLVMValueRef mainFunc = LLVMAddFunction(module, "main", mainFuncType);

	LLVMBasicBlockRef mainEntry = LLVMAppendBasicBlockInContext(context, mainFunc, "myentry");
	LLVMPositionBuilderAtEnd(builder, mainEntry);

	// define global vars:
	LLVMValueRef helloWorld = LLVMBuildGlobalStringPtr(builder, "hello world in c!\n", "");
	LLVMValueRef formatString = LLVMBuildGlobalStringPtr(builder, "=> %d\n", "");

	// call puts:
	LLVMValueRef putsArgs[] = { helloWorld };
	LLVMValueRef putsResult = LLVMBuildCall(builder, putsFunc, putsArgs, 1, "");

	// call myadd:
	LLVMValueRef addArg0 = LLVMConstInt(i32Type, 34, 0);
	LLVMValueRef addArg1 = LLVMConstInt(i32Type, 11, 0);
	LLVMValueRef addArgs[] = { addArg0, addArg1 };
	LLVMValueRef addResult = LLVMBuildCall(builder, addFunc, addArgs, 2, "");

	// call mystructfunc:
	LLVMValueRef struct1Value1 = LLVMConstInt(i8Type, 34, 0);
	LLVMValueRef struct1Value2 = LLVMConstInt(i32Type, 1337, 0);
	LLVMValueRef struct1Value2p32 = LLVMAddGlobal(module, i32Type, "");
	LLVMSetInitializer(struct1Value2p32, struct1Value2);
	LLVMValueRef struct1Value2p8 = LLVMBuildPointerCast(builder, struct1Value2p32, i8PtrType, "");
	//LLVMValueRef struct1Value2idxs[] = { 0 };
	//LLVMValueRef struct1Value2p32 = LLVMBuildGEP(builder, struct1Value2, struct1Value2idxs, 1, "");
	LLVMValueRef struct1Values[] = { struct1Value1, struct1Value2p8 };
	LLVMValueRef struct1 = LLVMConstNamedStruct(struct1Type, struct1Values, 2);
	LLVMValueRef struct1Args[] = { struct1 };
	LLVMValueRef struct1FuncResult = LLVMBuildCall(builder, structFunc, struct1Args, 1, "");

	print(builder, printfFunc, formatString, struct1FuncResult);

	LLVMValueRef retVoid = LLVMBuildRet(builder, struct1FuncResult);

	LLVMDumpModule(module);

	return 0;
}

