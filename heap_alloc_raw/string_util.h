#ifndef __STRING_UTIL__
#define __STRING_UTIL__

/**
 *Given a formatstring, converts the string into a headerstring that describes the memorylayout.
 *If no string is given, terminate the program.
 *@param The formatstring to be converted.
 *@return Returns a headerstring.
 */

char* formatStringToHeaderString(char* layout); 


#endif
