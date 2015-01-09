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
  if(sizeof(void*) == 4){
    headerString = calloc(32, 4);
  }
  if(sizeof(void*) == 8){
    headerString = calloc(64, 8);
  }
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
  char* layout8 = "8c2i**";
  char* layout9 = "9c2i**";
  char* layout10 = "ii**";
  char* layout11 = "iii**";
  char* layout12 = "3i**";
  char* layout13 = "*iii";
  char* layout14 = "cci*";
  char* layout15 = "*ci";
  char* layout16 = "*cccccci";
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
    free(test1);
    char* test2 = formatStringToHeaderString(layout1);
    CU_ASSERT(strcmp(test2,"") == 0);
    free(test2);
    char* test3 = formatStringToHeaderString(layout2);
    CU_ASSERT(strcmp(test3,"rrrrr") == 0);
    free(test3);
    char* test4 = formatStringToHeaderString(layout3);
    CU_ASSERT(strcmp(test4, "rrr") == 0);
    free(test4);
    char* test5 = formatStringToHeaderString(layout4);
    CU_ASSERT(strcmp(test5, "rrrrrr") == 0);
    free(test5);
    char* test6 = formatStringToHeaderString(layout5);
    CU_ASSERT(strcmp(test6, "rr*r") == 0);
    free(test6);
    char* test7 = formatStringToHeaderString(layout6);
    CU_ASSERT(strcmp(test7, "rr**") == 0);
    free(test7);
    char* test8 = formatStringToHeaderString(layout7);
    CU_ASSERT(strcmp(test8, "rrr") == 0);
    free(8);
    char* test9 = formatStringToHeaderString(Alfa);
    CU_ASSERT(headerStringToSize(test9) == sizeof(alfa));
    free(test9);
    char* test10 = formatStringToHeaderString(Beta);
    CU_ASSERT(headerStringToSize(test10) == sizeof(beta));
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
    char* layout8 = "8c2i**";
    char* layout9 = "9c2i**";
    char* layout10 = "ii**";
    char* layout11 = "iii**";
    char* layout12 = "3i**";
    char* layout13 = "*iii";
    char* layout14 = "cci*";
    char* layout15 = "*ci";
    char* layout16 = "*cccccci";
    - */
  if(sizeof(void*) == 8){ //tests for linux 64-bit
    puts("hej/n");
    char* test1 = formatStringToHeaderString(layout);
    CU_ASSERT(strcmp(test1,"rrrrrrrr**rr") == 0);
    free(test1);
    char* test2 = formatStringToHeaderString(layout1);
    CU_ASSERT(strcmp(test2,"") == 0);
    free(test2);
    char* test3 = formatStringToHeaderString(layout2);
    CU_ASSERT(strcmp(test3,"rrrrrr") == 0);
    free(test3);
    char* test4 = formatStringToHeaderString(layout3);
    CU_ASSERT(strcmp(test4, "rrr") == 0);
    free(test4);
    char* test5 = formatStringToHeaderString(layout4);
    CU_ASSERT(strcmp(test5, "rrrrrr") == 0);
    free(test5);
    char* test6 = formatStringToHeaderString(layout5);
    CU_ASSERT(strcmp(test6, "rr*rr") == 0);
    free(test6);
    char* test7 = formatStringToHeaderString(layout6);
    CU_ASSERT(strcmp(test7, "rr**") == 0);
    free(test7);
    char* test8 = formatStringToHeaderString(layout7);
    CU_ASSERT(strcmp(test8, "rrr") == 0);
    free(test8);
    char* test9 = formatStringToHeaderString(Alfa);
    CU_ASSERT(headerStringToSize(test9) == sizeof(alfa));
    free(test9);
    char* test10 = formatStringToHeaderString(Beta);
    CU_ASSERT(headerStringToSize(test10) == sizeof(beta));
    free(test10);
    /*
      char* layout8 = "8c2i**";
      char* layout9 = "9c2i**";
      char* layout10 = "ii**";
      char* layout11 = "iii**";
      char* layout12 = "3i**";
      char* layout13 = "*iii";
      char* layout14 = "cci*";
      char* layout15 = "*ci";
      char* layout16 = "*cccccci";
    */
    char* test11 = formatStringToHeaderString(layout8);
    CU_ASSERT(strcmp(test11,"rrrr**") == 0);
    free(test11);
    char* test12 = formatStringToHeaderString(layout9);
    CU_ASSERT(strcmp(test12,"rrrrrr**") == 0);
    free(test12);
    char* test13 = formatStringToHeaderString(layout10);
    CU_ASSERT(strcmp(test13,"rr**") == 0);
    free(test13);
    char* test14 = formatStringToHeaderString(layout11);
    CU_ASSERT(strcmp(test14,"rrrr**") == 0);
    free(test14);
    char* test15 = formatStringToHeaderString(layout12);
    CU_ASSERT(strcmp(test15,"rrrr**") == 0);
    free(test15);
    char* test16 = formatStringToHeaderString(layout13);
    CU_ASSERT(strcmp(test16,"*rrrr") == 0);
    free(test6);
    char* test17 = formatStringToHeaderString(layout14);
    CU_ASSERT(strcmp(test17,"rr*") == 0);
    free(test17);
    char* test18 = formatStringToHeaderString(layout15);
    CU_ASSERT(strcmp(test18,"*rr") == 0);
    free(test18);
    char* test19 = formatStringToHeaderString(layout16);
    CU_ASSERT(strcmp(test19,"*rrrr") == 0);
    free(test19);
  }
  if(sizeof(void*) == 4 && SPARC != SPARC){ //test for solars 32-bit
    char* test1 = formatStringToHeaderString(layout);
    CU_ASSERT(strcmp(test1, "rrrrrrrr**rr") == 0);
	free(test1);
    char* test2 = formatStringToHeaderString(layout1);
    CU_ASSERT(strcmp(test2,"") == 0);
	free(test2);
    char* test3 = formatStringToHeaderString(layout2);
    CU_ASSERT(strcmp(test3,"rrrrrr") == 0);
	free(test3);
    char* test4 = formatStringToHeaderString(layout3);
    CU_ASSERT(strcmp(test4, "rrrr") == 0);
	free(test4);
    char* test5 = formatStringToHeaderString(layout4);
    CU_ASSERT(strcmp(test5, "rrrr") == 0);
	free(test5);
    char* test6 = formatStringToHeaderString(layout5);
    CU_ASSERT(strcmp(test6, "rr*r") == 0);
	free(test6);
    char* test7 = formatStringToHeaderString(layout6);
    CU_ASSERT(strcmp(test7, "rr**") == 0);
	free(test7);
    char* test8 = formatStringToHeaderString(layout7);
    CU_ASSERT(strcmp(test8, "rrr") == 0);
	free(test8);
    char* test9 = formatStringToHeaderString(Alfa);
    CU_ASSERT(headerStringToSize(test9) == sizeof(alfa));
	free(test9);
    char* test10 = formatStringToHeaderString(Beta);
    CU_ASSERT(headerStringToSize(test10) == sizeof(beta));
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
