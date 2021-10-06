#ifndef STACKARRAYS_H
#define STACKARRAYS_H

#include "Episode.h"
#include "defs.h"

class StackArrays {
    public:
        StackArrays();
        ~StackArrays();

        Episode* getObjectArray();
        Episode** getPointerArray();

    private:
        Episode episodes[ARR_SIZE];
        Episode** episodePtrs;
};

#endif