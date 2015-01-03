#include <stdlib.h>

#ifndef __HEAP__
#define __HEAP__

// This structure is defined in heap_rep.c
typedef struct heap_s *Heap;

/**
* Creates a heap with the given size in bytes.
* Only half of the given amount will be usable at all times due
* to it being split into an active and a passive area.
* 
* Returns null if the given size does not have space enough 
* to fit metadata required by the heap.
*
* @param bytes - The heap size in amount of bytes.
* @return Pointer to the new heap, or null if the given space is too small.
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
 * Copies the data from the pointer pointing to a part in the active heap to the first
 * empty slot in the passive part. Will also mark the header of the object
 * in the active part as copied to the passive part.
 * NOTE: This does not alter the data in any way, it is a clean copy of the data.
 *
 * @param heap - The heap to work on.
 * @param data - Pointer pointing to the data to copy over.
 * @return Returns pointer to the copied data. This will still be a legal pointer after a call to heap_swapActiveAndPassive function.
 */
void* heap_copyFromActiveToPassive(Heap heap, void *data);

/**
 * Replaces the header of the object pointed to by data parameter with the given
 * forwarding address and marks it as copied.
 *
 * @param data - The object to mark.
 * @param forwarding_address - The address the new header should point to.
 */
void heap_markAsCopied(void* data, void* forwarding_address);

/**
 * Checks if the object pointed to by the data parameter is marked as copied to the passive part.
 * 
 * @param data - Pointer to the object on the active part to check.
 * @return 1 if the object has been copied, 0 if not.
 */
int heap_hasBeenCopied(void* data);

/**
 * Marks the active part of the heap as the passive and vice versa.
 *
 * @param heap - The heap to work on.
 */
void heap_swapActiveAndPassive(Heap heap);

#endif
