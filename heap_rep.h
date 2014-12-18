#ifndef __HEAP_REP__
#define __HEAP_REP__

#define GET_HEAPBLOCK(p) ((HeapBlock) p - sizeof(void*))
#define GET_DATABLOCK(p) ((void*) p + sizeof(void*))

typedef struct heap_block {
    void *header; // Contains all metadata.
    // Directly after the header pointer is the data.
} *HeapBlock;

typedef struct heap_s {
    void *active_pointer;  // Like the stack pointer, but for the heap.
    void *passive_pointer; // Like the above.
    void *active;   // Points to the active part of the heap.
    void *passive;  // Same as above but for the passive.
};

#endif
