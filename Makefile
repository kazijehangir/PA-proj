CC=clang
CFLAGS=-Xclang -load

all: clean build

clean:
	rm -f transformations/build/CMakeCache.txt

build: transformations/markSweep/MarkSweep.cpp
	cd transformations/build && cmake .. && make &&  cd ../.. 
	clang -O0 -emit-llvm sourcecode/part1.c -c -o sourcecode/part1.bc
	cat texts/markSweep.txt
	opt -load transformations/build/markSweep/libMarkSweepPass.so -markSweep < sourcecode/part1.bc > /dev/null
	cat texts/partEnd.txt

part1: transformations/countStatic/CountStaticInstructions.cpp
	cd transformations/build && cmake .. && make &&  cd ../.. 
	clang -O3 -emit-llvm sourcecode/part1.c -c -o sourcecode/part1.bc
	cat texts/part1.txt
	opt -load transformations/build/countStatic/libCountStaticPass.so -countStatic < sourcecode/part1.bc > /dev/null
	cat texts/partEnd.txt

part2: transformations/countDynamic/CountDynamicInstructions.cpp
	cd transformations/build && cmake .. && make &&  cd ../.. 
	clang -O3 -emit-llvm sourcecode/compression.c -c -o sourcecode/compression.bc
	clang -O3 -emit-llvm -std=c++11 transformations/countDynamic/rtlib.cpp -c -o transformations/countDynamic/rtlib.bc
	opt -load transformations/build/countDynamic/libCountDynamicPass.so -countDynamic < sourcecode/compression.bc > sourcecode/compression.1.bc 
	llvm-link transformations/countDynamic/rtlib.bc sourcecode/compression.1.bc -o sourcecode/compression.linked.bc
	llc -o sourcecode/compression.o -filetype=obj sourcecode/compression.linked.bc 
	clang++ -std=c++11 sourcecode/compression.o -o sourcecode/compression.a.out

	cat texts/part2.txt
	./sourcecode/compression.a.out
	cat texts/partEnd.txt

