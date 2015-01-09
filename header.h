#ifndef __HEADER__
#define __HEADER__

#include <stdlib.h>

/**
 * The opaque data type holding all the heap data
 */
typedef struct heap_s* Heap;

/**
 * The signature of the trace function
 */
typedef void* (*trace_f)(Heap h, void* obj);

/**
 * The signature of object-specific trace functions. It will be
 * called for its specific objects, and be given a generic trace
 * function f to be called on each pointer inside obj.
 */
typedef void* (*s_trace_f)(Heap h, trace_f f, void* obj);

/**
 * Used to determine the type of the header.
 */
typedef enum {
    POINTER_TO_STRING,
    FORWARDING_ADDRESS,
    FUNCTION_POINTER,
    BITVECTOR,
    ERROR // Returned if an error occured when getting the header type.
} header_type;

/**
 * Returns a compact version of the string (aka bitvector) or a pointer to
 * a copy of the string on the heap if the string will not fit inside a single void pointer.
 *
 * The least significant bits of the returned pointer shows if it is a bitvector or pointer.
 * If the two last bits (little-endian) are equal to 00 then it is a pointer.
 * If they are equal to 11 then it is a bitvector.
 * 
 * Allowed characters in the string is:
 *  r - To represent sizeof(int)
 *  * - To represent sizeof(void*)
 *
 * @param string - The string to base the header on.
 * @return The header created.
 */
void* header_fromFormatString(char* string);

/**
 * Creates a header that is a forwarding address.
 *
 * @param pointer - The pointer the header should be based on.
 * @return The created header.
 */
void* header_forwardingAddress(void* pointer);

/**
 * Takes a pointer to an object specific garbage collection function
 * and returns a header pointing to said function.
 *
 * @param function - The function the header should point to.
 * @return The created header.
 */
void* header_objectSpecificFunction(s_trace_f function);

/**
 * Removes the two bits that indicate the type of the header.
 *
 * @param header - The header to clear.
 * @return The now clean header.
 */
void* header_clearHeaderTypeBits(void* header);

/**
 * Returns the type of the given header.
 *
 * @param header - The header to determine the type of.
 * @return The type of the given header.
 */
header_type header_getHeaderType(void* header);

/**
 * Returns the size of the object defined in the header.
 *
 * @param header - The header to read.
 * @return The size "hidden" in the header.
 */
size_t header_getSize(void* header);

/**
 * f anropas med alla pekare som headerns objekt har,
 * där pekare som functionen anropas med beskriver hur mycket ifrån objektets adress pekare verkligen är,
 * Objektet är den data som header beskriver och hör till.
 *
 *
 * @param header en pekare
 * @param f en funktion
 */
void header_pointerIterator(void* header, void (*f)(void*));

#endif

