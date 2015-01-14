#ifndef __int_list__
#define __int_list__



//include "../persikan/src/gc.h"
#include "../../src/gc.h"
#include "linked_int_list.h"
#include "../../src/stack.h" 
#include "../../src/header.h" 
#include "../../src/heap.h" 
#include "../../src/heapIterator.h" 
#include "../../src/string_util.h" 


typedef struct list_node{
  struct list_node* next;
  long int value;
} *Node;

typedef struct linked_list{
  Node firstNode;
  Node lastNode;
} *List;

List create_list_malloc();
List create_list_gc(Heap heap);
void push_malloc(int val, List list);
void push_gc(int val, List list, Heap heap);
bool exists_in_list(int val, List list);
void print_list(List list);

#endif
