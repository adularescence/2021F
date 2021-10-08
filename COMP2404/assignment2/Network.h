#ifndef NETWORK_H
#define NETWORK_H

#include <string>

#include "PodArray.h"
#include "Subscriber.h"

class Network {
    public:
        Network(std::string& name);
        ~Network();

        // get
        bool getPodcast(std::string& podcastTitle, Podcast** pod);
        bool getSubscriber(std::string& name, Subscriber** sub);

        // add, remove
        bool addPodcast(std::string& podcastTitle, std::string& podcastHost);
        bool removePodcast(std::string& podcastTitle);
        bool addEpisode(std::string& podcastTitle, std::string& episodeName, std::string& content);
        bool addSubscriber(std::string& name, std::string& creditcard);

        // Client services
        bool download(std::string& subscriberName, std::string& podcastTitle, Podcast** pod);
        bool stream(std::string& subscriberName, std::string& podcastTitle, int& episodeNum, Episode** ep);

        // other?
        bool hasSubscriber(std::string& name);
        void print();


    private:
        std::string name;
        PodArray* podArray;
        Subscriber* subscribers[MAX_SUBS];
        int numSubs;
};

#endif