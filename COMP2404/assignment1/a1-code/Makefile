all: Student.o Room.o Date.o Reservation.o

Student.o: Student.h Student.cc
	g++ -c Student.cc

Room.o: Room.h Room.cc
	g++ -c Room.cc

Date.o: Date.h Date.cc
	g++ -c Date.cc

Reservation.o: Reservation.h Reservation.cc
	g++ -c Reservation.cc

clean:
	rm -f Student.o Room.o Date.o Reservation.o