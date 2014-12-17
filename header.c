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
#define TOKENS_PER_POINTER ((sizeof(void*) * 4) / BITS_PER_TOKEN)

/**
 * Defines the bit representation of the bitvector terminator.
 */
#define TERMINATOR_TOKEN 0b01

/**
 * Bit representation of the pointer token.
 */
#define POINTER_TOKEN 0b11

/**
 * Bit representation of the int token.
 */
#define INT_TOKEN 0b00

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
	bool useVector = strlen(string) <= (TOKENS_PER_POINTER - 4);
	
	if(useVector) {
		int i = 0;
		intptr_t header = 0;
		
		while(string[i] != '\0'){
			
			if(string[i] == '*') {
				header |= POINTER_TOKEN;
			}
			else {
				header |= INT_TOKEN;
			}
			
			header <<= 2;
			i++;
		}
		
		// Terminate the bitvector.
		header |= TERMINATOR_TOKEN;
		
		// Make sure the header is properly shifted.
		// Subtract one to account for the terminating bits.
		while(i++ < TOKENS_PER_POINTER - 1) {
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
			for(int i = TOKENS_PER_POINTER * BITS_PER_TOKEN - BITS_PER_TOKEN; i >= 2; i -= 2) {
				
				intptr_t shifted = ((intptr_t) 0b11) << i;
				
				intptr_t bits = ((intptr_t) header) & shifted;
				bits = (bits >> i) & 0b11;
				
				if(bits == TERMINATOR_TOKEN) {
					break; // Stop the loop.
				}
				
				switch(bits) {
					case INT_TOKEN:
						antal_r += 1;
						break;
					case POINTER_TOKEN:
						antal_p += 1;
						break;
					case TERMINATOR_TOKEN:
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