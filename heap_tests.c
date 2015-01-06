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

testInit() {
	// Test with not enough memory space.
	Heap heap = heap_init(1);
	CU_ASSERT(heap == NULL);

	// Test with exactly enough space to fit structure.
	heap = heap_init(sizeof(struct heap_s));
	CU_ASSERT(heap == NULL);

	// Test with enough space.
	heap = heap_init(sizeof(struct heap_s) + 10);
	CU_ASSERT(heap != NULL);

	free(heap);
}

testGetGrowthDirection() {

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
	if(
	    (NULL == CU_add_test(pSuite1, "test of heap_init()", testInit)) ||
	    (NULL == CU_add_test(pSuite1, "test of heap_getGrowthDirection()", testGetGrowthDirection))
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
