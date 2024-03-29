#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <setjmp.h>
#include <assert.h>
#include <stdint.h>
#include "CUnit/Basic.h"
#include "../src/stack.h"


int init_suite1(void) {
	return 0;
}

int clean_suite1(void) {
	return 0;
}


void testSTACKITERATOR(void) {
	int count = 0;
	void testfun(void** pointer) {
		count++;
		*pointer = NULL;
	}
	size_t isize = 320;
	void* myHeap = malloc(isize * sizeof(void*));
	void* alpha = myHeap + 4;
	void* beta = myHeap + 23;
	count = 0;
	stackIterator((void*)myHeap , (void*)myHeap + isize, &testfun);
	CU_ASSERT(2 == count);
	CU_ASSERT(alpha == NULL);
	CU_ASSERT(beta == NULL);
	free(myHeap);
}


/* The main() function for setting up and running the tests.
 * Returns a CUE_SUCCESS on successful running, another
 * CUnit error code on failure.
 */
int main() {
	CU_pSuite pSuite = NULL;

	/* initialize the CUnit test registry */
	if(CUE_SUCCESS != CU_initialize_registry())
		return CU_get_error();

	/* add a suite to the registry */
	pSuite = CU_add_suite("Suite_1", init_suite1, clean_suite1);

	if(NULL == pSuite) {
		CU_cleanup_registry();
		return CU_get_error();
	}

	/* add the tests to the suite */
	if((NULL == CU_add_test(pSuite, "test of stackIterator()", testSTACKITERATOR))) {
		CU_cleanup_registry();
		return CU_get_error();
	}

	/* Run all tests using the CUnit Basic interface */
	CU_basic_set_mode(CU_BRM_VERBOSE);
	CU_basic_run_tests();
	CU_cleanup_registry();
	return CU_get_error();
}

