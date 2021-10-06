
#ifndef PODARRAY_H
#define PODARRAY_H

#include <iostream>
#include <string>
#include <iomanip>
#include "Podcast.h"
#include "defs.h"

using namespace std;

class PodArray {
		
	public:
		//constructor
		PodArray();
		//copy constructor
		PodArray(PodArray&);
		
		//destructor
		~PodArray();
		
		//other
		bool addPodcast(Podcast*);
		bool getPodcast(const string& title, Podcast**);
		bool removePodcast(const string& title, Podcast**);
		int size();
		bool isFull();
		void print();
	
	private:
		int numPods;
		Podcast** podcasts;
};
#endif
