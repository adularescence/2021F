#ifndef PODCAST_H
#define PODCAST_H

#include <iostream>
#include <string>

#include "defs.h"
#include "Episode.h"

class Podcast {
    public:
        Podcast(const std::string& title, const std::string& host);
        Podcast(Podcast& pod);
        ~Podcast();

        std::string getTitle() const;
        std::string getHost() const;
        int getNumEpisodes() const;

        bool addEpisode(const std::string& title, const std::string& content);
        bool getEpisode(int index, Episode** ep);
        bool lessThan(Podcast& pod);
        void print();

    private:
        std::string title, host;
        Episode** episodes;
        int numEps;
};

#endif