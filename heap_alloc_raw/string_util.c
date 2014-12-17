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
 * Searches for integers in a row in a substring until end of string or a non-integer item is found
 * and converts the string of integers to an integer. 
 *@param layout The formatstring.
 *@param digitPos Position of the first integer in the substring of the formatstring.
 *@return Returns the converted value of the substring.  
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


/**
 * Searches from current position after non-integer or until end of string and returns that
 * position
 *@param layout The formatstring
 *@param currentPos Current position in the formatstring.
 *@return Returns the position of the next non-integer of the string.
 */

int newPos(char* layout, int currentPos){
  int i;
  int newPos;
  for(i = currentPos; i < strlen(layout); i++){
      if(isdigit(layout[i])){
      }
      else{
	newPos = i;
	return newPos;
      }
  }
  newPos = i;
  return newPos;
}

/**
 *Given a formatstring, converts the string into a headerstring that describes the memorylayout.
 *If no string is given, terminate the program.
 *@param The formatstring to be converted.
 *@return Returns a headerstring.
 */


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
      if(length == newPosition){
	concateFormatString(value, headerString, 1, r);
	return headerString;
      }
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
