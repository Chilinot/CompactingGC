#include <stdlib.h>
#include "heap.h"
#include "heap_rep.h"
#include "header.h"

Heap heap_init(size_t bytes) {

	if(bytes <= sizeof(struct heap_s)) {
		// The given space is too small.
		return NULL;
	}
	
	// This is the amount of bytes available to the user.
	size_t allocateable = bytes - sizeof(struct heap_s);
	
	// Make sure the available space can be split in half and still be properly aligned.
	if((allocateable / 2) % sizeof(void*) != 0) {
		return NULL;
	}
	
	Heap heap = malloc(bytes);
	
	heap->active = ((char*) heap) + sizeof(struct heap_s);
	heap->passive = ((char*) heap->active) + (allocateable / 2);
	
	heap->active_pointer = heap->active;
	heap->passive_pointer = heap->passive;

    return heap;
}

void heap_del(Heap heap) {
    free(heap);
}

void* heap_allocate(Heap heap, void* header, size_t bytes) {
    HeapBlock block = heap->active_pointer;
	
	// Make sure the bytes are properly aligned.
	// This will not work in all cases, but for this project it should work fine.
	bytes = bytes + (bytes % sizeof(void*));

    block->header = header;

    void *data_pointer = heap->active_pointer + sizeof(void*);

    heap->active_pointer += bytes + sizeof(void*);

    return data_pointer;
}

void* heap_allocatePassive(Heap heap, void* header, size_t bytes) {
    HeapBlock block = heap->passive_pointer;

	// Make sure the bytes are properly aligned.
	bytes = bytes + (bytes % sizeof(void*));
	
    block->header = header;

    void *data_pointer = heap->passive_pointer + sizeof(void*);

    heap->passive_pointer += bytes + sizeof(void*);

    return data_pointer;
}

void* heap_copyFromActiveToPassive(Heap heap, void *data) {
	
	//TODO heap_copyFromActiveToPassive needs to be remade.
	// Should it recurse over the object and copy any object this object is pointing to?

    HeapBlock block = GET_HEAPBLOCK(data);

    void* header = (void*) block;
    size_t data_size = header_getSize(header);

    HeapBlock passive_block = heap_allocatePassive(heap, header, data_size);

    char* active_data = GET_DATABLOCK(block->header);
    char* passive_data = GET_DATABLOCK(passive_block->header);

    for(size_t i = 0; i < data_size; i++) {
        passive_data[i] = active_data[i];
    }

    heap_markAsCopied(data, passive_data);

    return (void *) passive_data;
}

void heap_markAsCopied(void* data, void* forwarding_address) {
	HeapBlock block = GET_HEAPBLOCK(data);
	void* new_header = header_forwardingAddress(forwarding_address);
	block->header = new_header;
}

int heap_hasBeenCopied(void* data) {
	HeapBlock block = GET_HEAPBLOCK(data);
	return header_getHeaderType(block->header) == FORWARDING_ADDRESS;
}

void heap_swapActiveAndPassive(Heap heap) {
	
	// Temporary store the value of the active pointer.
	void* temp_active = heap->active;
	
	heap->active = heap->passive;
	heap->passive = temp_active;
	heap->active_pointer = heap->passive_pointer;

	// The passive pointer is reset to the beginning as no live data is stored there.
	heap->passive_pointer = heap->passive;
}