#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>


#ifdef __sparc__
int SPARC = 1;
#else
int SPARC = 0;
#endif

/*
char* concateFormatString(int value, int size, char* rOrStar, char* headerString, int is64or32){
  int wholeSize = (value * size);
  int temp = wholeSize;{
    if(is64or32 == 0){ // 32bit platform
      if(wholeSize <= 4 && wholeSize > 0){ // If type can fit in a word
	strcat(headerString, rOrStar);
	return headerString;
      }
      wholeSize = wholeSize / 4; // r is 4 bytes
      for(int i = 0; i < wholeSize; i++){
	strcat(headerString, rOrStar);	
      }
      if (temp % 4 != 0){ // If any remainder, add to string
	strcat(headerString, rOrStar);
      }
    }
    if(is64or32 == 1){ // 64bit platform
      if(wholeSize <= 8 && wholeSize > 0){
	strcat(headerString, rOrStar);
	if(strcmp(rOrStar, "r") == 0){
	  strcat(headerString, rOrStar);
	}
	return headerString;
      }
      if(strcmp(rOrStar,"*") == 0){
	wholeSize /= 8; 
      }
      else{
	wholeSize /= 4;
      }
      for(int i = 0; i < wholeSize; i++){
	strcat(headerString, rOrStar);
      }
      if (temp % 8 != 0){
	strcat(headerString, rOrStar);
	strcat(headerString, rOrStar);
      }
    }
  }
  return headerString;
}
*/

int returnDigit(char* layout, int digitPos){
  assert(digitPos >= 0 && digitPos <= strlen(layout));
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


int checkForPointerDoubleLong(char* layout){
  for(int i = 0; i < strlen(layout); i++){
    if(sizeof(void*) == 8){
      if(layout[i] == 'l' || layout[i] == 'd' || layout[i] == '*'){
	return 1;
      }
    }
    else{
      if( layout[i] == 'd'){
	return 1;
      }
    }
  }
  return 0;
}

int lengthOfFormatStringToAllocate(char* layout){
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
  return sizeToAllocate;
}

char* formatStringWithoutDigits(char* formatString){
  char* returnformatStringWithoutDigits = calloc(lengthOfFormatStringWithoutDigitsToAllocate(formatString), 1);

  char charToString[2]; // for converting one char into a string used for strcat
  charToString[1] = '\0';
 
  for(int i = 0; i < strlen(formatString); i++){
    if(isdigit(formatString[i])){
      
      int numberOfChars = returnDigit(formatString, i); // the amount of chars to add to string
      int charPos = newPos(formatString, i); // position for next character to add
      charToString[0] = formatString[charPos];
      
      if(charPos == strlen(formatString)){
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


int totalPadding(char* layout){
  if(sizeof(void*) == 8){
    if(checkForPointerDoubleLong(layout) == 1){ // Check on which platform the program is run
      return 8;
    }
    else{
      return  4;
    }
  }
  if(sizeof(void*) == 4 && SPARC == 0){
    return  4;
  }
  if(SPARC == 1){
    if(checkForPointerDoubleLong(layout) == 1){
      return 8;
    }
    else{
      return 4;
    }
  }
  return 0;
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

int returnalignof(char type){
  if(sizeof(void*) == 4 && SPARC == 0){ // X86 == true
    if(returnsizeof(type) > 4) 
      return 4;
  }
  return returnsizeof(type);
}

//concatefeormatstring körs med (value, size, headerstring, rOrStar, isbit6432) i denna ordning
char* convertformatStringWithoutDigitsToHeaderString(char* formatString, char* headerString, int totalPadding){
  int sizeStar = sizeof(void*);
  int sizeR    = sizeof(int);
  //  int formatStringLength = strlen(formatstring);
  int previousSize = 0;
  
  int adress = 0;
  for(int i = 0; formatstring[i] != '\0';){
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
      i++;
    }
    while(adress-headerStringToSize(headerString)>= sizeR){
      strcat(headerString, "r");
    }
  }
  // padda ut strukten mot paddingen
  // bad way to do it, need to be fixed. lots of overhead atm
  strcat(headerString,"rr");

    /*
    if(size == 1){
      for(j = i; j < strlen(formatString); j++){
	
        if(){
	  counter++;
	}
	i = j;
      }
      
    }
    if(size == 4){
      if(is64or32 == 0){
	if(formatString[i] == '*'){
	  strcat(headerString, "*");
	}
	else{
	  strcat(headerString, "r");
	}
      }
      else{}
    }
    if(size == 8){
      if(formatString[i] == '*'){
	strcat(headerString, "r");
      }
      else{}
    }
    */
  }
  return headerString;
}


char* formatStringToHeaderString(char* layout ){
  if(layout == NULL){
    puts("No formatstring to allocate");
    exit(0);
  }
  
  char* formatString = formatStringWithoutDigits(layout);
  char* headerString = calloc(lengthOfFormatStringToAllocate(layout),1);

  int padding = totalPadding(layout); // 1 if its 64 bits 8-bit padding, else 0 then its 32bit so 4-bit padding
  
  char* returnHeaderString = convertformatStringWithoutDigitsToHeaderString(formatString, headerString, padding);
 
  free(formatString);
  return returnHeaderString
}





int main(int argc, char* argv[]){
  char* print1 = formatStringWithoutDigits(argv[1]);
  int print2 = lengthOfFormatStringWithoutDigitsToAllocate(argv[1]);
  char* print3 = formatStringToHeaderString(argv[1]);
  printf(" formatstring without digits length to allocate %d\n formatstring without digits: %s\n formatString to headerString: %s\n",print2, print1, print3);
  
  return 0;
}

 
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
