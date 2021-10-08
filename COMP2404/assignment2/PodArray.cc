#include "PodArray.h"

PodArray::PodArray() {
    numPods = 0;
    podcasts = new Podcast*[MAX_PODS];
}

PodArray::PodArray(PodArray& pa) {
    podcasts = new Podcast*[MAX_PODS];
    for (int i = 0; i < pa.numPods; ++i) {
        podcasts[i] = new Podcast(*pa.podcasts[i]);
    }
    numPods = pa.numPods;
}


PodArray::~PodArray() {
    for (int i = 0; i < numPods; ++i) {
        delete podcasts[i];
    }
    delete [] podcasts;
}

bool PodArray::addPodcast(Podcast* p) {
    if (numPods >= MAX_PODS) return false;
    for (int i = numPods; i > 0; --i){
        if (p->lessThan(*podcasts[i - 1])){
            podcasts[i] = podcasts[i - 1];
        } else {
            podcasts[i] = p;
            ++numPods;
            return true;
        }
    }
    podcasts[0] = p;
    ++numPods;
    return true;
}

bool PodArray::removePodcast(const string& title, Podcast** pod) {
    int index = 0;
    for (; index < numPods; ++index) {
        if (podcasts[index]->getTitle() == title) {
            // update output parameter
            *pod = podcasts[index];

            // retain index
            break;
        }
    }

    // if the first for loop didn't hit the if statement, then index == numPods
    // which means no podcast with title $title was found, thus return false
    // but it's anything else, then it means we found something
    // therefore we shift the remaining podcasts up by 1
    if (index != numPods) {
        --numPods;
        delete podcasts[index];
        for (; index < numPods; ++index) {
            podcasts[index] = podcasts[index + 1];
        }
        return true;
    } else {
        return false;
    }
}

bool PodArray::getPodcast(const string& title, Podcast** pod) {
    for (int i = 0; i < numPods; ++i) {
        if (podcasts[i]->getTitle() == title) {
            *pod = podcasts[i];
            return true;
        }
    }
    return false;
}

bool PodArray::isFull() {
    return numPods >= MAX_PODS;
}

int PodArray::size() {
    return numPods;
}

void PodArray::print() {
    for (int i = 0; i < numPods; ++i) {
        podcasts[i]->print();
    }
}
