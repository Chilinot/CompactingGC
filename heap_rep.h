/**
 * @File
 */
#ifndef __HEAP_REP__
#define __HEAP_REP__

#define GET_HEAPBLOCK(p) ((HeapBlock) (((char*) p) - sizeof(void*)))
#define GET_DATABLOCK(p) ((void*) (((char*) p) + sizeof(void*)))

typedef struct heap_block {
	void* header; // Contains all metadata.
	// Directly after the header pointer is the data.
}* HeapBlock;

struct heap_s {
	size_t heapsize; // This is total heap size without the size of this structure. Basically active + passive.
	void* active_pointer;  // Like the stack pointer, but for the heap.
	void* passive_pointer; // Like the above.
	void* active;   // Points to the active part of the heap.
	void* passive;  // Same as above but for the passive.
};

/**
 * Allocates an object on the passive area of the heap similar to
 * how heap_allocate allocates memory on the active area.
 *
 * @param heap - The heap to allocate on.
 * @param header - The header to use for the allocated data.
 * @param bytes - The amount of bytes to allocate.
 * @return Pointer to the allocated memory space.
 */
void* heap_allocatePassive(struct heap_s* heap, void* header, size_t bytes);

/**
 * Allocates memory based on the given pointers.
 *
 * @param heap - The heap to allocate memory in.
 * @param header - The header to use for the allocated memory.
 * @param bytes - The amount of bytes to allocate.
 * @param block_pointer - Double pointer to start of allocatable space.
 * @return Returns pointer to allocated memory space.
 */
void* heap_allocate(struct heap_s* heap, void* header, size_t bytes, void** block_pointer);

#endif
