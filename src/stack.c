#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>
#include <assert.h>
#include <stdint.h>
#include "stack.h"
//#include "../../heap.h"

#define Dump_registers() \
jmp_buf env; \
if (setjmp(env)) abort(); \
 
// Finds all the possible pointers that points on the stack to memoryspace where;
// heapstart < memoryspace < heapEnd and calls the fucntion foreach for every pointer found
void stackIterator(void* heapStart, void* heapEnd,  void (*foreach)(void**)) {
	extern char** environ;
	Dump_registers();
#ifdef __GNUC__
	void* stackTop = __builtin_frame_address(0);
#else
	int getStackPointerTemp = Ox1337;
	void* stackTop = &getStackPointerTemp;
#endif
	void* stackBottom = (void*) environ;

	int sign = stackBottom - stackTop < 0 ? -1 : 1;

	void** cursor = stackTop;

	while(cursor != stackBottom) {
		void* cursorValue = *cursor;

		if(cursorValue < heapEnd && heapStart < cursorValue) {
			(*foreach)(cursor);
		}

		cursor = cursor + sign;
	}

}



