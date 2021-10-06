objects = main.o TestView.o TestControl.o Client.o Network.o Subscriber.o Podcast.o Episode.o PodArray.o

a2: $(objects)
	g++ -o a2 $(objects)

main.o: main.cc TestControl.o
	g++ -c main.cc 

TestView.o: TestView.h TestView.cc TestControl.o

TestControl.o: TestControl.h TestControl.cc Network.o
	g++ -c TestControl.cc

Client.o: Client.h Client.cc Network.o
	g++ -c Client.cc

Network.o: Network.h Network.cc PodArray.o
	g++ -c Network.cc

Subscriber.o: Subscriber.h Subscriber.cc
	g++ -c Subscriber.cc

PodArray.o: PodArray.cc PodArray.h Podcast.o
	g++ -c PodArray.cc

Podcast.o: Podcast.cc Podcast.h Episode.h
	g++ -c Podcast.cc
	
Episode.o: Episode.cc Episode.h Podcast.h
	g++ -c Episode.cc

clean:
	rm -f a2 *.o	

