#include "CUnit/Basic.h"
#include "heap.h"
#include "heap_rep.h"

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
	heap = heap_init(sizeof(struct heap_s) + 2 * sizeof(void*));
	CU_ASSERT(heap != NULL);

	free(heap);
}

void testDel() {
	//This method can only be tested with valgrind.
}

void testAllocStruct() {
	Heap heap = heap_init(sizeof(struct heap_s) + 4 * sizeof(void*));
	CU_ASSERT(heap != NULL);
	
	void* foo = heap_allocate_struct(heap, "r");
	void* bar = heap_allocate_struct(heap, "r");
	
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
		(NULL == CU_add_test(pSuite1, "test of heap_allocate_union()", testAllocUnion))
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
