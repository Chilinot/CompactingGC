
#ifndef __HEADER__
#define __HEADER__



/** 
Finds all the possible pointers that points on the stack to the memoryspace where; 
heapStart < memoryspace < heapEnd
and calls the function "foreach" for every pointer found.   
*/

void stackIterator(void* heapStart, void* heapEnd,  void (*foreach)(void**));


#endif
