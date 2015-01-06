all: test_all

# Tex settings
C_COMPILER   = gcc
C_OPTIONS    = -ggdb -Wall -std=c99

# Clean settings
GEN_EXTENSIONS = *.o *.out

test_all: test_header test_heap test_heapIterator test_linkedlist

clean:
	rm -f $(GEN_EXTENSIONS) unittests *.orig

%:	%.c
	$(C_COMPILER) $(C_OPTIONS) $< -o $@
	
test_header: header.c header.h header_tests.c
	$(C_COMPILER) $(C_OPTIONS) header_tests.c header.c -o header_unittests -lcunit
	./header_unittests
	
test_heap: heap.c heap_rep.h heap.h heap_tests.c
	$(C_COMPILER) $(C_OPTIONS) heap_tests.c heap.c -o heap_unittests -lcunit
	./heap_unittests

test_heapIterator: heapIterator.c heapIterator.h heapIterator_tests.c
	$(C_COMPILER) $(C_OPTIONS) heapIterator.c heapIterator_tests.c -o heapIterator_unittests -lcunit
	./heapIterator_unittests
	
test_linkedlist: linkedlist.c linkedlist.h linkedlist_tests.c
	$(C_COMPILER) $(C_OPTIONS) linkedlist.c linkedlist_tests.c -o linkedlist_unittests -lcunit
	./linkedlist_unittests
	
test_stack: stack.c stack.h stack_tests.c
	$(C_COMPILER) $(C_OPTIONS) stack.c stack_tests.c -o stack_unittests -lcunit
	./stack_unittests
