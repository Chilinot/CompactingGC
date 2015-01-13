#ifndef __heapiterator__
#define __heapiterator__

/**
 * Objekt flyttas till den passiva/nya delen av heapen om den inte redan är flyttad och markeras som flyttad.
 * Om objektet redan är flyttat kommer det inte flyttas igen, addresen till objektet på passiva delen kommer fortfarande retuneras.
 * Om objektet har pekare till andra objekt på heapen kommer dom också flyttas och pekarna ändras därefter.
 * @param h heapen vi jobbar på
 * @param obj är en pekare till objekt på den aktiva heapen
 * @return en pekare till det nya stället(på den passiva delen av heapen) objektet nu kan hittas
 */
void* heapIterator(Heap heap, void* obj);


#endif
