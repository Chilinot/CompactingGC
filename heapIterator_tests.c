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


// --- MAIN ---

int main() {
	CU_pSuite pSuite1 = NULL;
	
	/* initialize the CUnit test registry */
	if (CUE_SUCCESS != CU_initialize_registry())
		return CU_get_error();
	
	/* add a suites to the registry */
	pSuite1 = CU_add_suite("Basic Functions Suite", init_suite_1, clean_suite_1);
	if (NULL == pSuite1) {
		CU_cleanup_registry();
		return CU_get_error();
	}
	
	/* add the tests to the suites */
	if (
		
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