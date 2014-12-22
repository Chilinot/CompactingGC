all: test_all

# Tex settings
C_COMPILER   = gcc
C_OPTIONS    = -ggdb -Wall -std=c99

# Clean settings
GEN_EXTENSIONS = *.o *.out

test_all: test_header test_heap

clean:
	rm -f $(GEN_EXTENSIONS) unittests *.orig

%:	%.c
	$(C_COMPILER) $(C_OPTIONS) $< -o $@
	
test_header: header.c header.h header_tests.c
	$(C_COMPILER) $(C_OPTIONS) header_tests.c header.c -o header_unittests -lcunit
	./header_unittests
	
test_heap: heap.c heap_rep.h heap.h
	$(C_COMPILER) $(C_OPTIONS) heap_tests.c heap.c -o heap_unittests -lcunit
	./heap_unittests
