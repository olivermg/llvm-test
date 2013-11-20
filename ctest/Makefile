CC = clang
CXX = clang++
LLVMCFG = llvm-config
CFLAGS = -Wall -I`$(LLVMCFG) --includedir` `$(LLVMCFG) --cflags`
CXXFLAGS = -Wall -I`$(LLVMCFG) --includedir` `$(LLVMCFG) --cxxflags`
LDFLAGS = -Wall -L`$(LLVMCFG) --libdir` `$(LLVMCFG) --ldflags --libs`

test: test.o
	$(CXX) test.o -o test $(LDFLAGS)

test.o: test.cc
	$(CXX) -c test.cc -o test.o $(CXXFLAGS)

clean:
	rm -rvf test.o test

