#include "Network.h"

Network::Network(const std::string& name) {
    this->name = name;
    podArray = new PodArray();
    numSubs = 0;
}

Network::~Network() {
    delete podArray;
    for (int i = 0; i < numSubs; ++i) {
        delete subscribers[i];
    }
}

bool Network::getPodcast(const std::string& podcastTitle, Podcast** pod) {
    return podArray->getPodcast(podcastTitle, pod);
}

bool Network::getSubscriber(const std::string& name, Subscriber** sub) {
    for (int i = 0; i < numSubs; ++i) {
        if (subscribers[i]->matches(name)) {
            *sub = subscribers[i];
            return true;
        }
    }
    return false;
}

bool Network::addPodcast(const std::string& podcastTitle, const std::string& podcastHost) {
    return podArray->addPodcast(new Podcast(podcastTitle, podcastHost));
}

bool Network::removePodcast(const std::string& podcastTitle) {
    Podcast* placeholderPtr;
    return podArray->removePodcast(podcastTitle, &placeholderPtr);
}

bool Network::addEpisode(const std::string& podcastTitle, const std::string& episodeName, const std::string& content) {
    Podcast* targetPodcast;
    if (podArray->getPodcast(podcastTitle, &targetPodcast)) {
        return targetPodcast->addEpisode(episodeName, content);
    } else {
        return false;
    }
}

bool Network::addSubscriber(const std::string& name, const std::string& creditcard) {
    if (numSubs < MAX_SUBS) {
        subscribers[numSubs] = new Subscriber(name, creditcard);
        ++numSubs;
        return true;
    }
    return false;
}

bool Network::download(const std::string& subscriberName, const std::string& podcastTitle, Podcast** pod) {
    if (hasSubscriber(subscriberName)) {
        if (podArray->getPodcast(podcastTitle, pod)) {
            return true;
        } else {
            std::cout << "ERROR: Could not download Podcast \"" << podcastTitle << "\" because it doesn't exist in our Network." << std::endl;
            return false;
        }
    } else {
        std::cout << "ERROR: Could not download Podcast \"" << podcastTitle << "\" because Subscriber \"" << subscriberName << "\" doesn't exist in our Network." << std::endl;
        return false;
    }
}

bool Network::stream(const std::string& subscriberName, const std::string& podcastTitle, int episodeNum, Episode** ep) {
    if (hasSubscriber(subscriberName)) {
        Podcast* podcastTarget;
        if (podArray->getPodcast(podcastTitle, &podcastTarget)) {
            if (podcastTarget->getEpisode(episodeNum, ep)) {
                return true;
            } else {
                std::cout << "ERROR: Could not stream Podcast \"" << podcastTitle << "\" episode " << episodeNum << " because Podcast \"" << podcastTitle << "\" doesn't have episode " << episodeNum << "." << std::endl;
                return false;
            }
        } else {
            std::cout << "ERROR: Could not stream Podcast \"" << podcastTitle << "\" episode " << episodeNum << " because no such Podcast exists in our Network." << std::endl;
            return false;
        }
    } else {
        std::cout << "ERROR: Could not stream Podcast \"" << podcastTitle << "\" because Subscriber \"" << subscriberName << "\" doesn't exist in our Network." << std::endl;
        return false;
    }
}

bool Network::hasSubscriber(const std::string& name) {
    for (int i = 0; i < numSubs; ++i) {
        if (subscribers[i]->matches(name)) {
            return true;
        }
    }
    return false;
}

void Network::print() {
    // [Network] $networkName
    // $numSubs Suscribers:
    // $(print all subscribers)
    // Podcasts on Network:
    // $podArray.print()
    std::cout << "[Network] " << name << std::endl <<
        numSubs << " Subscribers:" << std::endl;
    for (int i = 0; i < numSubs; ++i) {
        subscribers[i]->print();
    }
    std::cout << "Podcasts on Network:" << std::endl;
    podArray->print();
}