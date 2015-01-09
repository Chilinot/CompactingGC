#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "heap.h"
#include "heap_rep.h"
#include "header.h"

// Comment the following row to disable debug output
// #define HEAP_DEBUG

#ifdef HEAP_DEBUG
#include "debug.h"
#endif

Heap heap_init(size_t bytes) {
	
	size_t struct_size = sizeof(struct heap_s);

	if(bytes <= struct_size) {
		// The given space is too small.
		return NULL;
	}

	// This is the amount of bytes available to the user.
	size_t allocateable = bytes - struct_size;

	// This is the amount of bytes per block (active or passive block).
	size_t blocksize = allocateable / 2;

	// Make sure the block sizes are properly aligned.
	if(blocksize % sizeof(void*) != 0) {
		return NULL;
	}

	Heap heap = calloc(bytes, 1);

	heap->heapsize = allocateable;

	heap->active = (void*) (((char*) heap) + struct_size);
	heap->passive = (void*) (((char*) heap->active) + blocksize);

	heap->active_pointer = heap->active;
	heap->passive_pointer = heap->passive;

	return heap;
}

void heap_del(Heap heap) {
	free(heap);
}

void* heap_allocate_raw(Heap heap, size_t bytes) {
	char string[bytes + 1];

	for(int i = 0; i < bytes; i++) {
		string[i] = 'c';
	}

	string[bytes] = '\0';
	return heap_allocate_struct(heap, string);
}

void* heap_allocate_struct(Heap heap, char* structure) {
	void* header = header_fromFormatString(heap, structure);
	
#ifdef HEAP_DEBUG
	puts("heap_allocate_struct() header binary:");
	printBits(sizeof(void*), &header);
#endif
	
	size_t bytes = header_getSize(header);
	return heap_allocateActive(heap, header, bytes);
}

void* heap_allocate_union(Heap heap, size_t bytes, s_trace_f f) {
	void* header = header_objectSpecificFunction(f);
	return heap_allocateActive(heap, header, bytes);
}

void* heap_allocateActive(Heap heap, void* header, size_t bytes) {
	return heap_allocate(heap, header, bytes, &heap->active_pointer);
}

void* heap_allocatePassive(Heap heap, void* header, size_t bytes) {
	return heap_allocate(heap, header, bytes, &heap->passive_pointer);
}

void* heap_allocate(Heap heap, void* header, size_t bytes, void** block_pointer) {
	HeapBlock block = *block_pointer;
	
	// Make sure the bytes are properly aligned.
	// This will not work in all cases, but for this project it should work fine.
	bytes = bytes + (bytes % sizeof(void*));
	
	block->header = header;
	
	*block_pointer = ((char*) *block_pointer) + sizeof(void*) + bytes;
	
	return (((char*) &block->header) + sizeof(void*));
}

void* heap_copyFromActiveToPassive(Heap heap, void* data) {

	//TODO heap_copyFromActiveToPassive needs to be remade.
	// Should it recurse over the object and copy any object this object is pointing to?

	HeapBlock block = GET_HEAPBLOCK(data);

	void* header = block->header;
	size_t data_size = header_getSize(header);
	
#ifdef HEAP_DEBUG
	printf("\ndata_size: %zu\n", data_size);
	
	puts("Header binary #1:");
	printBits(sizeof(void*), &header);
	puts("");
#endif

	char* active_data = data;
	char* passive_data = heap_allocatePassive(heap, header, data_size);
	
#ifdef HEAP_DEBUG
	puts("Passive data binary #1:");
	printBits(sizeof(void*), &passive_data);
	puts("");
#endif

	for(size_t i = 0; i < data_size; i++) {
#ifdef HEAP_DEBUG
		puts("active_data char:");
		printf("%c\n", active_data[i]);
		puts("");
#endif
		passive_data[i] = active_data[i];
	}
	
#ifdef HEAP_DEBUG
	puts("Passive data binary #2:");
	printBits(sizeof(void*), &passive_data);
	puts("");
#endif

	heap_markAsCopied(data, passive_data);
	
#ifdef HEAP_DEBUG
	puts("Header binary #2 ought to be forwarding address:");
	printBits(sizeof(void*), &block->header);
	puts("");
#endif

	return (void*) passive_data;
}

void heap_markAsCopied(void* data, void* forwarding_address) {
	HeapBlock block = GET_HEAPBLOCK(data);
	
#ifdef HEAP_DEBUG
	puts("header and forwardinng address:");
	printBits(sizeof(void*), &block->header);
	printBits(sizeof(void*), &forwarding_address);
#endif
	
	void* new_header = header_forwardingAddress(forwarding_address);
	block->header = new_header;
	
#ifdef HEAP_DEBUG
	puts("header");
	printBits(sizeof(void*), &new_header);
#endif
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

size_t heap_sizeLeft(Heap heap) {
	size_t blocksize = heap->heapsize / 2;
	
	char* active_start = heap->active;
	char* active_pointer = heap->active_pointer;
	
	size_t bytes_used = active_pointer - active_start;
	
	return blocksize - bytes_used;
}

void* heap_getActiveStart(Heap heap) {
	return heap->active;
}

void* heap_getActiveEnd(Heap heap) {
	return heap->active_pointer;
}