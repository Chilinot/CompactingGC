#ifndef BINARYTREE_H
#define BINARYTREE_H

#include "../../src/gc.h"

typedef struct binary_tree *BinaryTree;

BinaryTree tree_insert(Heap heap, BinaryTree tree, char* key, char* value);
BinaryTree tree_remove(Heap heap, BinaryTree tree, char* key);
int        tree_update(Heap heap, BinaryTree tree, char* key, char* value);
char*      tree_query(BinaryTree tree, char* key);
void       tree_print(BinaryTree tree);

#endif
