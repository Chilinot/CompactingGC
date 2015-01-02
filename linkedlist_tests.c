#include "linkedlist.h"
#include "CUnit/Basic.h"
#include <stdlib.h>

// --- SUITES ---
int init_suite_1(void) {
	return 0;
}

int clean_suite_1(void) {
	return 0;
}

// --- UNIT TESTS ---

void testAdd() {
	int foo = 12;
	LinkedList list = add(NULL, &foo);
	CU_ASSERT(list != NULL);
	CU_ASSERT(*(int*)list->data == 12);
	CU_ASSERT(list->next == NULL);
	
	list = add(list, &foo);
	CU_ASSERT(list != NULL);
	CU_ASSERT(*(int*)list->data == 12);
	CU_ASSERT(list->next != NULL);
	
	LinkedList next_list = list->next;
	CU_ASSERT(next_list->next == NULL);
	CU_ASSERT(*(int*)next_list->data == 12);
	
	free(list);
	free(next_list);
}

void testExamineHead() {
	LinkedList list = malloc(sizeof(struct _linkedlist));
	int foo = 12;
	list->data = &foo;
	list->next = NULL;
	
	int* bar = examine_head(list);
	CU_ASSERT(*bar == 12);
	
	free(list);
}

void testRemoveHead() {
	LinkedList first = malloc(sizeof(struct _linkedlist));
	LinkedList second = malloc(sizeof(struct _linkedlist));
	
	first->next = second;
	
	LinkedList next = remove_head(first);
	
	CU_ASSERT(next == second);
	
	free(second);
}

void testDestroyList() {
	// This can not be tested with CUnit, this method can only be tested with valgrind.
	// If valgrind reports no memory leaks when this method has run its course then the method works.
	
	LinkedList first = malloc(sizeof(struct _linkedlist));
	LinkedList second = malloc(sizeof(struct _linkedlist));
	
	first->next = second;
	second->next = NULL;
	
	destroy_list(first);
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
		(NULL == CU_add_test(pSuite1, "test of add()", testAdd)) ||
		(NULL == CU_add_test(pSuite1, "test of examine_head()", testExamineHead)) ||
		(NULL == CU_add_test(pSuite1, "test of remove_head()", testRemoveHead)) ||
		(NULL == CU_add_test(pSuite1, "test of destroy_list()", testDestroyList))
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