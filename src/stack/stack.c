#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>
#include <assert.h>
#include <stdint.h>

///////////////////////////////////////////////////////////////
// Caution! Under no circumstances confuse the mesh with the //
// interleave operator, except under confusing circumstances!!!
///////////////////////////////////////////////////////////////


#define Dump_registers() \
jmp_buf env; \
if (setjmp(env)) abort(); \

extern char** environ;

int foo(void* heapStart, void* heapEnd);

int main(int argc, char* argv[]){

  
  size_t isize = 320;
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
  
  int x = 32;
  void* head = &x;
  void* head2 = __builtin_frame_address(0);
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
