#include "gc.h"

Heap h_init(size_t bytes) {
	/* 
	 * 1. Create a heap from the heap module with the given amount of bytes.
	 * 2. Return a pointer to said heap.
	 */
}

void h_delete(Heap h) {
	/*
	 * 1. Destroy the given heap by calling the appropriate function in the heap module. 
	 */
}

void h_delete_dbg(Heap h, void* dbg_value) {
	/*
	 * 1. Call stack tracer to retreive pointers to all places in the stack that contains pointers to the heap.
	 * 2. Call h_delete() with the given heap.
	 * 3. Overwrite the values on the stack with the dbg_value using pointers from #1.
	 */
}

size_t h_avail(Heap h) {
	/*
	 * 1. Call function in heap module that returns the available size and return that value.
	 */
}

size_t h_gc(Heap h) {
	/*
	 * 1. Call stack tracer to retreive pointers to all places in the stack that contains pointers to the heap.
	 * 2. Use pointers from #1 to call heap iterator that iterates over the heap and finds pointers to other objects on the heap.
	 *    (The heap iterator should also return pointers to places in the heap similar to stack tracer!)
	 * 3. Call function in heap module that copies objects from active to passive using pointers retreived in #2.
	 * 4. Call function in heap module to swap active and passive area.
	 * 5. Return available size by calling appropriate function in heap module.
	 */
}

void* h_alloc_data(Heap h, size_t bytes) {
	/*
	 * 1. Check if there is space left in the heap.
	 *    If there are no space left in the heap, call h_gc to trigger garbage collection.
	 * 2. Create a string with the value in bytes amount of 'c' characters.
	 * 3. Call the function for allocating objects with strings in the heap module with the newly created string.
	 */
}

void* h_alloc_struct(Heap h, char* layout) {
	/*
	 * Same as h_alloc_data but here we don't need to create a string.
	 */
}

void* h_alloc_union(Heap h, size_t bytes, s_trace_f f) {
	/*
	 * 1. Check if there is space left in the heap.
	 *    If there are no space left in the heap, call h_gc to trigger garbage collection.
	 * 2. Call function in heap module for allocating objects with function pointers.
	 */
}

