#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include "header.h"
#include "heap.h"
#include "string_util.h"


 // Defines number of bits per token.
#define BITS_PER_TOKEN 2

 // Defines the amount of chars we can store in a bitvector.
#define TOKENS_PER_POINTER ((sizeof(void*) * 8) / BITS_PER_TOKEN)

 // Defines the bit representation of the bitvector terminator.
#define TERMINATOR_TOKEN 0b01

 // Bit representation of the pointer token.
#define POINTER_TOKEN 0b11

 // Bit representation of the int token.
#define INT_TOKEN 0b00

// Removes two bits that indicate the type of the header.
void* header_clearHeaderTypeBits(void* header) {
	intptr_t cast_header = (intptr_t) header;
	cast_header &= ~0b11;
	return (void*) cast_header;
}

// Returns the type of the given header.

header_type header_getHeaderType(void* header) {
	intptr_t cast_header = (intptr_t) header;

	cast_header &= 0b11; //tar ut de minst tv� signifikanta bitarna

	switch(cast_header) {
	case 0b00:
		return POINTER_TO_STRING;

	case 0b01:
		return FORWARDING_ADDRESS;

	case 0b10:
		return FUNCTION_POINTER;

	case 0b11:
		return BITVECTOR;

	default:
		return ERROR;
	}

	// This statement should never be reached. It is just here as a precaution.
	return ERROR;
}

// Creates a header that is a forwarding adress.

void* header_forwardingAddress(void* pointer) {
	intptr_t cast_pointer = (intptr_t) pointer;
	cast_pointer |= 1;
	return (void*) cast_pointer;
}

// Returns a compact version of the string aka bitvector or a pointer to a copy of the string 
// on the heap if the string will not fit inside a single void-pointer 
// The least significant bits of the returned pointer shows if it is a bitvector or pointer. 
// If the two last bits (little endian) are equal to 00 then it is a pointer.
// If they are equal to 11 then it is a bitvector.

void* header_fromFormatString(Heap heap, char* string) {
	// True if the string will fit inside a void*-4 else false.
	// It subtracts four to make sure the bitvector terminator and the header type will fit.

	string = formatStringToHeaderString(string);

	bool useVector = strlen(string) <= (TOKENS_PER_POINTER - 4);

	if(useVector) {
		int i = 0;
		intptr_t header = 0;

		while(string[i] != '\0') {

			if(string[i] == '*') {
				header |= POINTER_TOKEN;
			}
			else {
				header |= INT_TOKEN;
			}

			header <<= BITS_PER_TOKEN;
			i++;
		}

		// Terminate the bitvector.
		header |= TERMINATOR_TOKEN;

		// Make sure the header is properly shifted.
		// Subtract one to account for the terminating bits.
		while(i++ < TOKENS_PER_POINTER - 1) {
			header <<= BITS_PER_TOKEN;
		}

		// Mark the two type bits as a bitvector.
		header |= 0b11;

		free(string);

		return (void*) header;
	}
	else {
		// Return a copy of the string allocated on the real heap.
		char* string_copy = heap_allocate_raw(heap, strlen(string) + 1);
		strcpy(string_copy, string);

		free(string);

		return (void*) string_copy;
	}
}

// Takes a pointer to an object specific garbagecollection function and returns a header pointing to a said
// function.

void* header_objectSpecificFunction(s_trace_f function) {
	intptr_t ptr = (intptr_t) function;
	ptr |= 0b10;
	return (void*) ptr;
}

// Returns the size of the object in the header.

size_t header_getSize(void* header) {
	int antal_r = 0;
	int antal_p = 0;

	switch(header_getHeaderType(header)) {
	case BITVECTOR:
		for(int i = TOKENS_PER_POINTER * BITS_PER_TOKEN - BITS_PER_TOKEN; i >= 2; i -= 2) {

			intptr_t shifted = ((intptr_t) 0b11) << i;

			intptr_t bits = ((intptr_t) header) & shifted;
			bits = (bits >> i) & 0b11;

			if(bits == TERMINATOR_TOKEN) {
				break; // Stop the loop.
			}

			switch(bits) {
			case INT_TOKEN:
				++antal_r;
				break;

			case POINTER_TOKEN:
				++antal_p;
				break;

				// This is only reached if the header is not properly formatted.
			default:
				return 0;
			}
		}

		break;

	case POINTER_TO_STRING:
		header = header_clearHeaderTypeBits(header);
		char* string = (char*) header;

		for(int i = 0; string[i] != '\0'; i++) {
			if(string[i] == '*') {
				++antal_p;
			}
			else if(string[i] == 'r') {
				++antal_r;
			}
		}

		break;

	default:
		return 0;
	}

	return (sizeof(int) * antal_r) + (sizeof(void*) * antal_p);
}

// f anropas med alla pekare som headerns objekt har,
// där pekare som functionen anropas med beskriver hur mycket ifrån objektets adress pekare verkligen är,
// Objektet är den data som header beskriver och hör till.

void header_pointerIterator(void* header, void (*f)(void*)) {
	char* cursor = 0;

	switch(header_getHeaderType(header)) {
	case BITVECTOR:
		for(int i = TOKENS_PER_POINTER * BITS_PER_TOKEN - BITS_PER_TOKEN; i >= 2; i -= 2) {
			intptr_t shifted = ((intptr_t) 0b11) << i; // varfor??

			intptr_t bits = ((intptr_t) header) & shifted;
			bits = (bits >> i) & 0b11;

			if(bits == TERMINATOR_TOKEN) {
				break; // Stop the loop.
			}

			switch(bits) {
			case INT_TOKEN:
				cursor += sizeof(int) / sizeof(char);
				break;

			case POINTER_TOKEN:
				(*f)((void*)(cursor));
				cursor += sizeof(void*) / sizeof(char);
				break;

				// This is only reached if the header is not properly formatted.
			default:
				return;
			}
		}

		break;

	case POINTER_TO_STRING:
		header = header_clearHeaderTypeBits(header);
		char* string = (char*) header;

		for(int i = 0; string[i] != '\0'; i++) {
			switch(string[i]) {
			case 'r':
				cursor += sizeof(int) / sizeof(char);
				break;

			case '*':
				(*f)((void*)(cursor));
				cursor += sizeof(void*) / sizeof(char);
				break;
			}
		}

		break;

	default:
		return;
	}

	return;
}

// Takes the given header and returns the same header but with the typebits set according to the given type.

void* header_setHeaderType(void* header, header_type type) {

	intptr_t ptr = (intptr_t) header;

	// First we need to clear the type bits.
	ptr = header_clearHeaderTypeBits(ptr);

	// Now we re set them according to the given type.
	switch(type) {
	case POINTER_TO_STRING:
		ptr |= 0b00;
		break;

	case FORWARDING_ADDRESS:
		ptr |= 0b01;
		break;

	case FUNCTION_POINTER:
		ptr |= 0b10;
		break;

	case BITVECTOR:
		ptr |= 0b11;
		break;

	default:
		// ERROR
		return NULL;
	}

	return ptr;
}

