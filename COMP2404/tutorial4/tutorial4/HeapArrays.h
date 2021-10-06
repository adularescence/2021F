
#ifndef HEAPARRAYS_H
#define HEAPARRAYS_H

#include "Episode.h"
#include "defs.h"

class HeapArrays {
    public:
        HeapArrays();
        ~HeapArrays();

        Episode* getObjectArray();
        Episode** getPointerArray();

    private:
        Episode* episodes;
        Episode** episodePtrs;
};

#endif