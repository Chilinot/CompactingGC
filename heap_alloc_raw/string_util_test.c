
#include "CUnit/Basic.h"
#include "heap_alloc.h"
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int init_suite_2(void){
  return 0;
}

int clean_suite_2(void){
  return 0;
}

void testconcateFormatString(int value, char* concatedString, int size, char* rOrStar) {
  char* headerString;
  char* star = "*";
  char* empty = "";
  if(sizeof(void*) == 4){
    headerString = malloc(32* 4);
   
  }
  if(sizeof(void*) == 8){
    headerString = calloc(64, 8);
  }

  char* test1 = concateFormatString(8, headerString, 2, empty);
  CU_ASSERT(strcmp(test1, "") == 0);

  char* test2 = concateFormatString(4, headerString, 3, star);
  CU_ASSERT(strcmp(test2, "***") == 0);
  free(headerString);
}

/*
void testreturnDigit() {

  char* layout = "daa43af1";
  int test = returnDigit(layout, 5);
  printf("%d", test);
  CU_ASSERT(test == 1);
}
*/

int main()
{
  CU_pSuite pSuite2 = NULL;

  /* initialize the CUnit test registry */
  if (CUE_SUCCESS != CU_initialize_registry())
    return CU_get_error();

  pSuite2 = CU_add_suite("Advanced Functions Suite", init_suite_2, clean_suite_2);
  if (NULL == pSuite2)
    {
      CU_cleanup_registry();
      return CU_get_error();
    }

  if(NULL == CU_add_test(pSuite2, "testconcateFormatString", testconcateFormatString) /*||
     NULL == CU_add_test(pSuite2, "testReturnDigit", testreturnDigit)*/)
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
