#include "../../src/gc.h"
#include "../../src/heap.h"
#include "binarytree.h"
#include <stdio.h>

int main(void) {
	// Create a 2KB large heap for the binary tree.
	Heap heap = h_init(sizeof(struct heap_s) + 2048 * sizeof(void*));
	
	BinaryTree tree = tree_insert(heap, tree, "5", "5");
	tree = tree_insert(heap, tree, "3", "3");
	tree = tree_insert(heap, tree, "2", "2");
	tree = tree_insert(heap, tree, "4", "4");
	tree = tree_insert(heap, tree, "7", "7");
	tree = tree_insert(heap, tree, "6", "6");
	tree = tree_insert(heap, tree, "8", "8");
	
	puts("First print:");
	tree_print(tree);
	
	tree = tree_remove(heap, tree, "7");
	
	puts("Second print:");
	tree_print(tree);
	printf("%d\n", h_avail(heap));
	
	// Force garbage collection on the heap.
	h_gc(heap);
	
	// Is the tree still "alive"?
	puts("Third print:");
	tree_print(tree);
	printf("%d\n", h_avail(heap));
	
	return 0;
}