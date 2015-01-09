#include "CUnit/Basic.h"
#include "heap.h"
#include "heap_rep.h"
#include "header.h"

// Comment this row to disable debug output.
//#define HEAP_TESTS_DEBUG

#ifdef HEAP_TESTS_DEBUG
#include "debug.h"
#endif

// --- SUITES ---
int init_suite_1(void) {
	return 0;
}

int clean_suite_1(void) {
	return 0;
}

// --- UNIT TESTS ---

void testInit() {
	// Test with not enough memory space.
	Heap heap = heap_init(1);
	CU_ASSERT(heap == NULL);

	// Test with exactly enough space to fit structure.
	heap = heap_init(sizeof(struct heap_s));
	CU_ASSERT(heap == NULL);

	// Test with enough space.
	heap = heap_init(sizeof(struct heap_s) + 4 * sizeof(void*));
	CU_ASSERT(heap != NULL);
	
	CU_ASSERT(heap->active == heap->active_pointer);
	CU_ASSERT(heap->passive == heap->passive_pointer);
	
	size_t delta = heap->passive - heap->active;
	CU_ASSERT(delta / sizeof(void*) == 2);
	
	// Make sure there are at least two rows of empty data in passive block since there should be two empty rows per memory block.
	for(int i = 0; i < 2 * sizeof(void*); i++) {
		CU_ASSERT(((char*) heap->passive)[i] == NULL);
	}
	
	free(heap);
}

void testDel() {
	//This method can only be tested with valgrind.
}

void testAllocStruct() {
	Heap heap = heap_init(sizeof(struct heap_s) + 4 * sizeof(void*));
	CU_ASSERT(heap != NULL);
	
	void* foo = heap_allocate_struct(heap, "i");
	void* bar = heap_allocate_struct(heap, "i");
	
	strcpy(foo, "foo");
	strcpy(bar, "foo");
	
	CU_ASSERT(strcmp(foo, bar) == 0);
	
	// Check if bar block is after foo block.
	CU_ASSERT(foo < bar);
	
	// Check if bar block still is after foo when subtracting sizeof(void*) (this is for header).
	CU_ASSERT(foo < (bar - 1));
	
	// Check if allocation is only allocating the given space (with padding if needed).
	CU_ASSERT((((char*)foo) + sizeof(int) + (sizeof(int) % sizeof(void*))) == (((char*) bar) - sizeof(void*)));
	
	free(heap);
}

void testAllocRaw() {
	Heap heap = heap_init(sizeof(struct heap_s) + 12 * sizeof(void*));
	CU_ASSERT(heap != NULL);
	
	void* foo = heap_allocate_raw(heap, 4);
	void* bar = heap_allocate_raw(heap, 4);
	
	strcpy(foo, "foo");
	strcpy(bar, "foo");
	
	CU_ASSERT(strcmp(foo, bar) == 0);
	
	// Check if bar block is after foo block.
	CU_ASSERT(foo < bar);
	
	// Check if bar block still is after foo when subtracting sizeof(void*) (this is for header).
	CU_ASSERT(foo < (bar - 1));
	
	// Check if allocation is only allocating the given space (with padding if needed).
	CU_ASSERT((((char*)foo) + 4 + (4 % sizeof(void*))) == (((char*) bar) - sizeof(void*)));
	
	free(heap);
}

void testAllocUnion() {
	Heap heap = heap_init(sizeof(struct heap_s) + 4 * sizeof(void*));
	CU_ASSERT(heap != NULL);
	free(heap);
}

void testAllocateActive() {
	Heap heap = heap_init(sizeof(struct heap_s) + 12 * sizeof(void*));
	CU_ASSERT(heap != NULL);
	
	void* foo_header = header_fromFormatString("ii");
	void* bar_header = header_fromFormatString("ii");
	
	int* foo = heap_allocateActive(heap, foo_header, 2 * sizeof(int));
	int* bar = heap_allocateActive(heap, bar_header, 2 * sizeof(int));
	
	*foo = 12;
	*(foo + 1) = 27;
	
	*bar = 23;
	*(bar + 1) = 53;
	
	CU_ASSERT(*foo == 12);
	CU_ASSERT(*(foo + 1) == 27);
	
	CU_ASSERT(*bar == 23);
	CU_ASSERT(*(bar + 1) == 53);
	
	free(heap);
}

void testAllocatePassive() {
	Heap heap = heap_init(sizeof(struct heap_s) + 12 * sizeof(void*));
	CU_ASSERT(heap != NULL);
	
	void* foo_header = header_fromFormatString("ii");
	void* bar_header = header_fromFormatString("ii");
	
	int* foo = heap_allocatePassive(heap, foo_header, 2 * sizeof(int));
	int* bar = heap_allocatePassive(heap, bar_header, 2 * sizeof(int));
	
	*foo = 12;
	*(foo + 1) = 27;
	
	*bar = 23;
	*(bar + 1) = 53;
	
	CU_ASSERT(*foo == 12);
	CU_ASSERT(*(foo + 1) == 27);
	
	CU_ASSERT(*bar == 23);
	CU_ASSERT(*(bar + 1) == 53);
	
	free(heap);
}

void testAllocate() {
	Heap heap = heap_init(sizeof(struct heap_s) + 4 * sizeof(void*));
	CU_ASSERT(heap != NULL);
	
	void* header = header_fromFormatString("cccc");
	
	char* foo = heap_allocate(heap, header, header_getSize(header), &heap->active_pointer);
	char* bar = heap_allocate(heap, header, header_getSize(header), &heap->active_pointer);
	
	strcpy(foo, "foo");
	strcpy(bar, "bar");
	
	CU_ASSERT(strcmp(foo, "foo") == 0);
	CU_ASSERT(strcmp(bar, "bar") == 0);
	
	free(heap);
}

void testSizeLeft() {
	Heap heap = heap_init(sizeof(struct heap_s) + 8 * sizeof(void*));
	CU_ASSERT(heap != NULL);
	
	void* foo = heap_allocate_struct(heap, "*");
	
	size_t left = heap_sizeLeft(heap);
	
	CU_ASSERT(left == 2 * sizeof(void*));
	
	free(heap);
}

void testCopyFromActiveToPassive() {
	Heap heap = heap_init(sizeof(struct heap_s) + 12 * sizeof(void*));
	CU_ASSERT(heap != NULL);
	
	char* foo = heap_allocate_struct(heap, "cccc");
	strcpy(foo, "foo");
	
#ifdef HEAP_TESTS_DEBUG
	printf("\nfoo pointer: %p\n", foo);
	printf("foo: %s\n", foo);
#endif
	
	CU_ASSERT(strcmp(foo, "foo") == 0);
	
	HeapBlock block = GET_HEAPBLOCK(foo);
	
	CU_ASSERT(header_getHeaderType(block->header) == BITVECTOR);
	
#ifdef HEAP_TESTS_DEBUG
	printf("Header type: ");
	switch(header_getHeaderType(block->header)) {
		case BITVECTOR:
			puts("BITVECTOR");
			break;
		case POINTER_TO_STRING:
			puts("POINTER_TO_STRING");
			break;
		case FORWARDING_ADDRESS:
			puts("FORWARDING_ADDRESS");
			break;
		case FUNCTION_POINTER:
			puts("FUNCTION_POINTER");
			break;
	}
	printBits(sizeof(void*), &block->header);
#endif
	
	char* bar = heap_copyFromActiveToPassive(heap, (void*) foo);
	
	CU_ASSERT(strcmp(foo, bar) == 0);
	CU_ASSERT(header_getHeaderType(block->header) == FORWARDING_ADDRESS);
	
#ifdef HEAP_TESTS_DEBUG
	printf("foo pointer: %p\n", foo);
	printf("foo: %s\n", foo);
	printf("bar: %s\n", bar);
#endif
	
	free(heap);
}

void testMarkAsCopied() {
	Heap heap = heap_init(sizeof(struct heap_s) + 4 * sizeof(void*));
	CU_ASSERT(heap != NULL);
	
	void* foo = heap_allocate_struct(heap, "*");
	char* string = "foobar";
	
	heap_markAsCopied(foo, &string);
	
	HeapBlock block = GET_HEAPBLOCK(foo);
	void* header = block->header;
	
	CU_ASSERT(header_getHeaderType(header) == FORWARDING_ADDRESS);
	
	header = header_clearHeaderTypeBits(header);
	
	CU_ASSERT(strcmp(*((char**)header), string) == 0);
	
	free(heap);
}

void testHasBeenCopied() {
	Heap heap = heap_init(sizeof(struct heap_s) + 4 * sizeof(void*));
	CU_ASSERT(heap != NULL);
	
	void* foo = heap_allocate_struct(heap, "*");
	
	CU_ASSERT(!heap_hasBeenCopied(foo));
	
	heap_copyFromActiveToPassive(heap, foo);
	
	CU_ASSERT(heap_hasBeenCopied(foo));
	
	free(heap);
}

void testSwapActiveAndPassive() {
	Heap heap = heap_init(sizeof(struct heap_s) + 4 * sizeof(void*));
	CU_ASSERT(heap != NULL);
	
	void* active = heap->active;
	void* active_pointer = heap->active_pointer;
	
	void* passive = heap->passive;
	void* passive_pointer = heap->passive_pointer;
	
	heap_swapActiveAndPassive(heap);
	
	// Check if they have been swapped.
	CU_ASSERT(heap->active == passive);
	CU_ASSERT(heap->passive == active);
	
	// Check if active pointer has been set to first empty in the old active area.
	CU_ASSERT(heap->active_pointer == passive_pointer);
	
	// Check if passive pointer has been reset to the start.
	CU_ASSERT(heap->passive_pointer == heap->passive);
	
	free(heap);
}

void testGetActiveStart() {
	Heap heap = heap_init(sizeof(struct heap_s) + 4 * sizeof(void*));
	CU_ASSERT(heap != NULL);
	
	CU_ASSERT(heap->active == heap_getActiveStart(heap));
	
	free(heap);
}

void testGetActiveEnd() {
	Heap heap = heap_init(sizeof(struct heap_s) + 4 * sizeof(void*));
	CU_ASSERT(heap != NULL);
	
	void* active_pointer = heap->active_pointer;
	
	CU_ASSERT(active_pointer == heap_getActiveEnd(heap));
	
	heap_allocate_raw(heap, 4);
	
	CU_ASSERT(active_pointer != heap_getActiveEnd(heap));
	
	free(heap);
}

// --- MAIN ---

int main() {
	CU_pSuite pSuite1 = NULL;

	/* initialize the CUnit test registry */
	if(CUE_SUCCESS != CU_initialize_registry())
		return CU_get_error();

	/* add a suites to the registry */
	pSuite1 = CU_add_suite("Basic Functions Suite", init_suite_1, clean_suite_1);

	if(NULL == pSuite1) {
		CU_cleanup_registry();
		return CU_get_error();
	}

	/* add the tests to the suites */
	if (
		(NULL == CU_add_test(pSuite1, "test of heap_init()", testInit)) ||
		(NULL == CU_add_test(pSuite1, "test of heap_allocate_struct()", testAllocStruct)) ||
		(NULL == CU_add_test(pSuite1, "test of heap_allocate_raw()", testAllocRaw)) ||
		(NULL == CU_add_test(pSuite1, "test of heap_allocate_union()", testAllocUnion)) ||
		(NULL == CU_add_test(pSuite1, "test of heap_allocateActive()", testAllocateActive)) ||
		(NULL == CU_add_test(pSuite1, "test of heap_allocatePassive()", testAllocatePassive)) ||
		(NULL == CU_add_test(pSuite1, "test of heap_allocate()", testAllocate)) ||
		(NULL == CU_add_test(pSuite1, "test of heap_sizeLeft()", testSizeLeft)) ||
		(NULL == CU_add_test(pSuite1, "test of heap_copyFromActiveToPassive()", testCopyFromActiveToPassive)) ||
		(NULL == CU_add_test(pSuite1, "test of heap_markAsCopied()", testMarkAsCopied)) ||
		(NULL == CU_add_test(pSuite1, "test of heap_hasBeenCopied()", testHasBeenCopied)) ||
		(NULL == CU_add_test(pSuite1, "test of heap_swapActiveAndPassive()", testSwapActiveAndPassive)) ||
		(NULL == CU_add_test(pSuite1, "test of heap_getActiveStart()", testGetActiveStart)) ||
		(NULL == CU_add_test(pSuite1, "test of heap_getActiveEnd()", testGetActiveEnd))
	) {
		CU_cleanup_registry();
		return CU_get_error();
	}

	/* Run all tests using the CUnit Basic interface */
	CU_basic_set_mode(CU_BRM_VERBOSE);
	CU_basic_run_tests();
	CU_cleanup_registry();
	return CU_get_error();
}