#include "../../src/gc.h"
#include "binarytree.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void) {
	// Initiate random generator with a random seed.
	srand(time(NULL));
	
	// Create a 4KB large heap for the binary tree.
	Heap heap = h_init(h_get_meta_size() + 2048 * 2);
	
	printf("\nAvailable bytes in heap: %zu\n", h_avail(heap));
	
	// Initialize the tree with the key 25.
	BinaryTree tree = tree_insert(heap, NULL, 25);
	
	// Add 49 random nodes to the tree.
	for(int i = 0; i < 49; i++) {
		tree = tree_insert(heap, tree, (rand() % 50) + 1);
	}
	
	puts("\nFirst print:");
	tree_print(tree);
	printf("%zu Bytes left.\n", h_avail(heap));
	
	// Force garbage collection.
	h_gc(heap);
	
	// Is the tree still "alive"?
	puts("");
	tree_print(tree);
	printf("%zu Bytes left.\n", h_avail(heap));
	
	h_delete(heap);
	
	return 0;
}