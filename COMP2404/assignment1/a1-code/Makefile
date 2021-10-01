all: Student.o Room.o Date.o Reservation.o Library.o main.o a1

a1: main.o
	g++ -o a1 main.o Student.o Room.o Date.o Reservation.o Library.o -g

Student.o:
	g++ -c Student.cc -g

Room.o:
	g++ -c Room.cc -g

Date.o:
	g++ -c Date.cc -g

Reservation.o:
	g++ -c Reservation.cc -g

Library.o:
	g++ -c Library.cc -g

Main.o:
	g++ -c main.cc -g

clean:
	rm -f *.o a1