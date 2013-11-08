LLI = lli
LLC = llc
AS = llvm-as
CC = clang

run: test.ll
	$(LLI) test.ll

runc: compilec
	$(LLI) testc.s

compile: test.ll
	$(AS) test.ll

compilec: testc.c
	$(CC) -S -emit-llvm testc.c

clean:
	rm -vf test.bc testc.s

