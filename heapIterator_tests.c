#include "CUnit/Basic.h"
#include "heap.h"
#include "heap_rep.h"
#include "heapIterator.h"
#include "header.h"

// --- SUITES ---
int init_suite_1(void) {
	return 0;
}

int clean_suite_1(void) {
	return 0;
}

typedef struct test_struct {
	int integer;
	struct test_struct* next_test_struct;
} *TestNode;

// --- UNIT TESTS ---
void testHeapIterator(void){
	Heap heap = heap_init(sizeof(struct heap_s) + 128 * sizeof(void*));
	
	// Allocate memory on the heap
	TestNode last = heap_allocate_struct(heap, "i*");
	TestNode middle = heap_allocate_struct(heap, "i*");
	TestNode first = heap_allocate_struct(heap, "i*");
	
	// Store values.
	first->integer = 12;
	first->next_test_struct = middle;
	
	middle->integer = 24;
	middle->next_test_struct = last;
	
	last->integer = 48;
	last->next_test_struct = NULL;
	
	// Make sure stored values are intact.
	CU_ASSERT(first->integer == 12);
	CU_ASSERT(first->next_test_struct != NULL);
	
	CU_ASSERT(middle->integer == 24);
	CU_ASSERT(middle->next_test_struct != NULL);
	
	CU_ASSERT(last->integer == 48);
	CU_ASSERT(last->next_test_struct == NULL);
	
	// Make sure all pointers are on the active part of the heap.
	CU_ASSERT(first > heap_getActiveStart(heap) && first < heap_getActiveEnd(heap));
	CU_ASSERT(middle > heap_getActiveStart(heap) && middle < heap_getActiveEnd(heap));
	CU_ASSERT(last > heap_getActiveStart(heap) && last < heap_getActiveEnd(heap));
	
	// Run heap iterator on the first object.
	TestNode new_first = heapIterator(heap, first);
	TestNode new_middle = new_first->next_test_struct;
	TestNode new_last = new_middle->next_test_struct;
	
	// Make sure values are still intact.
	CU_ASSERT(new_first->integer == 12);
	CU_ASSERT(new_middle->integer == 24);
	CU_ASSERT(new_last->integer == 48);
	
	// Make sure they are no longer on the active part of the heap.
	CU_ASSERT(!(new_first > heap_getActiveStart(heap) && new_first < heap_getActiveEnd(heap)));
	CU_ASSERT(!(new_middle > heap_getActiveStart(heap) && new_middle < heap_getActiveEnd(heap)));
	CU_ASSERT(!(new_last > heap_getActiveStart(heap) && new_last < heap_getActiveEnd(heap)));
	
	// Make sure the old objects are now forwarding addresses.
	HeapBlock first_block = GET_HEAPBLOCK(first);
	HeapBlock middle_block = GET_HEAPBLOCK(middle);
	HeapBlock last_block = GET_HEAPBLOCK(last);
	
	CU_ASSERT(header_getHeaderType(first_block->header) == FORWARDING_ADDRESS);
	CU_ASSERT(header_getHeaderType(middle_block->header) == FORWARDING_ADDRESS);
	CU_ASSERT(header_getHeaderType(last_block->header) == FORWARDING_ADDRESS);
	
	// Make sure the old objects are pointing to the correct new objects.
	CU_ASSERT(header_clearHeaderTypeBits(first_block->header) == new_first);
	CU_ASSERT(header_clearHeaderTypeBits(middle_block->header) == new_middle);
	CU_ASSERT(header_clearHeaderTypeBits(last_block->header) == new_last);
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
	if((NULL == CU_add_test(pSuite1, "test of heapIterator()", testHeapIterator))
	   
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
