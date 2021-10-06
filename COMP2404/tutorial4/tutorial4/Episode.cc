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

void Episode::play() {
    // [Podcast] $podcast
    //     [Episode] $episodeName ($episodeNumber)
    //     $content
    std::cout << "[Podcast] " << this->podcast << std::endl <<
        "    [Episode] " << this->name << " (" << this->number << ")" << std::endl <<
        "    " << this->content << std::endl;
}