#include "heap.h"
#include "linkedlist.h"
#include "header.h"
#include "gc.h"
#include "heap_rep.h"
#include <stdint.h>
#include <stdbool.h>
#include "heapIterator.h"



/**
 Objekt flyttas till den passiva/nya delen av heapen om den inte redan är flyttad och markeras som flyttad.
Om objektet redan är flyttat kommer det inte flyttas igen, addresen till objektet på passiva delen kommer fortfarande retuneras.
Om objektet har pekare till andra objekt på heapen kommer dom också flyttas och pekarna ändras därefter. 
@param h heapen vi jobbar på
@param obj är en pekare till objekt på den aktiva heapen
@return en pekare till det nya stället(på den passiva delen av heapen) objektet nu kan hittas
 */

void *heapIterator(Heap h, void *obj){
  if(heap_hasBeenCopied(obj) == true){
    return header_clearHeaderTypeBits(GET_HEAPBLOCK(obj));
  }
  //else
  void *newObjPlats = heap_copyFromActiveToPassive(h, obj);
  void g(void *p){
    *p = heapIterator(h, *p);
    return;
  };
  header_pointerIterator(GET_HEAPBLOCK(newObjPlats), &g);
  return newObjPlats;
}


/*
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
*/
