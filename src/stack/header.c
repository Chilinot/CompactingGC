#include <stdlib.h>
#include <string.h>
  
#define main int main(int argc, char *argv[])

#define true 1
#define false 0

bool setuptest(void){
    CU_INIT()
    CU_ADDTEST(nanna, a)
    CU_ADDTEST(nanna, a)
    CU_ADDTEST(nanna, a)
    CU_END()
}



#ifdef debug
 
#fidef


#define RAW_BIT_HEAD_HEAD 0b011
#define RAW_BIT_HEAD_HEAD_LENGTH 3

#if ( __SIZEOF_POINTER__ ==  8)
#define UINT_T uint64_t
#else
#define UINT_T uint32_t
#endif



#define HEADER_RAW(PTR , BYTES)  \
*((UINT_T*)(PTR) - __SIZEOF_POINTER__) =  RAW_BIT_HEAD_HEAD | ((BYTES) << RAW_BIT_HEAD_HEAD_LENGTH)


void headerRaw(void *ptr, size_t bytes){
//*((UINT_T)ptr) = 0x00;

*((UINT_T*)ptr) =  RAW_BIT_HEAD_HEAD | (bytes << RAW_BIT_HEAD_HEAD_LENGTH);
 om(3

}

#ifdef UINT_T
#undef UINT_T
