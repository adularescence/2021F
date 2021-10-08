#include "Episode.h"

#include <iostream>

Episode::Episode() {
    this->podcast = "Placeholder Podcast Name";
    this->number = 1;
    this->name = "Generic Name";
    this->content = "Placeholder content";
}

Episode::Episode(const std::string& podcast, int number, const std::string& name, const std::string& content) {
    this->podcast = podcast;
    this->number = number;
    this->name = name;
    this->content = content;
}

std::string Episode::getName() const {
    return this->name;
}

std::string Episode::getContent() const {
    return this->content;
}

void Episode::play() {
    // [Episode] $episodeName ($episodeNumber)
    //     From [Podcast] $podcastTitle
    //     $content
    //
    std::cout << "[Episode] " << name << " (" << number << ")" << std::endl <<
        "    From [Podcast] " << podcast << std::endl << 
        "    " << content <<
        std::endl;
}