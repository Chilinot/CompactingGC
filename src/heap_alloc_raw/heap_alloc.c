#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "gc.h"



int newPos(char* layout,  int digitPos){
  int nr = 0;
  
  for(int i = digitPos; i < strlen(layout); i++){
    if(isdigit(layout[i])){
      nr++;
    }
    }
   return nr;
}

int returnDigit(char* layout, int digitPos){
  int nr = 0;
  
  for(int i = digitPos; i < strlen(layout); i++){
    if(isdigit(layout[i])){
      nr++;
    }
  }
  char stringValue[strlen(layout)];
  memcpy(stringValue, layout + digitPos, nr);
  return atoi(stringValue);
}

int formatStringToSize(char* layout){
  if(layout == NULL){
    puts("No formatstring to allocate");
    exit(0);
  }

  int p = 0;
  int k = 0;
  int f = 0;
  int d = 0;
  int l = 0;
  int c = 0;

  int length = strlen(layout);
  char array[6];
  array[0] = '*';
  array[1] = 'i';
  array[2] = 'f';
  array[3] = 'd';
  array[4] = 'l';
  array[5] = 'c';

  for(int i = 0; i < length; i++){
    printf("%d",i);
    if(isdigit(layout[i])){
      int value = returnDigit(layout, i);
      int newPosition = newPos(layout, i);
    if(layout[newPosition] == array[0]){
      p += value;
    }
    if(layout[newPosition] == array[1]){
      k += value;
    }
    if(layout[newPosition] == array[2]){
      f += value;
    }
    if(layout[newPosition] == array[3]){
      d += value;
    }
    if(layout[newPosition] == array[4]){
      l += value;
    }
    if(layout[newPosition] == array[5]){
      c += value;
    }
    i = newPosition;
    }
    else{
    if(layout[i] == array[0]){
      p++;
    }
    if(layout[i] == array[1]){
      k++;
    }
    if(layout[i] == array[2]){
      f++;
    }
    if(layout[i] == array[3]){
      d++;
    }
    if(layout[i] == array[4]){
      l++;
    }
    if(layout[i] == array[5]){
      c++;
    }
    }
  }
  int sizeOfLayout = p *(sizeof(void*))   + k * (sizeof(int)) + f * ( sizeof(float)) + d * (sizeof(double)) + l * (sizeof(long)) + c * (sizeof(char));
  return sizeOfLayout;

}



int main(int argc, char* argv[]){
 int print = formatStringToSize(argv[1]); 
 printf(" format strängens size: %d\n", print);
 return 0;
}
