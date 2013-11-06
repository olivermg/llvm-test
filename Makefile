LLI = lli
LLC = llc
AS = llvm-as

run: test.ll
	$(LLI) test.ll

compile: test.ll
	$(AS) test.ll

clean:
	rm -vf test.bc

