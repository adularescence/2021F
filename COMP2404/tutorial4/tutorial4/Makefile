all: test
	
test: test.cc Episode.o HeapArrays.o StackArrays.o
	g++ -o test test.cc Episode.o HeapArrays.o StackArrays.o -g
	
StackArrays.o:	StackArrays.h StackArrays.cc 
	g++ -c StackArrays.cc  -g
	
HeapArrays.o:	HeapArrays.h HeapArrays.cc 
	g++ -c HeapArrays.cc -g

Episode.o:	Episode.h Episode.cc
	g++ -c Episode.cc -g
	
clean:
	rm -f test *.o
