LLI = lli
LLC = llc
AS = llvm-as
CC = clang



run-bin: test
	./test

run-ll: test.ll
	$(LLI) test.ll

run-bc: test.bc
	$(LLI) test.bc

test.bc: test.ll
	$(AS) test.ll

test.o: test.ll
	$(LLC) -filetype=obj test.ll

test.s: test.ll
	$(LLC) test.ll

test: test.o
	$(CC) -Wall test.o -o test



clean:
	rm -vf test.bc test.o test.s test
	rm -vf testc.s



compilec: testc.c
	$(CC) -S -emit-llvm testc.c

runc: compilec
	$(LLI) testc.s

