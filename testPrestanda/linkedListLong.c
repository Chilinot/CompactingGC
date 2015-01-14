#include "linkedListLong.h"
#include <stdlib.h>
#include <inttypes.h>
#include "../gc.h" // our garbage collector!
#include "../stack.h" 
#include "../header.h" 
#include "../heap.h" 
#include "../heapIterator.h" 
#include "../string_util/string_util.h" 
#include "../heap_rep.h"



LinkedListTest add(LinkedListTest list, uint64_t data) {
  LinkedListTest new_node = malloc(sizeof(struct _linkedlist));
  new_node->data = data;
  new_node->next = list;
  
  return new_node;
}



LinkedListTest addgc(LinkedListTest list, uint64_t data, Heap h) {
  LinkedListTest new_node = h_alloc_struct(h, "d*");
  new_node->data = data;
  new_node->next = list;
  printf("Heapspace available %d\n", h_avail(h));
  printf("data %d\n", data);
  return new_node;
}


uint64_t examine_head(LinkedListTest list) {
  return list->data;
}

LinkedListTest remove_head(LinkedListTest list) {
  LinkedListTest tail = list->next;
  free(list);
  return tail;
}

void destroy_list(LinkedListTest list) {
  // Remove each node until the list is null.
  while(list) {
    list = remove_head(list);
  }
}


void search(LinkedListTest list, uint64_t data){
  while(list != NULL){
    if(list->data == data){
      puts("FOUND SOMETHING");
      break;
    }
    list = list -> next;
  }

}
