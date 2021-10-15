#observe - Linux is case sensitive. These names should match your filenames exactly

all: test
	
test: test.o Episode.o Podcast.o 
	g++ -o test test.o Episode.o Podcast.o 
	
test.o: test.cc Episode.h Podcast.h
	g++ -c test.cc
	
Podcast.o:	Podcast.h Podcast.cc 
	g++ -c Podcast.cc 

Episode.o:	Episode.h Episode.cc
	g++ -c Episode.cc
	
clean:
	rm -f test *.o
