//Linked list structure used for performance testing of garbage collector

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "../../src/gc.h"
#include "../../src/stack.h" 
#include "../../src/header.h" 
#include "../../src/heap.h" 
#include "../../src/heapIterator.h" 
#include "../../src/string_util.h" 


typedef struct list_node{
  struct list_node* next;
  long value;
}*Node;

typedef struct linked_list{
  Node firstNode;
  Node lastNode;
}*List;



List create_list_malloc(){
  List list = malloc(sizeof(struct linked_list));
  list->firstNode = NULL;
  list->lastNode = list->firstNode;
  return list;
}

  List create_list_gc(Heap heap){
  List list = h_alloc_struct(heap, "**");
  list->firstNode = NULL;
  list->lastNode = list->firstNode;
  return list;
  }

void push_malloc(long val, List list){
  Node newNode = malloc(sizeof(struct list_node));
  if(newNode != NULL){
    newNode->value = val;
    newNode->next = NULL;
    if(list->firstNode == list->lastNode){
      if(list->firstNode != NULL){
	list->firstNode->next = newNode;
	list->lastNode = newNode;
      }else{
	list->firstNode = newNode;
	list->lastNode = list->firstNode;
      }
    }else{
      list->lastNode->next = newNode;
      list->lastNode = newNode;
    }
  }
}

void push_gc(long val, List list, Heap heap){
  Node newNode = h_alloc_struct(heap, "*l");
  if(newNode != NULL){
    newNode->value = val;
    newNode->next = NULL;
    if(list->firstNode == list->lastNode){
      if(list->firstNode != NULL){
	list->firstNode->next = newNode;
	list->lastNode = newNode;
      }else{
	list->firstNode = newNode;
	list->lastNode = list->firstNode;
      }
    }else{
      list->lastNode->next = newNode;
      list->lastNode = newNode;
    }
  }
}

int exists_in_list(long int val, List list){
  Node cursor = list->firstNode;
  while(cursor != NULL){
    if (cursor->value == val){
      return 1;
    }
    cursor = cursor->next;
  }
  return 0;
}

void print_list(List list){
  Node cursor = list->firstNode;
  while (cursor != NULL){
    printf("List item is %lu\n", cursor->value);
    cursor = cursor->next;
  }
}
