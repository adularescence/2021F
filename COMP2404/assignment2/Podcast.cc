#include "Podcast.h"

Podcast::Podcast(std::string title, std::string host) {
    this->title = title;
    this->host = host;
    this->episodes = new Episode*[MAX_EPS];
    this->numEps = 0;
}

Podcast::Podcast(Podcast& pod) {
    this->title = pod.getTitle();
    this->host = pod.getHost();
    this->episodes = new Episode*[MAX_EPS];
    this->numEps = 0;

    Episode* currEpisode;
    for (int i = 1; pod.getEpisode(i, &currEpisode); ++i) {
        addEpisode(currEpisode->getName(), currEpisode->getContent());
    }
}

Podcast::~Podcast() {
    for (int i = 0; i < numEps; ++i) {
        delete episodes[i];
    }
    delete [] episodes;
}

std::string Podcast::getTitle() const {
    return this->title;
}

std::string Podcast::getHost() const {
    return this->host;
}

int Podcast::getNumEpisodes() const {
    return this->numEps;
}

bool Podcast::addEpisode(std::string title, std::string content) {
    if (numEps < MAX_EPS) {
        episodes[numEps] = new Episode(this->title, numEps + 1, title, content);
        ++numEps;
        return true;
    } else {
        return false;
    }
}

bool Podcast::getEpisode(int index, Episode** ep) {
    // index can't be less than 0, nor beyond numEps
    if (index < 0 || index >= numEps) {
        return false;
    } else {
        *ep = episodes[index];
        return true;
    }
}

bool Podcast::lessThan(Podcast& pod) {
    // a2.pdf says "return true if this->name comes before pod.name"
    // let's assume it meant title instead
    return this->title < pod.getTitle();
}

void Podcast::print() {
    // [Podcast] "$title" hosted by "$host" ($numEps episodes)
    //
    std::cout << "[Podcast] \"" << title << "\" hosted by \"" << host << "\" (" << numEps << " episodes)" <<
        std::endl;
    for (int i = 0; i < numEps; ++i) {
        episodes[i]->play();
    }
}