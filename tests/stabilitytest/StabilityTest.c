#include "../../src/gc.h"
#include "../../src/heap.h"
#include "binarytree.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {
	// Initiate random generator with a random seed.
	srand(9834589182300129);
	
	// Create a 2KB large heap for the binary tree.
	Heap heap = h_init(sizeof(struct heap_s) + 2048 * 2);
	
	printf("\nAvailable bytes in heap: %zu\n", h_avail(heap));
	
	BinaryTree tree = tree_insert(heap, NULL, 25);
	for(int i = 0; i < 50; i++) {
		tree = tree_insert(heap, tree, (rand() % 50) + 1);
	}
	
	puts("\nFirst print:");
	tree_print(tree);
	printf("%zu Bytes left.\n", h_avail(heap));
	
	// Force garbage collection on the heap 10 times.
	for(int i = 0; i < 10; i++) {
		h_gc(heap);
		
		// Is the tree still "alive"?
		puts("");
		tree_print(tree);
		printf("%zu Bytes left.\n", h_avail(heap));
	}
	
	return 0;
}