#include <stdio.h>
#include <stdlib.h>
#include <string,h>
#include "../linkedlist.h" // use Lucas' awesome module !

#define BILLION 1000000000
#define MAX_RANDOM 4 * BILLION



long randomLong(){
  long l = random();
  if(l >  MAX_RANDOM  /* 4 miljarder */){
    return randomLong();
  }
  return l;
}

void fillTheLists(l1, l2, l3, l4){

  unsigned long theRandomAmountOfNumbersToPutInTheLists = randomLong(); // between 0 and 4 billions

  for(int i = 0; i < theRandomAmountOfNumbersToPutInTheLists; i++){

    unsigned long randomNumberToAddInList = randomLong(); // between 0 and 4 billions
    if(randomNumberToAddInList >= 0 && randomNumberToAddInList <= 1 * BILLION){
      add(l1,randomNumberToAddInList);
    }

    if(randomNumberToAddInList >= 1 * BILLION && randomNumberToAddInList <= 2 * BILLION){
      add(l2,randomNumberToAddInList);
    }

    if(randomNumberToAddInList >= 2 * BILLION && randomNumberToAddInList <= 3 * BILLION){
      add(l3,randomNumberToAddInList);
    }

    if(randomNumberToAddInList >= 3 * BILLION && randomNumberToAddInList <= 4 * BILLION){
      add(l4,randomNumberToAddInList);
    }
  }
}

void mallocPrestanda(){;
  LinkedList l1 = NULL ;
  LinkedList l2 = NULL ;
  LinkedList l3 = NULL ;
  LinkedList l4 = NULL ;

  //random M numbers between 0 and 4e10  and put them in the four different lists
  
  fillTheLists(l1, l2, l3, l4);

  //Now we have a bunch of random numbers in our list now we have to random N numbers and search in the lists and find them if we can
  

}

int main(){
  puts("PRESTANDA TEST WITH MALLOC AND OUR GC"
  
  mallocPrestanda(); //NOT DONE IN PROGRESS
  gcPrestanda(); //NOT DONE NOT STARTED ON

  return 0;
}
