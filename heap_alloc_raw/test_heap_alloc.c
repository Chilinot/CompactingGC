#include <string.h>
#include "CUnit/Basic.h"
#include "heap_alloc.c"
#include <stdlib.h>

int init_suite_2(void){
  return 0;
}

int clean_suite_2(void){
  return 0;
}

void testconcateFormatString(int value, char* concatedString, int size, char* rOrStar) {
  char* headerString;
  char* star = '*';
  if(sizeof(void*) == 4){
    headerString = calloc(32, 4);
  }
  if(sizeof(void*) == 8){
    headerString = calloc(64, 8);
  }
  char* value = concateFormatString(8, headerString, 8, star);

  printf("%s", value);

}



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

  if(
    (NULL == CU_add_test(pSuite2, "testconcateFormatString", testconcateFormatString)))
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
