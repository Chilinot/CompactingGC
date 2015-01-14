#ifndef __STRING_UTIL__
#define __STRING_UTIL__

#include <stdlib.h>

/**
 *Given a formatstring, converts the string into a headerstring that describes the memorylayout.
 *If no string is given, terminate the program. empty strings will return an empty string.
 *@param The formatstring to be converted.
 *@return Returns a headerstring allocated on the heap.
 */

char* formatStringToHeaderString(char* layout); 

/* functions to test below */

/**
 *Given a formatstring converts the string to a equivalent formatstring without digits
 *@param formatString formatstring to be converted
 *@return A formatstring cotaining no digits
 */

char* formatStringWithoutDigits(char* formatString);


/**
 *returns the integer value in a string starting from digitpos ex. i23f, if digitPos is at index 1 the function will return 23.
 *@param layout the string to find the integer
 *@param digitPos position of the first integer
 */

int returnDigit(char* layout, int digitPos);

/**
 * finds the index after an integer in a string. ex.
 i23f if currentPos is at index 1 the function will return 4.
 *@param layout the string to find the new position
 *@param currentPos the position of the first integer.
 */

int newPos(char* layout, int currentPos);

/**
 *Calculates the size of a headerstring
 *@param layout the headerstring
 *@return size of the headerstring
 */

size_t headerStringToSize(char* layout);



#endif
