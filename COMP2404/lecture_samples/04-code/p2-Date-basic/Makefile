p2:	main.o Date.o
	g++ -o p2 main.o Date.o

main.o:	main.cc Date.h
	g++ -c main.cc

Date.o:	Date.cc Date.h
	g++ -c Date.cc

clean:
	rm -f *.o p2
