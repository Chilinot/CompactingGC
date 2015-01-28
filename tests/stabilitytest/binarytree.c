#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "binarytree.h"

struct binary_tree {
    char* key;
    char* value;
    struct binary_tree* left;
    struct binary_tree* right;
};

BinaryTree tree_new_node(Heap heap, char* key, char* value) {
    BinaryTree root = h_alloc_data(heap, sizeof(struct binary_tree));
	
    root->left = NULL;
    root->right = NULL;
    
    root->key = h_alloc_data(heap, sizeof(char) * (strlen(key) + 1));
    strcpy(root->key, key);
    
    root->value = h_alloc_data(heap, sizeof(char) * (strlen(value) + 1));
    strcpy(root->value, value);

    return root;
}

BinaryTree tree_insert(Heap heap, BinaryTree tree, char* key, char* value) {
    if(tree == NULL) {
        return tree_new_node(heap, key, value);
    }
    else {
        if(strncmp(tree->key, key, 128) <= 0) {
            tree->left = tree_insert(heap, tree->left, key, value);
        }
        else {
            tree->right = tree_insert(heap, tree->right, key, value);
        }
    }

    return tree;
}

BinaryTree tree_insert_subtree(Heap heap, BinaryTree root, BinaryTree subtree) {
    if(subtree != NULL) {
        root = tree_insert(heap, root, subtree->key, subtree->value);
        root = tree_insert_subtree(heap, root, subtree->left);
        root = tree_insert_subtree(heap, root, subtree->right);
       
//         free(subtree->key);
//         free(subtree->value);
//         free(subtree);
    }
    return root;
}

BinaryTree tree_remove(Heap heap, BinaryTree tree, char* key) {
    if(tree == NULL) {
        return NULL;
    }
    else {
        int cmp = strncmp(tree->key, key, 128);

        if(cmp < 0) {
            tree->left = tree_remove(heap, tree->left, key);
        }
        else if(cmp == 0) {
            tree->left = tree_insert_subtree(heap, tree->left, tree->right);

//             free(tree->key);
//             free(tree->value);
//             free(tree);

            return tree->left;
        }
        else {
            tree->right = tree_remove(heap, tree->right, key);
        }
    }

    return tree;
}

char* tree_query(BinaryTree tree, char* key) {
    if(tree == NULL) {
        return NULL;
    }
    else {
        int cmp = strncmp(tree->key, key, 128);
        
        if(cmp < 0) {
            return tree_query(tree->left, key);
        }
        else if(cmp == 0) {
            return tree->value;
        }
        else {
            return tree_query(tree->right, key);
        }
    }
}

int tree_update(Heap heap, BinaryTree tree, char* key, char* value) {
    if(tree == NULL) {
        return 0;
    }
    else {
        int cmp = strncmp(tree->key, key, 128);

        if(cmp < 0) {
            return tree_update(heap, tree->left, key, value);
        }
        else if(cmp == 0) {
//             free(tree->value);
            tree->value = h_alloc_data(heap, sizeof(char) * (strlen(value) + 1));
            strcpy(tree->value, value);
            return 1;
        }
        else {
            return tree_update(heap, tree->right, key, value);
        }
    }
}

void tree_print(BinaryTree tree) {
    if(tree == NULL) {
        return;
    }
    tree_print(tree->right);
    printf("|%-21s|%-21s|\n", tree->key, tree->value);
    tree_print(tree->left);
}
