CC = clang
CXX = clang++
LLVMCFG = llvm-config-3.2
OPT = opt-3.2
CFLAGS = -Wall `$(LLVMCFG) --cflags`
LDFLAGS = -Wall `$(LLVMCFG) --ldflags --libs core`



all: main


main: main.o
	$(CXX) main.o -o main $(LDFLAGS)

main.o: main.c
	$(CC) -c main.c -o main.o $(CFLAGS)


out.ll: main
	./main >out.ll 2>&1


opt-phi: out.ll
	$(OPT) -S -mem2reg <out.ll >out-opt-mem2reg.ll

opt-cfg: out.ll
	$(OPT) -S -simplifycfg <out.ll >out-opt-simplifycfg.ll

opt-o1: out.ll
	$(OPT) -S -O1 <out.ll >out-opt-o1.ll


clean:
	rm -rvf main.o main out*.ll

