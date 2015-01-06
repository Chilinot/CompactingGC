#include "heap.h"
#include "linkedlist.h"
#include "gc.h"
#include "header.c"
#include <stdint.h>
#include "heapIterator.h"


LinkedList heapIterator(void* start, Heap heap) {
	LinkedList list = NULL;
	char* cursor = start;

	switch(header_getHeaderType(getHeader(start))) {
	case POINTER_TO_STRING:
		char* string = ((char*) header_clearHeaderTypeBits(getHeader(start)));
		int i = 0;

		while(string[i] != '\0') {
			switch(string[i]) {
			case 'r':
				cursor += sizeof(int) / sizeof(char);
				break;

			case '*':
				list = add(list, (void*)(cursor));
				cursor += sizeof(void*) / sizeof(char);
				break;
			}

			i++;
		}

		break;

	case BITVECTOR:
		char* cursor = ((char*) start);
		intptr_t head = (intptr_t) getHeader(start);

		for(int i = 0; i < sizeof(intptr_t) - 2; i += 2) {
			switch((head >> sizeof(intptr_t) - i + numberofheaderbit) && tokenmask) {
			case INT_TOKEN:
				cursor += sizeof(int) / sizeof(char);
				break;

			case POINTER_TOKEN:
				list = add(list, (void*)(cursor));
				cursor += sizeof(void*) / sizeof(char);
				break;

			case TERMINATOR_TOKEN:
				i = 0xfffff; // number for termination of the loop
				break;
			}
		}

		break;
	}

	return list;
}

