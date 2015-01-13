#include <stdlib.h>

#ifndef __HEAP__
#define __HEAP__

// This structure is defined in heap_rep.c
typedef struct heap_s* Heap;

// The signature of the trace function
typedef void* (*trace_f)(Heap h, void* obj);

// The signature of object-specific trace functions. It will be
// called for its specific objects, and be given a generic trace
// function f to be called on each pointer inside obj.
typedef void* (*s_trace_f)(Heap h, trace_f f, void* obj);

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
 * Allocates a new object on the heap with the given format string.
 *
 * Valid characters are the same as for h_alloc_struct in gc.h.
 *
 * @param heap - The heap to allocate the object on.
 * @param structure - The format string.
 * @return Pointer to the newly allocated memory space.
 */
void* heap_allocate_struct(Heap heap, char* structure);

/**
 * Allocates a new object on the heap with the given amount of
 * bytes in size. This object is not allowed to have pointers back
 * into the heap.
 *
 * @param heap - The heap to allocate the object on.
 * @param bytes - The amount of bytes to allocate.
 * @return Pointer to the newly allocated memory space.
 */
void* heap_allocate_raw(Heap heap, size_t bytes);

/**
 * Allocate a new object on a heap with a given size, and
 * object-specific trace function.
 *
 * @param heap - The heap to allocate the object on.
 * @param bytes - The amount of bytes to allocate.
 * @param f - The object specific function.
 * @return Pointer to the newly allocated memory space.
 */
void* heap_allocate_union(Heap heap, size_t bytes, s_trace_f f);

/**
 * Allocates the given amount of bytes on the given heap.
 *
 * @param heap - The heap to allocate data on.
 * @param header - The header that describes what is to be stored on the heap.
 * @param bytes - The amount of bytes to allocate.
 * @return Pointer to the allocated memory space.
 */
void* heap_allocateActive(Heap heap, void* header, size_t bytes);

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
void* heap_copyFromActiveToPassive(Heap heap, void* data);

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

/**
 * Returns the amount of bytes left that can be allocated.
 *
 * @param heap - The heap to check free space.
 * @return The amount of bytes left that can be allocated for usage.
 */
size_t heap_sizeLeft(Heap heap);

/**
 * Returns pointer to the start of the active block in the given heap.
 *
 * @param heap - The heap to get the start of.
 * @return Pointer to the start of the active heap block.
 */
void* heap_getActiveStart(Heap heap);

/**
 * Returns pointer to the end of the currently allocated memory in the active heap block
 * of the given heap.
 *
 * @param heap - The heap to get the end of.
 * @return Pointer to the end of the active heap block.
 */
void* heap_getActiveEnd(Heap heap);

#endif
