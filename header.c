#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include "header.h"

/**
 * Defines number of bits per token.
 */
#define BITS_PER_TOKEN 2

/**
 * Defines the amount of chars we can store in a bitvector.
 */
#define TOKENS_IN_POINTER ((sizeof(void*) * 4) / BITS_PER_TOKEN)


/**
 * Defines the bit representation of the bitvector terminator.
 */
#define TOKEN_TERMINATOR 0b01

/**
 * Bit representation of the pointer token.
 */
#define TOKEN_POINTER 0b11

/**
 * Bit representation of the int token.
 */
#define TOKEN_INT 0b00

void* header_clearHeaderTypeBits(void* header) {
	intptr_t cast_header = (intptr_t) header;
	cast_header &= ~0b11;
	return (void*) cast_header;
}

header_type header_getHeaderType(void* header) {
	intptr_t cast_header = (intptr_t) header;
	
	cast_header &= 0b11; //tar ut de minst två signifikanta bitarna  

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

void* header_forwardingAddress(void* pointer) {
	intptr_t cast_pointer = (intptr_t) pointer;
	cast_pointer |= 1;
	return (void*) cast_pointer;
}

void* header_fromFormatString(char* string) {
	// True if the string will fit inside a void*-4 else false.
	// It subtracts four to make sure the bitvector terminator and the header type will fit.
	bool useVector = strlen(string) <= (TOKENS_IN_POINTER - 4);
	
	if(useVector) {
		int i = 0;
		intptr_t header = 0;
		
		// Add ones to the header for each '*' in the string.
		while(string[i] != '\0'){
			// If the current char is a pointer char.
			if(string[i] == '*') {
				header |= 0b11;
			}
			
			header <<= 2;
			i++;
		}
		
		// Terminate the bitvector.
		header |= TOKEN_TERMINATOR;
		
		// Make sure the header is properly shifted.
		// Subtract one to account for the terminating bits.
		while(i++ < TOKENS_IN_POINTER - 1) {
			header <<= 2;
		}
		
		// Mark the two type bits as a bitvector.
		header |= 0b11;
		
		return (void*) header;
	}
	else {
		// Return a copy of the string allocated on the real heap.
		return (void*) strdup(string);
	}
}

void* header_objectSpecificFunction(s_trace_f function) {
	intptr_t ptr = (intptr_t) function;
	ptr |= 0b10;
	return (void*) ptr;
}

size_t header_getSize(void* header) {
	int antal_r = 0;
	int antal_p = 0;
	
	switch(header_getHeaderType(header)) {
		case BITVECTOR:
			for(int i = TOKENS_IN_POINTER * BITS_PER_TOKEN - BITS_PER_TOKEN; i >= 2; i -= 2) {
				
				intptr_t shifted = ((intptr_t) 0b11) << i;
				
				intptr_t bits = ((intptr_t) header) & shifted;
				bits = (bits >> i) & 0b11;
				
				if(bits == TOKEN_TERMINATOR) {
					break; // Stop the loop.
				}
				
				switch(bits) {
					case TOKEN_INT:
						antal_r += 1;
						break;
					case TOKEN_POINTER:
						antal_p += 1;
						break;
					case TOKEN_TERMINATOR:
						break;
						
					// This is only reached if the header is not properly formatted.
					default:
 						return 0;
				}
			}
			break;
		
		case POINTER_TO_STRING:
			break;
			
		default:
			break;
	}

	return (sizeof(int) * antal_r) + (sizeof(void*) * antal_p);
}