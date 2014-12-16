#include <stdint.h>
#include "header.h"



void* header_clearHeaderTypeBits(void* header) {
	intptr_t cast_header = (intptr_t) header;
	//cast_header &= ~(1 << 0);
	//cast_header &= ~(1 << 1);
	cast_header &= ~(0b11); // sätter de två minst signifkanta bitarna noll
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
	
	return ERROR;
}

void* header_forwardingAddress(void* pointer) {
	intptr_t cast_pointer = (intptr_t) pointer;
	cast_pointer |= 1;
	return (void*) cast_pointer;
}
