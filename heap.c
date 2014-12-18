#include <stdlib.h>
#include "heap.h"
#include "heap_rep.h"
#include "header.h"

Heap heap_init(size_t bytes) {

	if(bytes > sizeof(struct heap_s)) {
		// The given space is too small.
		return NULL;
	}

	Heap heap = malloc(bytes);
	
	heap->active = heap + sizeof(struct heap_s);
	heap->passive = heap->active + ((bytes - sizeof(struct heap_s)) / 2);
	
	heap->active_pointer = heap->active;
	heap->passive_pointer = heap->passive;

    return heap;
}

void heap_del(Heap heap) {
    free(heap);
}

void* heap_allocate(Heap heap, void* header, int bytes) {
    HeapBlock block = heap->active_pointer;

    block->header = header;

    void *data_pointer = heap->active_pointer + sizeof(void*);

    heap->active_pointer += bytes + sizeof(void*);

    return data_pointer;
}

void* heap_allocatePassive(Heap heap, void* header, int bytes) {
    HeapBlock block = heap->passive_pointer;

    block->header = header;

    void *data_pointer = heap->passive_pointer + sizeof(void*);

    heap->passive_pointer += bytes + sizeof(void*);

    return data_pointer;
}

void* heap_copyFromActiveToPassive(Heap heap, void *data) {
    HeapBlock block = GET_HEAPBLOCK(data);

    void* header = (void*) block;
    size_t data_size = header_getSize(header);

    HeapBlock passive_block = heap_allocatePassive(heap, header, data_size);

    char* active_data = GET_DATABLOCK(block->header);
    char* passive_data = GET_DATABLOCK(passive_block->header);

    for(size_t i = 0; i < data_size; i++) {
        passive_data[i] = active_data[i];
    }

    heap_markAsCopied(heap, data, passive_data);

    return (void *) passive_data;
}

int heap_getGrowthDirection(Heap heap) {
    return heap->active - heap->passive;
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