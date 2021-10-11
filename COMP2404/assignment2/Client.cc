#include "Client.h"

Client::Client(const std::string& name) {
    this->name = name;
    this->podArray = new PodArray();
}

Client::~Client() {
    delete podArray;
}

void Client::download(Network* network, const std::string& podcastTitle) {
    Podcast* target;
    // assume client->name is subscriber name
    if (network->download(name, podcastTitle, &target)) {
        if (!podArray->isFull()) {
            podArray->addPodcast(new Podcast(*target));
        } else {
            std::cout << "ERROR: Cannot download \"" << podcastTitle << "\" because the PodArray is full." << std::endl;
        }
    } else {
        std::cout << "ERROR: Cannot download \"" << podcastTitle << "\" because it doesn't exist on the provided Network, or you are not a subscriber on the provided Network." << std::endl; 
    }
}

void Client::stream(Network* network, const std::string& podcastTitle, int& episodeNum) {
    Episode* target;
    if (network->stream(name, podcastTitle, episodeNum, &target)) {
        target->play();
    }
}

void Client::playLocal(const std::string& podcastTitle, int episodeNum) {
    Podcast* podcastTarget;
    if (podArray->getPodcast(podcastTitle, &podcastTarget)) {
        Episode* episodeTarget;
        if (podcastTarget->getEpisode(episodeNum, &episodeTarget)) {
            episodeTarget->play();
        } else {
            std::cout << "ERROR: Cannot play episode " << episodeNum << " of \"" << podcastTitle << "\" because there isn't an episode " << episodeNum << "." << std::endl;
        }
    } else {
        std::cout << "ERROR: Cannot play \"" << podcastTitle << "\" because it doesn't exist in the local PodArray." << std::endl;
    }
}

void Client::print() {
    // [Client] $name
    // Local Podcasts:
    // $podArray.print()
    std::cout << "[Client] " << name << std::endl <<
        "Local Podcasts:" << std::endl;
    podArray->print();
}