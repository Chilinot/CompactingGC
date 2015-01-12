#include "header.h"
#include "CUnit/Basic.h"
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
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

	Heap heap = heap_init(sizeof(struct heap_s) + 256 * sizeof(void*));

	// -- TEST SMALL STRING - Always a bitvector.

	void* header = header_fromFormatString(heap, "*ii*");

	// Check type bits to make sure it is a bitvector.
	CU_ASSERT((((intptr_t) header) & 0b11) == 0b11);

	// Make sure the bits are in the right places.
	intptr_t bits = 0b11000011; // This is what "*ii*" terminator looks like in bits.

	// Shift and terminate bitvector.
	bits <<= 2;
	bits |= 0b01;

	// Shift all bits to the left so they are in the right places then mark it as a bitvector.
	bits <<= (sizeof(void*) * 8) - 10;
	bits |= 0b11;

	CU_ASSERT(header == (void*) bits);

	// -- TEST ARCHITECTURE DEPENDENT STRING, bitvector on 64-bit systems, pointer on 32-bit.

	char medium_string[28];

	for(int i = 0; i < 28; i++) {
		if(i == 26) {
			medium_string[i] = '*';
		}
		else {
			medium_string[i] = 'i';
		}
	}

	medium_string[27] = '\0';

	header = header_fromFormatString(heap, medium_string);

	if(sizeof(void*) == 4) {  // 32 bit system
		// Check if it is a pointer.
		CU_ASSERT((((intptr_t) header) & 0b11) == 0b00);
	}
	else if(sizeof(void*) == 8) {  // 64 bit system
		// Check if it is a bitvector.
		CU_ASSERT((((intptr_t) header) & 0b11) == 0b11);
	}
	else {
		CU_FAIL("Unit test missing for architecture!");
	}


	// -- TEST LARGE STRING - Always a pointer.

	// Constructs a string of 126 r's and 1 * as the last character.
	// How it looks: rrr...rr*
	char large_string[128];

	for(int i = 0; i < 128; i++) {
		if(i == 126) {
			large_string[i] = '*';
		}
		else {
			large_string[i] = 'i';
		}
	}

	// Null terminate the large string.
	large_string[127] = '\0';

	// Retrieve value to test.
	header = header_fromFormatString(heap, large_string);

	// Check type bits to make sure it is a string pointer.
	CU_ASSERT((((intptr_t) header) & 0b11) == 0b00);

	heap_del(heap);
}

void testObjectSpecificFunction() {
	//TODO fixa unittest för header_objectSpecificFunction().
}

void testGetSize() {
	Heap heap = heap_init(sizeof(struct heap_s) + 40 * sizeof(void*));

	// This assumes that header_fromFormatString() is working.
	void* header = header_fromFormatString(heap, "*ii*");

	int size = (sizeof(void*) * 2) + (sizeof(int) * 2);
	int header_size = header_getSize(header);

	CU_ASSERT(header_size == size);

	// 47 chars, should always return a string pointer not a vector.
	header = header_fromFormatString(heap, "iiiiiiiiiiiii**ii*ii***iii**ii**ii*i*i**iii*iii");
	size = (sizeof(void*) * 15) + (sizeof(int) * 32);

	CU_ASSERT(size == header_getSize(header));

	heap_del(heap);
}


void testPointerIterator() {

  //Heap heap = heap_init(sizeof(struct heap_s) + 40 * sizeof(void*));

	char* testString = "*rr**r*";

	void* pointersToBeFind[] = {(void*)(0 * sizeof(void*)  + 0 * sizeof(int)), // Xrr**r*
	                            (void*)(1 * sizeof(void*)  + 2 * sizeof(int)), // *rrX*r*
	                            (void*)(2 * sizeof(void*)  + 2 * sizeof(int)), // *rr*Xr*
	                            (void*)(3 * sizeof(void*)  + 3 * sizeof(int)) // *rr**rX
	                           };
	size_t pointersToBeFind_Length = sizeof(pointersToBeFind) / sizeof(pointersToBeFind[0]);
	bool pointerHasBeFound[pointersToBeFind_Length];

	for(int i = 0; i < pointersToBeFind_Length; i++) {
		pointerHasBeFound[i] = false;
	}


	void testfun(void * offset) {
		bool hasFoundAPointer = false;

		for(int i = 0; i < pointersToBeFind_Length; i++) {
			if(offset == pointersToBeFind[i]) {
				CU_ASSERT(pointerHasBeFound[i] == false); //check that the pointer has not already been found
				pointerHasBeFound[i] = true;
				CU_ASSERT(hasFoundAPointer == false);
				hasFoundAPointer = true;
			}
		}

		CU_ASSERT(hasFoundAPointer == true);
	};



	//clear pointerHasBeFound
	for(int i = 0; i < pointersToBeFind_Length; i++) { //clear pointerHasBeFound
		pointerHasBeFound[i] = false;
	}

	void* testHeader = sizeof(void*) == 4 ? 0b11000011110011010000000000000011 : 0b1100001111001101000000000000000000000000000000000000000000000011;
	header_pointerIterator(testHeader, &testfun);

	//Checks that all pointers have been found.
	for(int i = 0; i < pointersToBeFind_Length; i++) {
		CU_ASSERT(pointerHasBeFound[i] == true);
	}

	//clear pointerHasBeFound
	for(int i = 0; i < pointersToBeFind_Length; i++) {
		pointerHasBeFound[i] = false;
	}
	
        char* headerstring = calloc(sizeof(char), 200);
        while(((intptr_t)(headerstring)) % 4 != 0){
	  headerstring = headerstring+1;
	}
	strcpy(headerstring,testString);
	//testHeader = strdup(testString); //headerstring
	header_pointerIterator(testHeader, &testfun);
	//free(testHeader);

	//Checks that all pointers have been found.
	for(int i = 0; i < pointersToBeFind_Length; i++) {
		CU_ASSERT(pointerHasBeFound[i] == true); //check that
	}

	//heap_del(heap);
}

void testSetHeaderType() {
	char* foo = "foobar";
	void* header = header_forwardingAddress(&foo);
	header = header_clearHeaderTypeBits(header);
	
	header = header_setHeaderType(header, FORWARDING_ADDRESS);
	CU_ASSERT(header_getHeaderType(header) == FORWARDING_ADDRESS);
	
	header = header_setHeaderType(header, POINTER_TO_STRING);
	CU_ASSERT(header_getHeaderType(header) == POINTER_TO_STRING);
	
	header = header_setHeaderType(header, BITVECTOR);
	CU_ASSERT(header_getHeaderType(header) == BITVECTOR);
	
	header = header_setHeaderType(header, FUNCTION_POINTER);
	CU_ASSERT(header_getHeaderType(header) == FUNCTION_POINTER);
	
	// Make sure the actual value in the header has not been touched even after all of these changes to the type.
	header = header_clearHeaderTypeBits(header);
	CU_ASSERT(strcmp(foo, *((char**) header)) == 0);
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
	    (NULL == CU_add_test(pSuite1, "test of header_clearHeaderTypeBits()", testClearHeaderTypeBits)) ||
	    (NULL == CU_add_test(pSuite1, "test of header_getHeaderType()", testGetHeaderType)) ||
	    (NULL == CU_add_test(pSuite1, "test of header_forwardingAddress()", testForwardingAddress)) ||
	    (NULL == CU_add_test(pSuite1, "test of header_fromFormatString()", testFromFormatString)) ||
	    (NULL == CU_add_test(pSuite1, "test of header_objectSpecificFunction()", testObjectSpecificFunction)) ||
	    (NULL == CU_add_test(pSuite1, "test of header_getSize()", testGetSize)) ||
	    (NULL == CU_add_test(pSuite1, "test of header_pointerIterator()", testPointerIterator)) ||
	    (NULL == CU_add_test(pSuite1, "test of header_setType()", testSetHeaderType))
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
