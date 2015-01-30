#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "binarytree.h"

struct binary_tree {
    int key;
    struct binary_tree* left;
    struct binary_tree* right;
};

BinaryTree tree_new_node(Heap heap, int key) {
    BinaryTree root = h_alloc_struct(heap, "i**");
	
    root->left  = NULL;
    root->right = NULL;
	root->key   = key;

    return root;
}

BinaryTree tree_insert(Heap heap, BinaryTree tree, int key) {
    if(tree == NULL) {
        return tree_new_node(heap, key);
    }
    else {
        if(key <= tree->key) {
            tree->left = tree_insert(heap, tree->left, key);
        }
        else {
            tree->right = tree_insert(heap, tree->right, key);
        }
    }

    return tree;
}

BinaryTree tree_insert_subtree(Heap heap, BinaryTree root, BinaryTree subtree) {
    if(subtree != NULL) {
        root = tree_insert(heap, root, subtree->key);
        root = tree_insert_subtree(heap, root, subtree->left);
        root = tree_insert_subtree(heap, root, subtree->right);
    }
    return root;
}

BinaryTree tree_remove(Heap heap, BinaryTree tree, int key) {
    if(tree == NULL) {
        return NULL;
    }
    else {
        if(key < tree->key) {
            tree->left = tree_remove(heap, tree->left, key);
        }
        else if(key == tree->key) {
            tree->left = tree_insert_subtree(heap, tree->left, tree->right);
            return tree->left;
        }
        else {
            tree->right = tree_remove(heap, tree->right, key);
        }
    }

    return tree;
}

void tree_print_subtree(BinaryTree tree) {
	if(tree == NULL) {
		return;
	}
	printf("|%-12p|%-5d|\n", tree, tree->key);
	tree_print_subtree(tree->left);
	tree_print_subtree(tree->right);
}

void tree_print(BinaryTree tree) {
	printf("|%-12s|%-5s|\n", "Node address", "Key");
	tree_print_subtree(tree);
}