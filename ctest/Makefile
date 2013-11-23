CC = clang
CXX = clang++
LLVMCFG = llvm-config
CFLAGS = -Wall `$(LLVMCFG) --cflags`
CXXFLAGS = -Wall `$(LLVMCFG) --cxxflags`
LDFLAGS = -Wall `$(LLVMCFG) --ldflags --libs`



all: test ctest



test: test.o
	$(CXX) test.o -o test $(LDFLAGS)

test.o: test.cc
	$(CXX) -c test.cc -o test.o $(CXXFLAGS)



ctest: ctest.o
	$(CXX) ctest.o -o ctest $(LDFLAGS)

ctest.o: ctest.c
	$(CC) -c ctest.c -o ctest.o $(CFLAGS)



clean:
	rm -rvf test.o test ctest.o ctest

