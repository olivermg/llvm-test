LLI = lli
LLC = llc
LLAS = llvm-as
AS = as
CC = clang



test: test.o
	$(CC) -v -Wall test.o -o test

test.bc: test.ll
	$(LLAS) test.ll

test.s: test.ll
	$(LLC) test.ll

test.o: test.s
	$(AS) -o test.o test.s



run: run-bin

run-bin: test
	./test

run-ll: test.ll
	$(LLI) test.ll

run-bc: test.bc
	$(LLI) test.bc



clean:
	rm -vf test.bc test.o test.s test
	rm -vf testc.s



compilec: testc.c
	$(CC) -S -emit-llvm testc.c

runc: compilec
	$(LLI) testc.s

