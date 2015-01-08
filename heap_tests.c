#include "CUnit/Basic.h"
#include "heap.h"
#include "heap_rep.h"
#include "header.h"

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
	
	CU_ASSERT(strcmp(foo, "foo") == 0);
	
	char* bar = heap_copyFromActiveToPassive(heap, (void*) foo);
	
	CU_ASSERT(strcmp(foo, bar) == 0);
	
	printf("\nfoo: %s\n", foo);
	printf("bar: %s\n", bar);
	
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
// 		(NULL == CU_add_test(pSuite1, "test of heap_allocate()", testAllocate)) ||
		(NULL == CU_add_test(pSuite1, "test of heap_sizeLeft()", testSizeLeft)) ||
		(NULL == CU_add_test(pSuite1, "test of heap_copyFromActiveToPassive()", testCopyFromActiveToPassive))
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
