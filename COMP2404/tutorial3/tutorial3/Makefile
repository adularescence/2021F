all: test1 test2

test1: test1.cc Room.o
	g++ -o test1 test1.cc Room.o
	
Room.o: Room.h Room.cc
	g++ -c Room.cc

test2: test2.cc Date.o
	g++ -o test2 test2.cc Date.o

Date.o:	Date.h Date.cc
	g++ -c Date.cc
	
clean:
	rm -f test1 test2 *.o
