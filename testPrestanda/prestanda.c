#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "linkedListLong.h" // use Lucas' awesome module (modified) !
#include "../gc.h" // our garbage collector!
#include "../stack.h" 
#include "../header.h" 
#include "../heap.h" 
#include "../heapIterator.h" 
#include "../string_util/string_util.h" 
#include "../heap_rep.h"


#include <inttypes.h> // for uint64_t

#define BILLION 1000000000
#define MAX_RANDOM 4 * BILLION



uint64_t random(){

  uint64_t num;

  /* add code to seed random number generator */

  num = rand();
  num = (num << 32) | rand();

  // enforce limits of value between 100000000 and 999999999
  num = (num % (999999999 - 100000000)) + 100000000;
  return num;
}

uint64_t randomLong(){
  uint64_t l = random();

  /* if(l >  MAX_RANDOM%(4*BILLION)  4 miljarder ){

     return randomLong();
     }
  */

  
  return l;
}



void fillTheLists(LinkedListTest l1, LinkedListTest l2, LinkedListTest l3, LinkedListTest l4){

  uint64_t theRandomAmountOfNumbersToPutInTheLists = randomLong();
  // between 0 and 4 billions
  
  for(int i = 0; i < theRandomAmountOfNumbersToPutInTheLists; i++){
    
    uint64_t randomNumberToAddInList = randomLong(); // between 0 and 4 billions
  
    if(randomNumberToAddInList%5 >= 0 && randomNumberToAddInList%5 < 1){
      add(l1,randomNumberToAddInList);
    }
    
    if(randomNumberToAddInList%5 >= 1 && randomNumberToAddInList%5 <= 2){
      add(l2,randomNumberToAddInList);
    }
    
    if(randomNumberToAddInList%5 > 2 && randomNumberToAddInList%5 <= 3){
      add(l3,randomNumberToAddInList);
    }

    if(randomNumberToAddInList%5 > 3 && randomNumberToAddInList%5 <= 4){
      add(l4,randomNumberToAddInList);
    }
  }
}

void randomNumberSearch(LinkedListTest l1, LinkedListTest l2, LinkedListTest l3, LinkedListTest l4){

  uint64_t NumberOfLoops = randomLong();

  for(int i = 0; i < NumberOfLoops; i++){

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

void mallocPrestanda(){;
  LinkedListTest l1 = NULL ;
  LinkedListTest l2 = NULL ;
  LinkedListTest l3 = NULL ;
  LinkedListTest l4 = NULL ;
 
  //random M numbers between 0 and 4e10  and put them in the four different lists
  
  fillTheLists(l1, l2, l3, l4);
  
  //Now we have a bunch of random numbers in our list now we have to random N numbers and search in the lists and find them if we can
  randomNumberSearch(l1 ,l2 ,l3 ,l4);

  //dealllocate the lists
  destroy_list(l1);
  destroy_list(l2);
  destroy_list(l3);
  destroy_list(l4);  

}


void fillTheListsgc(LinkedListTest l1, LinkedListTest l2, LinkedListTest l3, LinkedListTest l4, Heap heap){

  uint64_t theRandomAmountOfNumbersToPutInTheLists = randomLong();
  // between 0 and 4 billions
  
  for(int i = 0; i < theRandomAmountOfNumbersToPutInTheLists; i++){
    
    uint64_t randomNumberToAddInList = randomLong(); // between 0 and 4 billions
  
    if(randomNumberToAddInList%5 >= 0 && randomNumberToAddInList%5 < 1){
      addgc(l1,randomNumberToAddInList, heap);
    }
    
    if(randomNumberToAddInList%5 >= 1 && randomNumberToAddInList%5 <= 2){
      addgc(l2,randomNumberToAddInList, heap);
    }
    
    if(randomNumberToAddInList%5 > 2 && randomNumberToAddInList%5 <= 3){
      addgc(l3,randomNumberToAddInList, heap);
    }

    if(randomNumberToAddInList%5 > 3 && randomNumberToAddInList%5 <= 4){
      addgc(l4,randomNumberToAddInList, heap);
    }
  }
}


void gcPrestanda(){

  Heap h = h_init(20 + 100 * sizeof(void*)); // initialize a heap with what value??

  if(h == NULL){
    puts("h == NULL");
  }

  //need to create 4 lists and add theRandomAmountOfNumbersToAddInTheList
  LinkedListTest l1 =  NULL;
  LinkedListTest l2 =  NULL;
  LinkedListTest l3 =  NULL;
  LinkedListTest l4 =  NULL;
  fillTheListsgc(l1, l2, l3, l4, h);
  // randomNumberSearchgc(l1 ,l2 ,l3 ,l4, h);


  h_delete(h);

}


int main(){
  puts("PRESTANDA TEST WITH MALLOC AND OUR GC");
  
  clock_t start_t, end_t, total_t;


  start_t = clock();
  printf("Starting of the program, start_t = %ld\n", start_t);



  //mallocPrestanda(); //DONE I THINK
  gcPrestanda(); //NOT DONE NOT STARTED ON


  end_t = clock();
  printf("End of the big loop, end_t = %ld\n", end_t);
  return 0;
}
