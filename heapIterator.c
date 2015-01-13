#include <assert.h>
#include "heap.h"
#include "linkedlist.h"
#include "header.h"
#include "gc.h"
#include "heap_rep.h"
#include <stdint.h>
#include <stdbool.h>
#include "heapIterator.h"



/**
 * Objekt flyttas till den passiva/nya delen av heapen om den inte redan är flyttad och markeras som flyttad.
 * Om objektet redan är flyttat kommer det inte flyttas igen, addresen till objektet på passiva delen kommer fortfarande retuneras.
 * Om objektet har pekare till andra objekt på heapen kommer dom också flyttas och pekarna ändras därefter.
 * @param h heapen vi jobbar på
 * @param obj är en pekare till objekt på den aktiva heapen
 * @return en pekare till det nya stället(på den passiva delen av heapen) objektet nu kan hittas
 */
void* heapIterator(Heap h, void* obj) {
	if(heap_hasBeenCopied(obj) == true) {
		return header_clearHeaderTypeBits(GET_HEAPBLOCK(obj));
	}
	else if(header_getHeaderType(GET_HEAPBLOCK(obj)) == FUNCTION_POINTER) {
		return ((*((s_trace_f)(header_clearHeaderTypeBits(GET_HEAPBLOCK(obj)))))(h, &heapIterator, obj));
	}

	//else
	void* newObjPlats = heap_copyFromActiveToPassive(h, obj);
	void g(void * p) {
		*(((intptr_t) p) + newObjPlats) = heapIterator(h, *(((intptr_t) p) + newObjPlats));
		return;
	};
	header_pointerIterator(GET_HEAPBLOCK(newObjPlats), &g);

	return newObjPlats;
}
