#ifndef __STRING_UTIL__
#define __STRING_UTIL__

/**
 *Given a formatstring, converts the string into a headerstring that describes the memorylayout.
 *If no string is given, terminate the program.
 *@param The formatstring to be converted.
 *@return Returns a headerstring.
 */

char* formatStringToHeaderString(char* layout); 

size_t headerStringToSize(char* layout);

int returnDigit(char* string, int digitPos);

int newPos(char* string, int currentpost);

int checkForPointerDoubleLong(char* string);

char* concateFormatString(int value, char* headerString, int size, char* rOrStar, int is64or32);

int lenghtOfFormatStringToAllocate(char* layout);


#endif
