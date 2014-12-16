#include "header.h"
#include "CUnit/Basic.h"
#include <stdio.h>
#include <stdint.h>

// --- SUITES ---
int init_suite_1(void) {
	return 0;
}

int clean_suite_1(void) {
	return 0;
}

// --- UNIT TESTS ---

void testClearHeaderTypeBits() {
	void* x = (void*) 0b11;
	void* y = header_clearHeaderTypeBits(x);
	void* z = (void*) 0b00;
	
	CU_ASSERT(y == z);
	
	x = (void*) 0b111;
	y = header_clearHeaderTypeBits(x);
	z = (void*) 0b100;
	
	CU_ASSERT(y == z);
}

void testGetHeaderType() {
	void* header = (void*) 0b1011;
	header_type type = header_getHeaderType(header);
	CU_ASSERT(type == BITVECTOR);
	
	header = (void*) 0b0101;
	type = header_getHeaderType(header);
	CU_ASSERT(type == FORWARDING_ADDRESS);
	
	header = (void*) 0b1110;
	type = header_getHeaderType(header);
	CU_ASSERT(type == FUNCTION_POINTER);
	
	header = (void*) 0b1100;
	type = header_getHeaderType(header);
	CU_ASSERT(type == POINTER_TO_STRING);
}

void testForwardingAddress() {
	void* header = (void*) 4;
	void* new_header = header_forwardingAddress(header);
	CU_ASSERT(new_header == (void*) 5);
}

void testFromFormatString() {
	void* header = header_fromFormatString("*rr*");
	
	// Check type bits to make sure it is a bitvector.
	CU_ASSERT((((intptr_t) header) & 0b11) == 0b11);
	
	// Make sure the bits are in the right places.
	void* bits = (void*) ((((intptr_t) 0b1001) << ((sizeof(void*) * 8) - 4)) | 3);
	CU_ASSERT(header == bits);
	
	// Constructs a string of 126 r's and 1 * as the last character.
	// How it looks: rrr...rr*
	char large_string[128];
	for(int i = 0; i < 128; i++) {
		if(i == 126) {
			large_string[i] = '*';
		}
		else {
			large_string[i] = 'r';
		}
	}
	
	// Null terminate the large string.
	large_string[127] = '\0';
	
	// Retrieve value to test.
	header = header_fromFormatString(large_string);
	
	// Check type bits to make sure it is a string pointer.
	CU_ASSERT((((intptr_t) header) & 0b11) == 0b00);
	
	// Clear the type bits.
	header = (void*) (((intptr_t) header) & ~0b11);
	
	CU_ASSERT(strcmp(large_string, (char*) header) == 0);
	
	free(header);
}

void testObjectSpecificFunction() {
	
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
		(NULL == CU_add_test(pSuite1, "test of header_forwardingAddress()", testForwardingAddress)) ||
		(NULL == CU_add_test(pSuite1, "test of header_fromFormatString()", testFromFormatString)) ||
		(NULL == CU_add_test(pSuite1, "test of header_objectSpecificFunction()", testObjectSpecificFunction))
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