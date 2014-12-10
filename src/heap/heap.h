#ifndef __HEAP__
#define __HEAP__

#include <stdlib.h>
#include "heap_rep.h"

/**
* Creates a new heap with the given size doubled.
* The heap allocates double the bytes given to fit both an active and a passive part.
*
* @param bytes - The heap size in amount of bytes.
* @return Pointer to the new heap.
*/
MCHeap heap_init(size_t bytes);

/**
* De-allocates the given heap.
*/
void heap_del(MCHeap heap);

/**
* Allocates the given amount of bytes on the given heap.
*
* @param heap - The heap to allocate data on.
* @param header - The header that describes what is to be stored on the heap.
* @param bytes - The amount of bytes to allocate.
* @return Pointer to the allocated memory space.
*/
void *heap_allocate(MCHeap heap, void* header, int bytes);

/**
 * Copies the data from the pointer pointing to a part in the active heap to the first
 * empty slot in the passive part. Will also mark the header of the object
 * in the active part as copied to the passive part.
 * NOTE: This does not alter the data in any way, it is a clean copy of the data.
 *
 * @param heap - The heap to work on.
 * @param data - Pointer pointing to the data to copy over.
 * @return Returns pointer to the copied data. This will still be a legal pointer after a call to heap_swapActiveAndPassive function.
 */
void* heap_copyFromActiveToPassive(MCHeap heap, void *data);

/**
 * Replaces the header of the object pointed to by data paramter with the given
 * forwarding address and marks it as copied.
 *
 * @param heap - The heap to work on.
 * @param data - The object to mark.
 */
void heap_markAsCopied(MCHeap heap, void* data, void* forwarding_address);

/**
 * Checks if the object pointed to by the data parameter is marked as copied to the passive part.
 * 
 * @param heap - The heap to work on.
 * @param data - Pointer to the object on the active part to check.
 * @return 1 if the object has been copied, 0 if not.
 */
int heap_hasBeenCopied(MCHeap heap, void* data);

/**
 * Marks the active part of the heap as the passive and vice versa.
 *
 * @param heap - The heap to work on.
 */
void heap_swapActiveAndPassive(MCHeap heap);

/**
* Calculates the growth direction of the heap.
* A negative value indicates that it grows upward.
* A positive value indicates that it grows downward.
*
* @param heap - The heap to calculate the direction of.
* @return Int that indicates growth direction.
*/
int heap_getGrowthDirection(MCHeap heap);

#endif
