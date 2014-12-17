#include <string.h>
#include "CUnit/Basic.h"
#include "istring.h"
#include "istring_rep.h"
#include <stdlib.h>




int init_suite_1(void)
{
  return 0;
}

int clean_suite_1(void)
{
  return 0;
}

int init_suite_2(void)
{
  return 0;
}

int clean_suite_2(void)
{
  return 0;
}



void testStackIterator(){
  void testStackIteratorFun1(void**)
  

}

void testISTRING_MK(void)
{
  char *str1 = istring_mk(NULL);
  CU_ASSERT(str1 == NULL);
  char str2[] = "foo";
  char *str3 = istring_mk(str2);
  CU_ASSERT(strlen(str3) == strlen(str2));
  CU_ASSERT(strcmp(str2, str3)  == 0);
  CU_ASSERT(str3[0]  == 'f');
  CU_ASSERT(str3[1]  == 'o');
  CU_ASSERT(str3[2]  == 'o');
  CU_ASSERT(str3[3]  == '\0');
  str3[0]  = 'F';
  CU_ASSERT(strcmp(str2, str3) > 0);
  istring_rm(str1);
  istring_rm(str3);
}

void testISTRING_RM(void)
{
  istring_rm(istring_mk("test"));
}

void testISTRFIXLEN(void)
{
  char *foolnbar = istring_mk("foo\nbar");
  char *foolnbarnfix = istring_mk("foo\nbar");
  printf("istrfixlen(foolnbar) = %u \n", istrfixlen(foolnbar));
  
  CU_ASSERT(istrlen(foolnbar) == 7);
  CU_ASSERT(7 == istrlen(foolnbarnfix));
  CU_ASSERT(7 == 7);
  CU_ASSERT((istrlen(foolnbar)) == (istrlen(foolnbarnfix)));
  
}

void testISTRLEN(void)
{
  char *str1 = istring_mk("spam");
  char *str2 = istring_mk("ekieki");
  CU_ASSERT(istrlen(str1) == 4);
  CU_ASSERT(istrlen(str2) == 6);
  START(str2)->length = (uint32_t) (3);
  CU_ASSERT(istrlen(str2) == 3);
  CU_ASSERT(strlen(str2) == 6);
  istring_rm(str1);
  istring_rm(str2);
}

void testISTRING_TO_STRING(void)
{
  char *str1 = istring_mk("spam");
  CU_ASSERT(strcmp(istring_to_string(str1), "spam") == 0);
  istring_rm(str1);
}


void testISTRCAT(void)
{
  // You must implement you own!
  char *str1 = istring_mk("foo");
  char *str2 = istring_mk("bar");
  char *str3 = istring_mk("");
  char *catstr = istrcat(str1, str2);
  CU_ASSERT(strcmp(catstr, "foobar") == 0);
  CU_ASSERT(START(catstr)->length == ((uint32_t) 6));
  CU_ASSERT(catstr[6] == '\0');
  
  //lägg till för str3

  istring_rm(str1);
  //CU_FAIL("Test not implemented yet");
}

void testISTRNCAT(void)
{
  // You must implement you own!
  CU_FAIL("Test not implemented yet");
}

void testISTRCHR(void)
{
  char *str = istring_mk("spam spam bacon spam");
  CU_ASSERT(istrchr(str, 's') == str);
  CU_ASSERT(istrchr(str, 'b') == str + 10);
  CU_ASSERT(istrchr(str, 'c') == str + 12);
  CU_ASSERT(istrchr(str, 's') == str);
  CU_ASSERT(istrchr(str, '\0') == str + 20);
  CU_ASSERT(istrchr(str, 'x') == NULL);
  istring_rm(str);
}

void testISTRRCHR(void)
{
  char *str = istring_mk("spam spam bacon spam");
  CU_ASSERT(istrrchr(str, 's') == str + 16);
  CU_ASSERT(istrrchr(str, 'b') == str + 10);
  CU_ASSERT(istrrchr(str, 'c') == str + 12);
  CU_ASSERT(istrrchr(str, 's') == str + 16);
  CU_ASSERT(istrrchr(str, '\0') == str + 20);
  CU_ASSERT(istrrchr(str, 'x') == NULL);
  istring_rm(str);
}

void testISTRCMP(void)
{
  char *str1 = istring_mk("spam");
  char *str2 = istring_mk("spam");
  char *str3 = istring_mk("Spam");
  CU_ASSERT(istrcmp(str1, str1) == 0);
  CU_ASSERT(istrcmp(str1, str2) == 0);
  CU_ASSERT(istrcmp(str2, str3) > 0);
  CU_ASSERT(istrcmp(str3, str2) < 0);
  istring_rm(str1);
  istring_rm(str2);
  istring_rm(str3);
}

void testISTRNCMP(void)
{
  char *str1 = istring_mk("spam ");
  char *str2 = istring_mk("spam");
  char *str3 = istring_mk("Spam");
  CU_ASSERT(istrncmp(str1, str2, 4) == 0);
  CU_ASSERT(istrncmp(str1, str2, 5) > 0);
  CU_ASSERT(istrncmp(str2, str3, 4) > 0);
  CU_ASSERT(istrncmp(str3, str2, 4) < 0);
  istring_rm(str1);
  istring_rm(str2);
  istring_rm(str3);
}

void testISTRCPY(void)
{
  char dst[50];
  char *str1 = istring_mk("test string example");
  char *dst2 = istrcpy(dst, str1);
  CU_ASSERT(dst2 == STRING(dst))
  CU_ASSERT(dst2 != str1);
  CU_ASSERT(strcmp(dst2,str1) == 0);
  CU_ASSERT(START(dst2)->length == START(str1)->length);
  istring_rm(str1);
}

void testISTRNCPY(void)
{
  char dest1[50];
  char dest2[50];
  memset(dest2, 'a', 50);
  char *str1 = istring_mk("test string example");
  char *str2 = istring_mk("foo");
  char *dst1 = istrncpy(dest1, str1,11);
  char *dst2 = istrncpy(dest2, str2, 10);
  CU_ASSERT(dst1 == STRING(dest1));
  CU_ASSERT(dst1 != str1);
  CU_ASSERT(strncmp(dst1,str1,11) == 0);
  CU_ASSERT(START(dst1)->length == 11);

  CU_ASSERT(dst2 == STRING(dest2))
  CU_ASSERT(dst2 != str2);
  char *cmpdst2 = {'f', 'o', 'o', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', 'a', 'a'};
  CU_ASSERT(memcmp(dst2,cmpdst2,13) == 0);
  CU_ASSERT(START(dst2)->length == 3);

  istring_rm(str1);
  istring_rm(str2);
}

int main()
{
  CU_pSuite pSuite1 = NULL;
  CU_pSuite pSuite2 = NULL;
  
  /* initialize the CUnit test registry */
  if (CUE_SUCCESS != CU_initialize_registry())
    return CU_get_error();

  /* add a suites to the registry */
  pSuite1 = CU_add_suite("Basic Functions Suite", init_suite_1, clean_suite_1);
  if (NULL == pSuite1)
    {
      CU_cleanup_registry();
      return CU_get_error();
    }
  pSuite2 = CU_add_suite("Advanced Functions Suite", init_suite_2, clean_suite_2);
  if (NULL == pSuite2)
    {
      CU_cleanup_registry();
      return CU_get_error();
    }

  /* add the tests to the suites */
  if (
    (NULL == CU_add_test(pSuite1, "test of istring_mk()", testISTRING_MK)) ||
    (NULL == CU_add_test(pSuite1, "test of istring_rm()", testISTRING_RM)) ||
    (NULL == CU_add_test(pSuite1, "test of istring_to_string()", testISTRING_TO_STRING)) ||
    (NULL == CU_add_test(pSuite1, "test of istrlen()", testISTRLEN))  ||
    (NULL == CU_add_test(pSuite1, "test of istrfixlen()", testISTRFIXLEN))  
  )
    {
      CU_cleanup_registry();
      return CU_get_error();
    }

  if (
    (NULL == CU_add_test(pSuite2, "test of istrcat()", testISTRCAT)) ||
    (NULL == CU_add_test(pSuite2, "test of istrncat()", testISTRNCAT)) ||
    (NULL == CU_add_test(pSuite2, "test of istrchr()", testISTRCHR)) ||
    (NULL == CU_add_test(pSuite2, "test of istrrchr()", testISTRRCHR)) ||
    (NULL == CU_add_test(pSuite2, "test of istrcmp()", testISTRCMP)) ||
    (NULL == CU_add_test(pSuite2, "test of istrncmp()", testISTRNCMP)) ||
    (NULL == CU_add_test(pSuite2, "test of istrcpy()", testISTRCPY)) ||
    (NULL == CU_add_test(pSuite2, "test of istrncpy()", testISTRNCPY))
  )
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

