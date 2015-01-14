#include <assert.h>
#include "heap.h"
#include "linkedlist.h"
#include "header.h"
#include "gc.h"
#include "heap_rep.h"
#include <stdint.h>
#include <stdbool.h>
#include "heapIterator.h"



// Objekt flyttas till den passiva/nya delen av heapen om den inte redan är flyttad och markeras som flyttad.
// Om objektet redan är flyttat kommer det inte flyttas igen, addresen till objektet på passiva delen kommer fortfarande retuneras.
// Om objektet har pekare till andra objekt på heapen kommer dom också flyttas och pekarna ändras därefter.
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
	  void** pplusnewObjPlats = (void**)(((intptr_t) p ) + ((intptr_t) newObjPlats ));
	  *pplusnewObjPlats = heapIterator(h, *pplusnewObjPlats);
		return;
	};
	header_pointerIterator(GET_HEAPBLOCK(newObjPlats), &g);

	return newObjPlats;
}
