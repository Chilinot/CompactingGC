#include <stdlib.h>
#include "heap.h"
#include "heap_rep.h"
#include "header.h"

Heap heap_init (size_t bytes) {

	if (bytes <= sizeof (struct heap_s)) {
		// The given space is too small.
		return NULL;
	}

	// This is the amount of bytes available to the user.
	size_t allocateable = bytes - sizeof (struct heap_s);
	
	// This is the amount of bytes per block (active or passive block).
	size_t blocksize = allocateable / 2;

	// Make sure the block sizes are properly aligned.
	if (blocksize % sizeof (void *) != 0) {
		return NULL;
	}

	Heap heap = malloc (bytes);

	heap->heapsize = allocateable;
	
	heap->active = ( (char *) heap) + sizeof (struct heap_s);
	heap->passive = ( (char *) heap->active) + blocksize;

	heap->active_pointer = heap->active;
	heap->passive_pointer = heap->passive;

	return heap;
}

void heap_del (Heap heap) {
	free (heap);
}

void *heap_allocate_raw (Heap heap, size_t bytes) {
	char string[bytes];

	for (int i = 0; i < bytes; i++) {
		string[i] = 'c';
	}

	string[bytes] = '\0';
	return heap_allocate_struct (heap, &string);
}

void *heap_allocate_struct (Heap heap, char *structure) {
	void *header = header_fromFormatString (structure);
	size_t bytes = header_getSize (header);
	return heap_allocate (heap, header, bytes);
}

void *heap_allocate_union (Heap heap, size_t bytes, s_trace_f f) {
	void *header = header_objectSpecificFunction (f);
	return heap_allocate (heap, header, bytes);
}

void *heap_allocate (Heap heap, void *header, size_t bytes) {
	HeapBlock block = heap->active_pointer;

	// Make sure the bytes are properly aligned.
	// This will not work in all cases, but for this project it should work fine.
	bytes = bytes + (bytes % sizeof (void *));

	block->header = header;

	void *data_pointer = heap->active_pointer + sizeof (void *);

	heap->active_pointer += bytes + sizeof (void *);

	return data_pointer;
}

void *heap_allocatePassive (Heap heap, void *header, size_t bytes) {
	HeapBlock block = heap->passive_pointer;

	// Make sure the bytes are properly aligned.
	bytes = bytes + (bytes % sizeof (void *));

	block->header = header;

	void *data_pointer = heap->passive_pointer + sizeof (void *);

	heap->passive_pointer += bytes + sizeof (void *);

	return data_pointer;
}

void *heap_copyFromActiveToPassive (Heap heap, void *data) {

	//TODO heap_copyFromActiveToPassive needs to be remade.
	// Should it recurse over the object and copy any object this object is pointing to?

	HeapBlock block = GET_HEAPBLOCK (data);

	void *header = (void *) block;
	size_t data_size = header_getSize (header);

	HeapBlock passive_block = heap_allocatePassive (heap, header, data_size);

	char *active_data = GET_DATABLOCK (block->header);
	char *passive_data = GET_DATABLOCK (passive_block->header);

	for (size_t i = 0; i < data_size; i++) {
		passive_data[i] = active_data[i];
	}

	heap_markAsCopied (data, passive_data);

	return (void *) passive_data;
}

void heap_markAsCopied (void *data, void *forwarding_address) {
	HeapBlock block = GET_HEAPBLOCK (data);
	void *new_header = header_forwardingAddress (forwarding_address);
	block->header = new_header;
}

int heap_hasBeenCopied (void *data) {
	HeapBlock block = GET_HEAPBLOCK (data);
	return header_getHeaderType (block->header) == FORWARDING_ADDRESS;
}

void heap_swapActiveAndPassive (Heap heap) {

	// Temporary store the value of the active pointer.
	void *temp_active = heap->active;

	heap->active = heap->passive;
	heap->passive = temp_active;
	heap->active_pointer = heap->passive_pointer;

	// The passive pointer is reset to the beginning as no live data is stored there.
	heap->passive_pointer = heap->passive;
}


