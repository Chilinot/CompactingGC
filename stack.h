/**
 * @File
 */
#ifndef __HEADER__
#define __HEADER__



/**
 * Finds all the possible pointers that points on the stack to the memoryspace where;
 * heapStart < memoryspace < heapEnd
 * and calls the function "foreach" for every pointer found.
 * @param heapStart pointer to the start of the heap
 * @param heapEnd pointer to the end of the heap
 * @param foreach function which is applied to all pointers found
*/

void stackIterator(void* heapStart, void* heapEnd,  void (*foreach)(void**));


#endif
