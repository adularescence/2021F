#include "HeapArrays.h"

HeapArrays::HeapArrays() {
    this->episodes = new Episode[ARR_SIZE];
    this->episodePtrs = new Episode*[ARR_SIZE];
    for (int i = 0; i < ARR_SIZE; ++i) {
        this->episodePtrs[i] = new Episode();
    }
}

HeapArrays::~HeapArrays() {
    for (int i = 0; i < ARR_SIZE; ++i) {
        delete(this->episodePtrs[i]);
    }
    delete[](this->episodes);
    delete[](this->episodePtrs);
}

Episode* HeapArrays::getObjectArray() {
    return this->episodes;
}

Episode** HeapArrays::getPointerArray() {
    return this->episodePtrs;
}