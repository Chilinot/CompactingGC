#ifndef __HEADER__
#define __HEADER__

#include <stdlib.h>

/**
 * Returns the size defined in the header.
 * @param header - The header to read.
 * @return The size "hidden" in the header.
 */
size_t header_getSize(void* header);

#endif
