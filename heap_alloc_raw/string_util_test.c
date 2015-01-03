
#include "CUnit/Basic.h"
#include "string_util.h"
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int init_suite_2(void){
  return 0;
}

int clean_suite_2(void){
  return 0;
}

void testconcateFormatString() {
  char* headerString;
  char* star = "*";
  char* empty = "";
  char* r = "r";
  if(sizeof(void*) == 4){
    headerString = calloc(32, 4);
  }
  if(sizeof(void*) == 8){
    headerString = calloc(64, 8);
  }
  if(sizeof(void*) == 4){   
   
    char* test2 = concateFormatString(1, headerString, 4, star);
    CU_ASSERT(strcmp(test2, "*") == 0);
    
    free(headerString);
    headerString = calloc(32,4);
 
    char* test3 = concateFormatString(1, headerString, 0, empty);
    CU_ASSERT(strcmp(test3, "") == 0);
  

    char* test4 = concateFormatString(0, headerString, 0, star);
    CU_ASSERT(strcmp(test4, "") == 0);

    char* test5 = concateFormatString(3, headerString, 1, r);
    CU_ASSERT(strcmp(test5, "r") == 0);
    
    free(headerString);
    headerString = calloc(32,4);

    char* test6 = concateFormatString(3, headerString, 4, r);
    CU_ASSERT(strcmp(test6, "rrr") == 0);

    free(headerString);
  
  }
  if(sizeof(void*) == 8){
    char* test1 = concateFormatString(1, headerString, 8, star);
    CU_ASSERT(strcmp(test1, "*") == 0);
    free(headerString);
    headerString = calloc(32,4);

    char* test2 = concateFormatString(1, headerString, 0, empty);
    CU_ASSERT(strcmp(test2, "") == 0);
    
    char* test3 = concateFormatString(0, headerString, 0, star);
    CU_ASSERT(strcmp(test3, "") == 0);
 
    char* test4 = concateFormatString(7, headerString, 1, r);
    CU_ASSERT(strcmp(test4, "r") == 0);

    free(headerString);
    headerString = calloc(32,4);

    char* test5 = concateFormatString(3, headerString, 4, r);
    CU_ASSERT(strcmp(test5, "rr") == 0);

    free(headerString);
  }
}


void testreturnDigit() {

  char* layout = "2i3c1f*52l";

  int test1 = returnDigit(layout, 0);
  CU_ASSERT(test1 == 2);
  int test2 = returnDigit(layout, -1);
  CU_ASSERT(test2 == false);
  int test3 = returnDigit(layout, strlen(layout+1));
  CU_ASSERT(test3 == false);
  int test4 = returnDigit(layout, 3);
  CU_ASSERT(test4 == false);
  int test5 = returnDigit(layout, 7);
  CU_ASSERT(test5 == 52);
}

void testnewPos(){
  char* layout = "2i22c**l";
  int test1 = newPos(layout,0);
  CU_ASSERT(test1 == 1);
  int test2 = newPos(layout,-1);
  CU_ASSERT(test2 == -1);
  int test3 = newPos(layout, strlen(layout+1));
  CU_ASSERT(test3 == strlen(layout+1));
  int test4 = newPos(layout,2);
  CU_ASSERT(test4 == 4);
  int test5 = newPos(layout,5);
  CU_ASSERT(test5 == 5);


}

void testformatStringToHeaderString() {
  char* layout = "2i22c**l";
  char* layout1 = "";
  char* layout2 = "22";
  if(sizeof(void*)== 4){
    char* test1 = formatStringToHeaderString(layout);
    CU_ASSERT(strcmp(test1,"rrrrrrrr**r") == 0);
    char* test2 = formatStringToHeaderString(layout1);
    CU_ASSERT(strcmp(test2,"") == 0);
    char* test3 = formatStringToHeaderString(layout2);
    CU_ASSERT(strcmp(test3,"rrrrrr") == 0);

  }
  else{
    char* test1 = formatStringToHeaderString(layout);
    CU_ASSERT(strcmp(test1, "rrrrrrrr**rr") == 0);
    char* test2 = formatStringToHeaderString(layout1);
    CU_ASSERT(strcmp(test2,"") == 0);
    char* test3 = formatStringToHeaderString(layout2);
    CU_ASSERT(strcmp(test3,"rrrrrr") == 0);
  }
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

  if((NULL == CU_add_test(pSuite2, "testconcateFormatString", testconcateFormatString)) || (NULL == CU_add_test(pSuite2, "testreturnDigit", testreturnDigit))
     || (NULL == CU_add_test(pSuite2, "testnewPos", testnewPos))
     ||(NULL == CU_add_test(pSuite2, "testformatStringToHeaderString", testformatStringToHeaderString)))
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
