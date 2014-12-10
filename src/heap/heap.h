#ifndef __HEAP__
#define __HEAP__

#include <stdlib.h>

typedef struct heap_s *Heap;

/**
* Creates a new heap with the given size doubled.
* The heap allocates double the bytes given to fit both an active and a passive part.
*
* @param bytes - The heap size in amount of bytes.
* @return Pointer to the new heap.
*/
Heap heap_init(size_t bytes);

/**
* De-allocates the given heap.
*/
void heap_del(Heap heap);

/**
* Allocates the given amount of bytes on the given heap.
*
* @param heap - The heap to allocate data on.
* @param header - The header that describes what is to be stored on the heap.
* @param bytes - The amount of bytes to allocate.
* @return Pointer to the allocated memory space.
*/
void *heap_allocate(Heap heap, void* header, size_t bytes);

/**
* Calculates the growth direction of the heap.
* A negative value indicates that it grows upward.
* A positive value indicates that it grows downward.
*
* @param heap - The heap to calculate the direction of.
* @return Int that indicates growth direction.
*/
int getGrowthDirection(Heap heap);

#endif
