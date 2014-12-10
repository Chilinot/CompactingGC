#include <stdlib.h>
#include "heap.h"
#include "heap_rep.h"
#include "header.h"

MCHeap heap_init(size_t bytes) {
    MCHeap heap = malloc(sizeof(struct heap_s) + (bytes * 2));

    heap->active = heap + sizeof(struct heap_s);
    heap->passive = heap->active + bytes;

    heap->active_pointer = heap->active;
    heap->passive_pointer = heap->passive;

    return heap;
}

void heap_del(MCHeap heap) {
    free(heap);
}

void* heap_allocate(MCHeap heap, void* header, int bytes) {
    MCHeapBlock block = heap->active_pointer;

    block->header = header;

    void *data_pointer = heap->active_pointer + sizeof(void*);

    heap->active_pointer += bytes + sizeof(void*);

    return data_pointer;
}

void* heap_allocate_passive(MCHeap heap, void* header, int bytes) {
    MCHeapBlock block = heap->passive_pointer;

    block->header = header;

    void *data_pointer = heap->passive_pointer + sizeof(void*);

    heap->passive_pointer += bytes + sizeof(void*);

    return data_pointer;
}

void* heap_copyFromActiveToPassive(MCHeap heap, void *data) {
    MCHeapBlock block = GET_HEAPBLOCK(data);
    
    void* header = (void*) block;
    size_t data_size = header_getSize(header);

    MCHeapBlock passive_block = heap_allocate_passive(heap, header, data_size);

    char* active_data = GET_DATABLOCK(block->header);
    char* passive_data = GET_DATABLOCK(passive_block->header);

    for(size_t i = 0; i < data_size; i++) {
        passive_data[i] = active_data[i];
    }

    heap_markAsCopied(heap, data, passive_data);

    return (void *) passive_data;
}

int heap_getGrowthDirection(MCHeap heap) {
    return heap->active - heap->passive;
}
