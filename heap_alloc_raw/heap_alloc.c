#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "gc.h"

char* concateFormatString(int value, char* concatedString, int size, char* rOrStar){
  int wholeSize = (value * size);
  if(wholeSize <= 4){
    strcat(concatedString, rOrStar);
}
  else{
    if(sizeof(void*) == 4){
      wholeSize = wholeSize / 4;
      for(int i = 0; i < wholeSize; i++){
	strcat(concatedString, rOrStar);	
      }
      if (wholeSize % 4 != 0){
	strcat(concatedString, rOrStar);
      }
    }
    if(sizeof(void*) == 8){
     wholeSize = wholeSize / 8;
      for(int i = 0; i < wholeSize; i++){
	strcat(concatedString, rOrStar);
      }
      if (wholeSize % 8 != 0){
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


/*
int formatStringToSize(char* layout){
    if(sizeof(void*) == 4){
      char* headerString = calloc(120);
    }
    if(sizeof(void*) == 8){
      char* headerString = calloc(8 * 62);
	}
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
	concatedFormatString(value, headerString, size, star); 
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


}
*/
int main(int argc, char* argv[]){
  int i =    sizeof(void*);
  int i2 =   sizeof(int);
  int i3 =   sizeof(long);
  int i4 =   sizeof(double);
  int i5 =   sizeof(float);
  int i6 =   sizeof(char);
  char* test = malloc(120);
  concateFormatString(7, test, 1, "r");
  printf("void : %d\n int: %d\n long: %d\n double: %d\n float: %d\n char: %d\n test: %s\n ",i, i2, i3, i4, i5, i6, test);
return 0;
}
