#ifndef __DEBUG__
#define __DEBUG__

#include <stdlib.h>

/**
 * This function is copied from the following address:
 * http://stackoverflow.com/questions/111928/is-there-a-printf-converter-to-print-in-binary-format
 *
 * It is only used for debugging.
 */
void printBits(size_t const size, void const* const ptr);

#endif
