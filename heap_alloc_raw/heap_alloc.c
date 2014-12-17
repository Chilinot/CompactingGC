#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "gc.h"

char* concateFormatString(int value, char* concatedString, int size, char* rOrStar){
  int wholeSize = (value * size);
  int temp = wholeSize;
  if(wholeSize <= 4){
    strcat(concatedString, rOrStar);
  }
  else{
    if(sizeof(void*) == 4){
      wholeSize = wholeSize / 4;
      for(int i = 0; i < wholeSize; i++){
	strcat(concatedString, rOrStar);	
      }
      if (temp % 4 != 0){
	strcat(concatedString, rOrStar);
      }
    }
    if(sizeof(void*) == 8){
      if(wholeSize <= 8){
	strcat(concatedString, rOrStar);
      }
      wholeSize = wholeSize / 8;
      for(int i = 0; i < wholeSize; i++){
	strcat(concatedString, rOrStar);
      }
      if (temp % 8 != 0){
	strcat(concatedString, rOrStar);
      }
    }

  }
  return concatedString;
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


int newPos(char* layout, int currentPos){
  int newPos;
  for(int i = currentPos; i < strlen(layout); i++){
    if(isdigit(layout[i])){
      i++;
    }
    else{
      newPos = i;
      break;
    }
  }
  printf("%d\n", newPos);
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
  for(int i = 0; i < length; i++){
    printf("%d",i);
    if(isdigit(layout[i])){
      int value = returnDigit(layout, i);
      int newPosition = newPos(layout, i);
      if(layout[newPosition] == '*') {
	int size = sizeof(void*);
	concateFormatString(value, headerString, size, star); 
      }
      if(layout[newPosition] == 'c') {
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
    else{
      int value = 1;
      int newPosition = newPos(layout, i);
      if(layout[newPosition] == '*') {
	int size = sizeof(void*);
	concateFormatString(value, headerString, size, star); 
      }
      if(layout[newPosition] == 'c') {
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
  }
  return headerString;
}

int main(int argc, char* argv[]){
  /*  int i =    sizeof(void*);
  int i2 =   sizeof(int);
  int i3 =   sizeof(long);
  int i4 =   sizeof(double);
  int i5 =   sizeof(float);
  int i6 =   sizeof(char);
  printf("void : %d\n int: %d\n long: %d\n double: %d\n float: %d\n char: %d\n test: %s\n ",i, i2, i3, i4, i5, i6, test); */
  // char* test2;
  //  test2 = formatStringToHeaderString("2*3i");
  //  printf("%s\n", test2);
  newPos("32i", 1);
  return 0;
}
