#ifndef NETWORK_H
#define NETWORK_H

#include <string>

#include "PodArray.h"
#include "Subscriber.h"

class Network {
    public:
        Network(const std::string& name);
        ~Network();

        // get
        bool getPodcast(const std::string& podcastTitle, Podcast** pod);
        bool getSubscriber(const std::string& name, Subscriber** sub);

        // add, remove
        bool addPodcast(const std::string& podcastTitle, const std::string& podcastHost);
        bool removePodcast(const std::string& podcastTitle);
        bool addEpisode(const std::string& podcastTitle, const std::string& episodeName, const std::string& content);
        bool addSubscriber(const std::string& name, const std::string& creditcard);

        // Client services
        bool download(const std::string& subscriberName, const std::string& podcastTitle, Podcast** pod);
        bool stream(const std::string& subscriberName, const std::string& podcastTitle, int episodeNum, Episode** ep);

        // other?
        bool hasSubscriber(const std::string& name);
        void print();


    private:
        std::string name;
        PodArray* podArray;
        Subscriber* subscribers[MAX_SUBS];
        int numSubs;
};

#endif