#ifndef __linkedlist__
#define __linkedlist__

typedef struct _linkedlist {
	void* data;
	struct _linkedlist* next;
}* LinkedList;

/**
 * Adds a new head node to the given list with the given data.
 *
 * @param list - The list to add the data too.
 * @param data - The data to add to the list.
 * @return New pointer to new head with given list as tail.
 */
LinkedList add(LinkedList list, void* data);

/**
 * Returns the data in the head of the given list.
 *
 * @param list - The list to look at.
 * @return The data stored in the head of the given list.
 */
void* examine_head(LinkedList list);

/**
 * Removes the head of the given list and returns a pointer to its tail.
 *
 * @param list - The list to remove the head of.
 * @return A new pointer pointing to the tail of the given list.
 */
LinkedList remove_head(LinkedList list);

/**
 * Deallocates all memory of the given list.
 *
 * @param list - The list to destroy.
 */
void destroy_list(LinkedList list);

#endif
