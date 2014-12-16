#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "header.h"

void* header_clearHeaderTypeBits(void* header) {
	intptr_t cast_header = (intptr_t) header;
	cast_header &= ~0b11;
	return (void*) cast_header;
}

header_type header_getHeaderType(void* header) {
	intptr_t cast_header = (intptr_t) header;
	
	cast_header &= 0b11;
	
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
	// Defines the char for a pointer.
	static char p = '*'; 
	
	// True if the string will fit inside a void*-2 else false.
	bool useVector = strlen(string) <= ((sizeof(void*) * 8) - 2);
	
	if(useVector) {
		int i = 0;
		intptr_t header = 0;
		
		// Add ones to the header for each 'p' in the string.
		while(string[i] != '\0'){
			header <<= 1;
			
			// If the current char is a pointer char.
			if(string[i] == p) {
				header |= 1; // Add a one to the header.
			}
			
			i++;
		}
		
		// Make sure the header is properly shifted.
		while(i++ < (sizeof(void*) * 8)) {
			header <<= 1;
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
