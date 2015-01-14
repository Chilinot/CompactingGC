/**
 * @file
*/



#ifndef __linkedlistLong__
#define __linkedlistLong__
#include <inttypes.h>
#include "../src/gc.h" // our garbage collector!

typedef struct _linkedlist {
	uint64_t data;
	struct _linkedlist* next;
}* LinkedListTest;


/**
 * Adds a new head node to the given list with the given data.
 *
 * @param list - The list to add the data too.
 * @param data - The data to add to the list.
 * @return New pointer to new head with given list as tail.
 */
LinkedListTest add(LinkedListTest list, uint64_t data);

LinkedListTest addgc(LinkedListTest list, uint64_t data, Heap h);

/**
 * Returns the data in the head of the given list.
 *
 * @param list - The list to look at.
 * @return The data stored in the head of the given list.
 */
uint64_t examine_head(LinkedListTest list);

/**
 * Removes the head of the given list and returns a pointer to its tail.
 *
 * @param list - The list to remove the head of.
 * @return A new pointer pointing to the tail of the given list.
 */
LinkedListTest remove_head(LinkedListTest list);

/**
 * Deallocates all memory of the given list.
 *
 * @param list - The list to destroy.
 */
void destroy_list(LinkedListTest list);


/**
 * searches for data in the list
 * @param list list to be search in
 * @param data value to find in list
 */
void search(LinkedListTest list, uint64_t data);

#endif
