#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "linkedListLong.h" // use Lucas' awesome module (modified) !
#include "../src/gc.h" // our garbage collector!
#include "../src/stack.h" 
#include "../src/header.h" 
#include "../src/heap.h" 
#include "../src/heapIterator.h" 
#include "../src/string_util.h" 


#include <inttypes.h> // for uint64_t

#define BILLION 1000000000
#define MAX_RANDOM 4 * BILLION





uint64_t randomLong(){
  return (uint64_t) rand();
}



void fillTheLists(LinkedListTest l1, LinkedListTest l2, LinkedListTest l3, LinkedListTest l4, int m){

  uint64_t theRandomAmountOfNumbersToPutInTheLists = randomLong();
  // between 0 and 4 billions
  
  for(int i = 0; i < m; i++){

    uint64_t randomNumberToAddInList = randomLong(); // between 0 and 4 billions
  
    if(randomNumberToAddInList%5 >= 0 && randomNumberToAddInList%5 < 1){
      l1 = add(l1,randomNumberToAddInList);
    }
    
    if(randomNumberToAddInList%5 >= 1 && randomNumberToAddInList%5 <= 2){
      l2 = add(l2,randomNumberToAddInList);
    }
    
    if(randomNumberToAddInList%5 > 2 && randomNumberToAddInList%5 <= 3){
      l3 = add(l3,randomNumberToAddInList);
    }

    if(randomNumberToAddInList%5 > 3 && randomNumberToAddInList%5 <= 4){
      l4 = add(l4,randomNumberToAddInList);
    }
  }
}

void randomNumberSearch(LinkedListTest l1, LinkedListTest l2, LinkedListTest l3, LinkedListTest l4, int n){

  for(int i = 0; i < n; i++){

    uint64_t randomNumberToSearch = randomLong(); // between 0 and 4 billions

 
    if(randomNumberToSearch%5 >= 0 && randomNumberToSearch%5 <= 1){
      search(l1,randomNumberToSearch);
    }
    
    if(randomNumberToSearch%5 > 1 && randomNumberToSearch%5 <= 2){
      search(l2,randomNumberToSearch);
    }
    
    if(randomNumberToSearch%5 > 2 && randomNumberToSearch%5 <= 3){
      search(l3,randomNumberToSearch);
    }

    if(randomNumberToSearch%5 > 3 && randomNumberToSearch%5 <= 4){
      search(l4,randomNumberToSearch);
    }
   
  }


}

void mallocPrestanda(int m, int n){;
  LinkedListTest l1 = NULL ;
  LinkedListTest l2 = NULL ;
  LinkedListTest l3 = NULL ;
  LinkedListTest l4 = NULL ;
 
  //random M numbers between 0 and 4e10  and put them in the four different lists
  
  fillTheLists(l1, l2, l3, l4,m);
  
  fillTheLists(l1, l2, l3, l4,n);
  //Now we have a bunch of random numbers in our list now we have to random N numbers and search in the lists and find them if we can
  randomNumberSearch(l1 ,l2 ,l3 ,l4, n);

  //dealllocate the lists
  destroy_list(l1);
  destroy_list(l2);
  destroy_list(l3);
  destroy_list(l4);  

}




void fillTheListsgc(LinkedListTest l1, LinkedListTest l2, LinkedListTest l3, LinkedListTest l4, int m, Heap heap){

  for(int i = 0; i < m; i++){
    //printf("heap available %d\n", h_avail(heap));    
    uint64_t randomNumberToAddInList = randomLong(); // between 0 and 4 billions
  
    if(randomNumberToAddInList%5 >= 0 && randomNumberToAddInList%5 < 1){
      l1 = addgc(l1,randomNumberToAddInList, heap);
    }
    
    if(randomNumberToAddInList%5 >= 1 && randomNumberToAddInList%5 <= 2){
      l2 = addgc(l2,randomNumberToAddInList, heap);
    }
    
    if(randomNumberToAddInList%5 > 2 && randomNumberToAddInList%5 <= 3){
      l3 = addgc(l3,randomNumberToAddInList, heap);
    }
    
    if(randomNumberToAddInList%5 > 3 && randomNumberToAddInList%5 <= 4){
      l4 = addgc(l4,randomNumberToAddInList, heap);
    }
  }
}


void gcPrestanda(int m, int n, int heapSize){

  Heap h = h_init(sizeof(struct heap_s) +  heapSize * sizeof(void*)); // initialize a heap with what value??

  if(h == NULL){
    puts("h == NULL");
  }

  //need to create 4 lists and add theRandomAmountOfNumbersToAddInTheList
  LinkedListTest l1 =  NULL;
  LinkedListTest l2 =  NULL;
  LinkedListTest l3 =  NULL;
  LinkedListTest l4 =  NULL;

  fillTheListsgc(l1, l2, l3, l4, m, h); //shows cleaning unreferenced objects in the heap
  h_gc(h);
  fillTheListsgc(l1, l2, l3, l4, n, h); //shows cleaning unreferenced objects in the heap

  randomNumberSearch(l1 ,l2 ,l3 ,l4, n);
  

  h_delete(h);

}


int main(){
  puts("PRESTANDA TEST WITH MALLOC AND OUR GC");
  
  clock_t start_t, end_t, total_t;

  for(int i = 0; i < 0; i++){
    printf("random number = %d\n", rand());
  }


  
  printf("Starting of the program, start_t = %d\n", 1337);
 
  unsigned int N = 1000000; // times to search the list
  unsigned int M = 10000000; //add M number of objects in the list
  unsigned int heapSize = 10000000000;
  printf("RUNNING TESTS\n");


  printf("TESTING GC\n");
  for(int i = 0; i < 5; i++){
    start_t = clock();
 
    printf(" number of searches %d\n number of objects inserted %d\n size of the heap %d\n\n",N, M, heapSize);
   
    gcPrestanda(M,N, heapSize); 
    N /= 10;
    M /= 10;
    heapSize /= 10;


    start_t = clock() - start_t;
    double  time = ((float)start_t)/CLOCKS_PER_SEC;
    
    printf("Time for this test: %f\n\n", time  );
  }
  N = 1000000; // times to search the list
  M = 10000000; //add M number of objects in the list
  heapSize = 10000000000;
  printf("TESTING MALLOC\n");
  for(int i = 0; i < 5; i++){
    start_t = clock();
 
    printf(" number of searches %d\n number of objects inserted %d\n size of the heap %d\n\n",N, M, heapSize);
   
    gcPrestanda(M,N, heapSize); 
    N /= 10;
    M /= 10;
    heapSize /= 10;


    start_t = clock() - start_t;
    double  time = ((float)start_t)/CLOCKS_PER_SEC;
    
  printf("Time for this test: %f\n", time  );
  }

  start_t = clock() - start_t;
  double  time = ((float)start_t)/CLOCKS_PER_SEC;

  return 0;
}
