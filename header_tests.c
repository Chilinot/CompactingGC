#include "header.h"
#include "CUnit/Basic.h"
#include <stdio.h>

// --- SUITES ---
int init_suite_1(void) {
	return 0;
}

int clean_suite_1(void) {
	return 0;
}

// --- UNIT TESTS ---

void testClearHeaderTypeBits() {
	void* x = (void*) 3;
	void* y = header_clearHeaderTypeBits(x);
	void* z = (void*) 0;
	
	CU_ASSERT(y == z);
	
	x = (void*) 7;
	y = header_clearHeaderTypeBits(x);
	z = (void*) 4;
	
	CU_ASSERT(y == z);
}

void testGetHeaderType() {
	void* header = (void*) 7;
	header_type type = header_getHeaderType(header);
	CU_ASSERT(type == BITVECTOR);
	
	header = (void*) 5;
	type = header_getHeaderType(header);
	CU_ASSERT(type == FORWARDING_ADDRESS);
	
	header = (void*) 22;
	type = header_getHeaderType(header);
	CU_ASSERT(type == FUNCTION_POINTER);
	
	header = (void*) 4;
	type = header_getHeaderType(header);
	CU_ASSERT(type == POINTER_TO_STRING);
}

void testForwardingAddress() {
	void* header = (void*) 4;
	void* new_header = header_forwardingAddress(header);
	CU_ASSERT(new_header == (void*) 5);
}

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
		(NULL == CU_add_test(pSuite1, "test of header_clearHeaderTypeBits()", testClearHeaderTypeBits)) ||
		(NULL == CU_add_test(pSuite1, "test of header_getHeaderType()", testGetHeaderType)) ||
		(NULL == CU_add_test(pSuite1, "test of header_forwardingAddress()", testForwardingAddress))
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