#ifndef CLIENT_H
#define CLIENT_H

#include <string>
#include <iostream>

#include "Network.h"
#include "PodArray.h"
#include "Podcast.h"

class Client {
    public:
        Client(std::string& name);
        ~Client();

        void download(Network* network, std::string& podcastTitle);
        void stream(Network* network, std::string& podcastTitle, int& episodeNum);
        void playLocal(std::string& podcastTitle, int episodeNum);
        void print();

    private:
        std::string name;
        PodArray* podArray;
};

#endif