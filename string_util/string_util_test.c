#include "CUnit/Basic.h"
#include "string_util.h"
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>


#ifdef __sparc__
int SPARC = 1;
#else
int SPARC = 0;
#endif


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
  headerString = calloc(100, 1);
  if(sizeof(void*) == 4){   
    int bit32 = 0;
    int bit64 = 1;
    char* test2 = concateFormatString(1, headerString, 4, star, bit32);
    CU_ASSERT(strcmp(test2, "*") == 0);
    
    free(headerString);
    headerString = calloc(32,4);
 
    char* test3 = concateFormatString(1, headerString, 0, empty, bit32);
    CU_ASSERT(strcmp(test3, "") == 0);
  

    char* test4 = concateFormatString(0, headerString, 4, star, bit32);
    CU_ASSERT(strcmp(test4, "") == 0);

    char* test5 = concateFormatString(3, headerString, 1, r, bit32);
    CU_ASSERT(strcmp(test5, "r") == 0);
    
    free(headerString);
    headerString = calloc(32,4);

    char* test6 = concateFormatString(3, headerString, 4, r, bit32);
    CU_ASSERT(strcmp(test6, "rrr") == 0);

    /*tests for the SPARC */
    
    if(SPARC == 1){
    char* test7 = concateFormatString(1, headerString, 4, star, bit64);
    CU_ASSERT(strcmp(test7,"*") == 0);
    
    char* test8 = concateFormatString(1, headerString, 0, empty, bit64);
    CU_ASSERT(strcmp(test8, "") == 0);
    
    char* test9 = concateFormatString(0, headerString, 4, star, bit64);
    CU_ASSERT(strcmp(test9, "") == 0);
    
    char* test10 = concateFormatString(3, headerString, 1, r, bit64);
    CU_ASSERT(strcmp(test10, "rr") == 0);
    
    char* test11 = concateFormatString(3, headerString, 4, r, bit64);
    CU_ASSERT(strcmp(test11, "rrrr") == 0);
    }
    
    free(headerString);
    

  
  }

  if(sizeof(void*) == 8){
    int bit64 = 1;
    char* test1 = concateFormatString(1, headerString, 8, star, bit64);
    CU_ASSERT(strcmp(test1, "*") == 0);
    free(headerString);
    headerString = calloc(32,4);

    char* test2 = concateFormatString(1, headerString, 0, empty, bit64);
    CU_ASSERT(strcmp(test2, "") == 0);
    
    char* test3 = concateFormatString(0, headerString, 8, star, bit64);
    CU_ASSERT(strcmp(test3, "") == 0);
 
    char* test4 = concateFormatString(7, headerString, 1, r, bit64);
    CU_ASSERT(strcmp(test4, "rr") == 0);

    free(headerString);
    headerString = calloc(32,4);

    char* test5 = concateFormatString(3, headerString, 4, r, bit64);
    CU_ASSERT(strcmp(test5, "rrrr") == 0);

    free(headerString);
  }
}


void testreturnDigit() {

  char* layout = "2i3c1f*52l";

  int test1 = returnDigit(layout, 0);
  CU_ASSERT(test1 == 2);
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
  char* layout3 = "ici";
  char* layout4 = "cdc";
  char* layout5 = "icc*c";
  char* layout6 = "5c2*";
  char* layout7 = "cic";

  char* Alfa = "lic*";

  struct a{
    long a;
    int b;
    char c;
    void* d;
  }alfa;

  char* Beta = "cfic";

  struct b{
    char a;
    float b;
    int c;
    char d;
  }beta;

  if(sizeof(void*) == 4 && SPARC == 1){ //tests for the sparc
    char* test1 = formatStringToHeaderString(layout);
    CU_ASSERT(strcmp(test1,"rrrrrrrr**r") == 0);
    char* test2 = formatStringToHeaderString(layout1);  
    CU_ASSERT(strcmp(test2,"") == 0);
    char* test3 = formatStringToHeaderString(layout2);
    CU_ASSERT(strcmp(test3,"rrrrr") == 0);
    char* test4 = formatStringToHeaderString(layout3);
    CU_ASSERT(strcmp(test4, "rrr") == 0);
    char* test5 = formatStringToHeaderString(layout4);
    CU_ASSERT(strcmp(test5, "rrrrrr") == 0);
    char* test6 = formatStringToHeaderString(layout5);
    CU_ASSERT(strcmp(test6, "rr*r") == 0);
    char* test7 = formatStringToHeaderString(layout6);
    CU_ASSERT(strcmp(test7, "rr**") == 0);
    char* test8 = formatStringToHeaderString(layout7);
    CU_ASSERT(strcmp(test8, "rrr") == 0);
      
    char* test9 = formatStringToHeaderString(Alfa);
    CU_ASSERT(headerStringToSize(test9) == sizeof(alfa));

    char* test10 = formatStringToHeaderString(Beta);
    CU_ASSERT(headerStringToSize(test10) == sizeof(beta));
    free(test1);
    free(test2);
    free(test3);
    free(test4);
    free(test5);
    free(test6);
    free(test7);
    free(test8);
    free(test9);
    free(test10);
  }
  
  /*
  char* layout = "2i22c**l";
  char* layout1 = "";
  char* layout2 = "22";
  char* layout3 = "ici";
  char* layout4 = "cdc";
  char* layout5 = "icc*c";
  char* layout6 = "5c2*";
  char* layout7 = "cic";
  */

  if(sizeof(void*) == 8){ //tests for linux 64-bit
    char* test1 = formatStringToHeaderString(layout);
    printf("\n%s\n", test1);
    CU_ASSERT(strcmp(test1,"rrrrrrrr**rr") == 0);
    char* test2 = formatStringToHeaderString(layout1);
    CU_ASSERT(strcmp(test2,"") == 0);
    char* test3 = formatStringToHeaderString(layout2);
    CU_ASSERT(strcmp(test3,"rrrrrr") == 0);
    char* test4 = formatStringToHeaderString(layout3);
    CU_ASSERT(strcmp(test4, "rrr") == 0);
    char* test5 = formatStringToHeaderString(layout4);
    CU_ASSERT(strcmp(test5, "rrrrrr") == 0);
    char* test6 = formatStringToHeaderString(layout5);
    printf("\n%s\n", test6);    
    CU_ASSERT(strcmp(test6, "rr*rr") == 0);
    char* test7 = formatStringToHeaderString(layout6);
    printf("\n%s\n", test7);
    CU_ASSERT(strcmp(test7, "rr**") == 0);
    char* test8 = formatStringToHeaderString(layout7);
    CU_ASSERT(strcmp(test8, "rrr") == 0);

    char* test9 = formatStringToHeaderString(Alfa);
    CU_ASSERT(headerStringToSize(test9) == sizeof(alfa));
    
    char* test10 = formatStringToHeaderString(Beta);
    CU_ASSERT(headerStringToSize(test10) == sizeof(beta));
    
    free(test1);
    free(test2);
    free(test3);
    free(test4);
    free(test5);
    free(test6);
    free(test7);
    free(test8);
    free(test9);
    free(test10);

  }
  if(sizeof(void*) == 4 && SPARC == 0){ // test for solars 32-bit
    char* test1 = formatStringToHeaderString(layout);
    CU_ASSERT(strcmp(test1, "rrrrrrrr**rr") == 0);
    char* test2 = formatStringToHeaderString(layout1);
    CU_ASSERT(strcmp(test2,"") == 0);
    char* test3 = formatStringToHeaderString(layout2);
    CU_ASSERT(strcmp(test3,"rrrrrr") == 0);
    char* test4 = formatStringToHeaderString(layout3);
    CU_ASSERT(strcmp(test4, "rrrr") == 0);
    char* test5 = formatStringToHeaderString(layout4);
    CU_ASSERT(strcmp(test5, "rrrr") == 0);
    char* test6 = formatStringToHeaderString(layout5);
    CU_ASSERT(strcmp(test6, "rr*r") == 0);
    char* test7 = formatStringToHeaderString(layout6);
    CU_ASSERT(strcmp(test7, "rr**") == 0);
    char* test8 = formatStringToHeaderString(layout7);
    CU_ASSERT(strcmp(test8, "rrr") == 0);
    
    char* test9 = formatStringToHeaderString(Alfa);
    CU_ASSERT(headerStringToSize(test9) == sizeof(alfa));

    char* test10 = formatStringToHeaderString(Beta);
    CU_ASSERT(headerStringToSize(test10) == sizeof(beta));

    free(test1);
    free(test2);
    free(test3);
    free(test4);
    free(test5);
    free(test6);
    free(test7);
    free(test8);
    free(test9);
    free(test10);    
  } 
}

int main(){
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
