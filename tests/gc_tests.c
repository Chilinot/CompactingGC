#include "CUnit/Basic.h"
#include "../src/gc.h"
#include "../src/heap.h"
#include "../src/header.h"
#include "../src/stack.h"
#include "../src/heapIterator.h"
#include "../src/string_util.h"



#ifdef HEAP_TESTS_DEBUG
#include "debug.h"
#endif


int init_suite_1(void) {
	return 0;
}

int clean_suite_1(void) {
	return 0;
}

void testh_gc() {
  Heap heap;
  heap = h_init(sizeof(struct heap_s) + 140*sizeof(void*));

  heap_allocate_struct(heap, "*ii*");
  heap_allocate_struct(heap, "*****");
  h_gc(heap);
  CU_ASSERT(h_avail(heap) == 280);
  void* a = heap_allocate_struct(heap, "*ii*");
  void* b = heap_allocate_struct(heap, "*****");
  int bytesAvailable = h_avail(heap);
  heap_allocate_struct(heap, "*****");
  heap_allocate_struct(heap, "*c*d*");
  CU_ASSERT(h_avail(heap) < bytesAvailable);
  h_gc(heap);
  CU_ASSERT(h_avail(heap) == bytesAvailable);
}









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
	   (NULL == CU_add_test(pSuite1, "test of h_gc", testh_gc)))
	{
		CU_cleanup_registry();
		return CU_get_error();
	}

	/* Run all tests using the CUnit Basic interface */
	CU_basic_set_mode(CU_BRM_VERBOSE);
	CU_basic_run_tests();
	CU_cleanup_registry();
	return CU_get_error();
}
