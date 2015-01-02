#include "linkedlist.h"

#ifndef __heapiterator__
#define __heapiterator__

/**
 * Iterates over the given heap starting at the given start pointer.
 * It will return a linked list of pointers in the heap that points back to the heap.
 * 
 * @param start - The starting position in the heap. (Has to point to a HeapBlock)
 * @param heap - The heap to iterate over.
 * @return LinkedList of pointers to the heap.
 */
LinkedList heapIterator(void* start, Heap heap);

#endif