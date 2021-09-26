all: p1 battle.o Character.o

p1: main.o
	g++ -o p1 main.o Character.o battle.o

main.o: Character.o battle.o
	g++ -c main.cc

Character.o: Character.h Character.cc
	g++ -c Character.cc

battle.o: battle.h battle.cc
	g++ -c battle.cc

clean:
	rm -f p1 Character.o battle.o main.o