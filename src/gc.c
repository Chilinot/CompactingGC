#include "gc.h"
#include "heap.h"
#include "header.h"
#include "stack.h"
#include "heap_rep.h"
#include "heapIterator.h"
#include "string_util.h"

// Create a heap from the heap module with the given amount of bytes.
// Return a pointer to said heap.
Heap h_init(size_t bytes) {
	Heap h = heap_init(bytes);
	return h;
}

// Destroy the given heap by calling the appropriate function in the heap module.
void h_delete(Heap h) {
	heap_del(h);
}

// Calls stack tracer to retrieve pointers to all places in the stack that contains pointers to the heap and
// the overwrites the values on the stack with the dbg_value.
// Call h_delete() with the given heap.
void h_delete_dbg(Heap h, void* dbg_value) {
	void setPointerTodbg_value(void** pointer) {
		*pointer = dbg_value;
	}

	stackIterator(heap_getActiveStart(h) - 1, heap_getActiveEnd(h) + 1, setPointerTodbg_value);

	heap_del(h);
}

// Calls function in heap module that returns the available size and return that value.	 
size_t h_avail(Heap h) {
	return heap_sizeLeft(h);
}

// Retrieves pointers to all places in the stack that contains pointers to the heap.
// and iterates over the heap and finds pointers to other objects on the heap.
// Also copies objects from active to passive using the pointers retrieved and swap the active and the passive
// area. Returns the available size.
size_t h_gc(Heap h) {
	void f(void** stackPekare) {
		*stackPekare = heapIterator(h, *stackPekare);
	}

	stackIterator(heap_getActiveStart(h) - 1, heap_getActiveEnd(h) + 1, &f);

	heap_swapActiveAndPassive(h);

	return h_avail(h);
}

// Checks if there is space left in the heap and if there is space
// left in the heap triggers garbage collection.
// If there is still not enough space left in the heap after the garbage collection return null.
// Also creates a string with the value in bytes amount of 'c' characters.
void* h_alloc_data(Heap h, size_t bytes) {
	if(h_avail(h) < bytes) {
		if(h_gc(h) < bytes) {
			return NULL;
		}
	}

	//else
	return heap_allocate_raw(h, bytes);
}

// Checks if there is space left in the heap and if there is space
// left in the heap triggers garbage collection.
// If there is still not enough space left in the heap after the garbage collection return null.
void* h_alloc_struct(Heap h, char* layout) {
	char* headerString = formatStringToHeaderString(layout);
	size_t bytes = headerStringToSize(headerString);
	free(headerString);

	if(h_avail(h) < bytes) {
		if(h_gc(h) < bytes) {
			return NULL;
		}
	}

	//else
	return heap_allocate_struct(h, layout);
}

// Checks if there is space left in the heap and if there is space
// left in the heap triggers garbage collection.
// If there is still not enough space left in the heap after the garbage collection return null.
// Then allocates the objects with function pointers.
void* h_alloc_union(Heap h, size_t bytes, s_trace_f f) {
	if(h_avail(h) < bytes) {
		if(h_gc(h) < bytes) {
			return NULL;
		}
	}

	//else
	return heap_allocate_union(h, bytes, f);
}


