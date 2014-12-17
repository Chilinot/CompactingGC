#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>
#include <assert.h>
#include <stdint.h>
#include "../../heap.h"

///////////////////////////////////////////////////////////////
// Caution! Under no circumstances confuse the mesh with the //
// interleave operator, except under confusing circumstances!!!
///////////////////////////////////////////////////////////////


#define Dump_registers() \
jmp_buf env; \
if (setjmp(env)) abort(); \


#define STACK_ORIGIN env

extern char** environ;
//stack trace
void stackIterator(Heap superheap, void *(foreach)(void**)){
  Dump_registers();


}
int foo(void* heapStart, void* heapEnd);

int main(int argc, char* argv[]){

  
  gsize_t isize = 320;
  void* myHeap = malloc(isize*sizeof(void*));
  void* alpha = myHeap+1;
  printf("%d", foo(myHeap,((void*)myHeap , (void*)myHeap+isize )));
  free(myHeap);
}

int foo(void* heapStart, void* heapEnd){
  int count = 0; 
  Dump_registers();
  
  void* tail = (void*) environ;
  printf("%p\n", tail);
  

#ifdef __GNUC__
  void* stackPointer = __builtin_frame_address(0);
#else
  int _HOPEFULLY_NO_ONE_USES_THIS_VARIABLE_NAME_ = Ox1337;
  void* stackPointer = &_HOPEFULLY_NO_ONE_USES_THIS_VARIABLE_NAME_;
#endif
  


 void* head = stackPointer;
 //void* head2 = null;
  //register int sp = asm("sp"); 
  printf("%p\n", head2 );
  printf("%p\n", &x);
  
  int sign = tail-head < 0 ? -1 : 1;   

  void** cursor = head;
 loop:
  if( cursor != tail ){
    void* cursorValue = *cursor;
    if(cursorValue < heapEnd && heapStart < cursorValue){
      count++;
   }
    cursor = cursor+sign;
    goto loop;
  }   
  return count;
  
}
