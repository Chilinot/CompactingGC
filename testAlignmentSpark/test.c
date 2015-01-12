#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct biceps{
  double alpha;
  char beta;
  
} *Biceps;



int main(int argc, char *argv[]){
  puts("hello world!");
  
  char* super = malloc(100);
  printf("super.adress = 0x%x\n", super);

  printf("super.adress%%8 = 0x%x\n", ((intptr_t)super)%8);

  Biceps foobar = super;

  printf("foobar.adress%%8 = 0x%x\n", ((intptr_t)foobar)%8);

  foobar->alpha = 0.673376;
  foobar->beta = 't';
  
  printf("foobar->alpha = %f\n", foobar->alpha);
  printf("foobar->beta = %c\n", foobar->beta);

  foobar = super+4;

  printf("foobar.adress%%8 = 0x%x\n", ((intptr_t)foobar)%8);

  foobar->alpha = 0.673376;
  foobar->beta = 't';
  
  printf("foobar->alpha = %f\n", foobar->alpha);
  printf("foobar->beta = %c\n", foobar->beta);
  
  
  return 0;
}

