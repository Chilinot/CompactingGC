#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "gc.h"


/**
 * Concatinates a '*' or a 'r' on to the headerstring depending on platform,
 * number of items and size of item.
 *@param value Number of items.
 *@param headerString String on which to concatinate.
 *@param size Size of the item.
 *@param rOrStar '*' or 'r' wheter if the item is a void* or not. 
 *@return Returns the concatinated string.
 */

char* concateFormatString(int value, char* headerString, int size, char* rOrStar){
  int wholeSize = (value * size);
  int temp = wholeSize;
  if(wholeSize <= 4){
    strcat(headerString, rOrStar);
  }
  else{
    if(sizeof(void*) == 4){
      wholeSize = wholeSize / 4;
      for(int i = 0; i < wholeSize; i++){
	strcat(headerString, rOrStar);	
      }
      if (temp % 4 != 0){
	strcat(headerString, rOrStar);
      }
    }
    if(sizeof(void*) == 8){
      if(wholeSize < 8){
	strcat(headerString, rOrStar);
      }
      wholeSize = wholeSize / 8;
      for(int i = 0; i < wholeSize; i++){
	strcat(headerString, rOrStar);
      }
      if (temp % 8 != 0){
	strcat(headerString, rOrStar);
      }
    }

  }
  return headerString;
}

/**
 *
 *@param
 *@param
 *@return
 */

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


int newPos(char* layout, int currentPos){
  int newPos;
  for(int i = currentPos; i < strlen(layout); i++){
    if(isdigit(layout[i])){
    }
    else{
      newPos = i;
      break;
    }
  }
  return newPos;
}

char* formatStringToHeaderString(char* layout){
  char* headerString;
  if(sizeof(void*) == 4){
    headerString = calloc(32, 4);
  }
  if(sizeof(void*) == 8){
    headerString = calloc(64, 8);
  }
  if(layout == NULL){
    puts("No formatstring to allocate");
    exit(0);
  }
  char* r = "r";
  char* star = "*";
  int length = strlen(layout);  
  int value;
  for(int newPosition = 0; newPosition < length; newPosition++){
    if(isdigit(layout[newPosition])){
      value = returnDigit(layout, newPosition);
      newPosition = newPos(layout, newPosition);
    }
    else{
      value = 1;
    }
      if(layout[newPosition] == '*') {
	int size = sizeof(void*);
	concateFormatString(value, headerString, size, star); 
      }
      if(layout[newPosition] == 'c') {
	if (layout[newPosition + 1] == 'c'){
	  newPosition++;
	}
	if (layout[newPosition + 1] == 'c'){
	  newPosition++;
	}
      	if (layout[newPosition + 1] == 'c'){
	  newPosition++;
	}
	int size = sizeof(char);
	concateFormatString(value, headerString, size, r); 
      }
      if(layout[newPosition] == 'l') {
	int size = sizeof(long);
	concateFormatString(value, headerString, size, r); 
      }
      if(layout[newPosition] == 'i') {
	int size = sizeof(int);
	concateFormatString(value, headerString, size, r); 
      }
      if(layout[newPosition] == 'd') {
	int size = sizeof(double);
	concateFormatString(value, headerString, size, r); 
      }
      if(layout[newPosition] == 'f') {
	int size = sizeof(float);
	concateFormatString(value, headerString, size, r); 
      }
    }
  return headerString;
}

int main(int argc, char* argv[]){
   char* test2;
   test2 = formatStringToHeaderString("3*3i*c");
  printf("%s\n", test2);
  return 0;
}
