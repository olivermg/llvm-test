#include <stdio.h>
#include <llvm-c/Core.h>

int main( int argc, char* argv[] )
{
	LLVMContextRef context = LLVMGetGlobalContext();
	LLVMModuleRef module = LLVMModuleCreateWithNameInContext( "mytop", context );
	LLVMBuilderRef builder = LLVMCreateBuilderInContext( context );

	LLVMTypeRef mainFnReturnType = LLVMInt64TypeInContext( context );
	LLVMValueRef mainFn = LLVMAddFunction( module, "main", LLVMFunctionType( mainFnReturnType, NULL, 0, 0 ) );

	LLVMTypeRef recstruct = LLVMStructCreateNamed( context, "struct._recstruct_t" );
	LLVMTypeRef recstruct_p = LLVMPointerType( recstruct, 0 );
	LLVMTypeRef recstructTypes[] = { recstruct_p, LLVMInt64TypeInContext( context ) };
	LLVMStructSetBody( recstruct, recstructTypes, 2, 0 );

	LLVMBasicBlockRef entryblock = LLVMAppendBasicBlockInContext( context, mainFn, "entry" );
	LLVMPositionBuilderAtEnd( builder, entryblock );

	LLVMValueRef s1 = LLVMBuildAlloca( builder, recstruct, "s1" );
	LLVMValueRef s1_myp_gep = LLVMBuildStructGEP( builder, s1, 0, "s1_myp_gep" );
	LLVMValueRef s1_myint_gep = LLVMBuildStructGEP( builder, s1, 1, "s1_myint_gep" );
	LLVMValueRef myp = LLVMConstPointerNull( recstruct_p );
	LLVMValueRef myint = LLVMConstInt( LLVMInt64TypeInContext( context ), 555, 0 );
	LLVMBuildStore( builder, myp, s1_myp_gep );
	LLVMBuildStore( builder, myint, s1_myint_gep );

	LLVMValueRef s1_myint = LLVMBuildLoad( builder, s1_myint_gep, "s1_myint" );

	LLVMBuildRet( builder, s1_myint );

	LLVMDumpModule( module );
}

