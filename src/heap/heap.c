#include <stdlib.h>
#include "heap.h"
#include "heap_rep.h"


int getGrowthDirection(Heap heap) {
    return heap->active - heap->passive;
}
