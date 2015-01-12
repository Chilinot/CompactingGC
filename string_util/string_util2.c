#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <ctype.h>
#include <stdint.h>
#include <stdbool.h>
#include "string_util2.h"


int returnDigit(char* layout, int digitPos){
  if(isdigit(layout[digitPos])== false) {return 0;}

  assert(digitPos >= 0 && digitPos <= strlen(layout));
  int counter = 0;
  for(int i = digitPos; i < strlen(layout) ; i++){
    if(isdigit(layout[i])){
      counter++;
    }
    else
      break;
  }
  
  char stringValue[strlen(layout)];
  memcpy(stringValue, layout + digitPos, counter);
  stringValue[digitPos+counter] = '\0';
  return atoi(stringValue);
}



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


int lengthOfFormatStringToAllocate(char* layout){ // some overhead here 
  int headerLength = 0;
  for(int i = 0; i < strlen(layout); i++){
    if isdigit(layout[i]){
	headerLength += returnDigit(layout, i) *2;
	i = newPos(layout, i);
      }
    else{
      headerLength += 2;
    }
  }
  return headerLength;
}


int lengthOfFormatStringWithoutDigitsToAllocate(char* formatString){
  int sizeToAllocate = 0;
  int newpos = 0;
  int oneCharacter = 1;
  for(int i = newpos; i < strlen(formatString); i++){
    if(isdigit(formatString[i])){
      sizeToAllocate += returnDigit(formatString, i);
      newpos = newPos(formatString, i);
    
    }
    else{
      sizeToAllocate += oneCharacter;
    }
  }
  return sizeToAllocate + 1; //incase of when there are only chars and we want to add the NULL 
}

char* formatStringWithoutDigits(char* formatString){
  char* returnformatStringWithoutDigits = calloc(lengthOfFormatStringWithoutDigitsToAllocate(formatString), sizeof(char));

  char charToString[2]; // for converting one char into a string used for strcat
  charToString[1] = '\0';
 
  for(int i = 0; i < strlen(formatString); i++){
    if(isdigit(formatString[i])){
      
      int numberOfChars = returnDigit(formatString, i); // the amount of chars to add to string
      int charPos = newPos(formatString, i); // position for next character to add
      charToString[0] = formatString[charPos];
      
      if(charPos == strlen(formatString)){//if there are only digits in formatString
	for(int k = 0; k < numberOfChars; k++){
	  strcat(returnformatStringWithoutDigits, "c");
	}
	return returnformatStringWithoutDigits;
      }
      
      for(int j = 0; j < numberOfChars; j++){
	strcat(returnformatStringWithoutDigits, charToString);
      }
      i = charPos;
    }
    else{
      charToString[0] = formatString[i];
      strcat(returnformatStringWithoutDigits, charToString);
	
    }
  }

  return returnformatStringWithoutDigits;
}




int returnsizeof(char character){
  if(character == 'i'){
    return sizeof(int);
  }
  if(character == 'c'){
    return sizeof(char);
  }
  if(character == '*'){
    return sizeof(void*);
  }
  if(character == 'd'){
    return sizeof(double);
  }
  if(character == 'l'){
    return sizeof(long);
  }
  if(character == 'f'){
    return sizeof(float);
  }
  return 0;
}


#define RETURNALIGNOF(type) offsetof(struct {char a:1; type b;}, b)

size_t returnalignof(char character){
  if(character == 'i'){
    return RETURNALIGNOF(int);
  }
  if(character == 'c'){
    return RETURNALIGNOF(char);
  }
  if(character == '*'){
    return RETURNALIGNOF(void*);
  }
  if(character == 'd'){
    return RETURNALIGNOF(double);
  }
  if(character == 'l'){
    return RETURNALIGNOF(long);
  }
  if(character == 'f'){
    return RETURNALIGNOF(float);
  }
  return 0;
}



#define max(a,b) a>b ? a : b
char* convertformatStringWithoutDigitsToHeaderString(char* formatString, char* headerString){
  int sizeStar = sizeof(void*);
  int sizeR    = sizeof(int);
  //  int formatStringLength = strlen(formatstring);
 
  int totalPadding = 0;
  int adress = 0;
  for(int i = 0; formatString[i] != '\0';){
    char currentChar = formatString[i];
    int size = returnsizeof(currentChar);
    
    if(adress % returnalignof(currentChar)  != 0) { //inte tillåtet att lägga currentchar typ på 
	adress++;
      }

    else{ // tillåten adreess för typen av currentChar
      adress += size;
      if(currentChar == '*'){
	strcat(headerString, "*");
      }
      totalPadding = max(returnalignof(currentChar), totalPadding);
      i++;
    }
    while(adress-headerStringToSize(headerString)>= sizeR){
      strcat(headerString, "r");
    }
  }
  // padda ut strukten mot paddingen
  adress += ((totalPadding-(adress%totalPadding))%totalPadding);
  while(adress > headerStringToSize(headerString)){
      strcat(headerString, "r");
  }
  return headerString;
}


char* formatStringToHeaderString(char* layout ){
  if(layout == NULL){
    puts("No formatstring to allocate");
    exit(0);
  }
  if(layout[0] == '\0') return (char*) calloc(1,1);
  
  char* formatString = formatStringWithoutDigits(layout);
  char* headerString = calloc(lengthOfFormatStringToAllocate(layout),sizeof(char));

  char* returnHeaderString = convertformatStringWithoutDigitsToHeaderString(formatString, headerString);
 
  free(formatString);
  return returnHeaderString;
}




#ifdef MANUAL_TEST 
int main(int argc, char* argv[]){
  char* print1 = formatStringWithoutDigits(argv[1]);
  int print2 = lengthOfFormatStringWithoutDigitsToAllocate(argv[1]);
  char* print3 = formatStringToHeaderString(argv[1]);
  printf(" formatstring without digits length to allocate %d\n formatstring without digits: %s\n formatString to headerString: %s\n",print2, print1, print3);
  
  printf("returndigit test %d\n",returnDigit("2i3c1f*52l", 3));


  return 0;
}
#endif

 
 size_t headerStringToSize(char* layout){
  
   switch(*layout){
   case 'r':
     return sizeof(int) + headerStringToSize(layout + 1);
   case '*':
     return sizeof(void*) + headerStringToSize(layout + 1);
   case '\0':
     return 0;
   }

   return 0; // should not happen

 }
