#include "linkedlist.h"
#include <stdlib.h>

LinkedList add(LinkedList list, void* data) {
	LinkedList new_node = malloc(sizeof(struct _linkedlist));
	new_node->data = data;
	new_node->next = list;
	return new_node;
}

void* examine_head(LinkedList list) {
	return list->data;
}

LinkedList remove_head(LinkedList list) {
	LinkedList tail = list->next;
	free(list);
	return tail;
}

void destroy_list(LinkedList list) {
	// Remove each node until the list is null.
	while(list) {
		list = remove_head(list);
	}
}
