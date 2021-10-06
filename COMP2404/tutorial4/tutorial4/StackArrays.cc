#include "StackArrays.h"

StackArrays::StackArrays() {
    this->episodePtrs = new Episode*[ARR_SIZE];
    for (int i = 0; i < ARR_SIZE; ++i) {
        this->episodePtrs[i] = new Episode();
    }
}

StackArrays::~StackArrays() {
    for (int i = 0; i < ARR_SIZE; ++i) {
        delete(this->episodePtrs[i]);
    }
    delete[](this->episodePtrs);
}

Episode* StackArrays::getObjectArray() {
    return this->episodes;
}

Episode** StackArrays::getPointerArray() {
    return this->episodePtrs;
}