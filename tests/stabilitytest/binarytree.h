#ifndef BINARYTREE_H
#define BINARYTREE_H

#include "../../src/gc.h"

typedef struct binary_tree *BinaryTree;

BinaryTree tree_insert(Heap heap, BinaryTree tree, int key);
BinaryTree tree_remove(Heap heap, BinaryTree tree, int key);
void       tree_print(BinaryTree tree);

#endif
