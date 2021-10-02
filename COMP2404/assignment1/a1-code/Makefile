a1: Student.o Room.o Date.o Reservation.o Library.o Main.o
	g++ -o a1 *.o

Student.o:
	g++ -c Student.cc

Room.o:
	g++ -c Room.cc

Date.o:
	g++ -c Date.cc

Reservation.o:
	g++ -c Reservation.cc

Library.o:
	g++ -c Library.cc

Main.o:
	g++ -c main.cc

debug:
	g++ -g -c Student.cc;
	g++ -g -c Room.cc;
	g++ -g -c Date.cc;
	g++ -g -c Reservation.cc;
	g++ -g -c Library.cc;
	g++ -g -c main.cc;
	g++ -g -o a1 *.o

clean:
	rm -f *.o a1