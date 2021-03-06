#ifndef EPISODE_H
#define EPISODE_H

#include <string>

class Episode {
    public:
        Episode();
        Episode(const std::string& podcast, int number, const std::string& name, const std::string& content);
        void play();

    private:
        std::string name, content, podcast;
        int number;
};

#endif