#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>
#include <assert.h>
#include <stdint.h>
//#include "../../heap.h"


#define Dump_registers() \
jmp_buf env; \
if (setjmp(env)) abort(); \

extern char** environ;

int count = 0;
void countplusone(void** neveruse){
  count++;
}



void stackIterator( void* heapStart, void* heapEnd,  void (*foreach)(void**)){
  Dump_registers();
  #ifdef __GNUC__
  void* stackTop = __builtin_frame_address(0);
#else
  int getStackPointerTemp = Ox1337;
  void* stackTop = &getStackPointerTemp;
#endif
 void* stackBottom = (void*) environ;

  int sign = stackBottom -stackTop < 0 ? -1 : 1;   

  void** cursor = stackTop;
  while( cursor != stackBottom ){
    void* cursorValue = *cursor;
    if(cursorValue < heapEnd && heapStart < cursorValue){
      (*foreach)(cursor);
   }
    cursor = cursor+sign;
  }   
  
}
  

int main(int argc, char* argv[]){
  size_t isize = 320;
  void* myHeap = malloc(isize*sizeof(void*));
  void* alpha = myHeap+4;
  void* beta = myHeap+23;
  count = 0; 
  stackIterator((void*)myHeap , (void*)myHeap+isize, &countplusone);
  printf("%d\n",count); 
  free(myHeap);
}
