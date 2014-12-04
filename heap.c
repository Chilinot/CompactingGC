#include <stdio.h>
#include <stdlib.h>


typedef struct heap_s{
  void* data;
  int var;
  struct heap_s* left;
  struct heap_s* right;
} heap_t;


heap_t* init(size_t bytes){
  heap_t* heap = malloc(sizeof(bytes));
  return heap;
}


int main(int argc, char* argv[]){
  printf("Hur stor heap vill du ha?");
  heap_t* ret = init(argv[1]);

  return 0;
}
