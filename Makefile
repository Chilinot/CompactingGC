all: test_all

# Tex settings
CC     = gcc
CFLAGS = -ggdb -Wall -std=c99

# Clean settings
GEN_EXTENSIONS = *.o *.out

test_all: test_header test_heap test_heapIterator test_linkedlist

clean:
	rm -f $(GEN_EXTENSIONS) unittests *.orig

%:	%.c
	$(CC) $(CFLAGS) $< -o $@

test_header: header.c header.h header_tests.c string_util/string_util.c string_util/string_util.h heap.c heap.h heap_rep.h
	$(CC) $(CFLAGS) header_tests.c header.c string_util/string_util.c heap.c -o header_unittests -lcunit
	./header_unittests

test_heap: heap.c heap_rep.h heap.h heap_tests.c header.h header.c string_util/string_util.c string_util/string_util.h debug.c debug.h
	$(CC) $(CFLAGS) heap_tests.c heap.c header.c string_util/string_util.c debug.c -o heap_unittests -lcunit
	./heap_unittests

test_heapIterator: heapIterator.c heapIterator.h heapIterator_tests.c header.c header.h string_util/string_util.c string_util/string_util.h heap.c heap.h heap_rep.h
	$(CC) $(CFLAGS) heapIterator.c heapIterator_tests.c header.c string_util/string_util.c heap.c -o heapIterator_unittests -lcunit
	./heapIterator_unittests

test_linkedlist: linkedlist.c linkedlist.h linkedlist_tests.c
	$(CC) $(CFLAGS) linkedlist.c linkedlist_tests.c -o linkedlist_unittests -lcunit
	./linkedlist_unittests

test_stack: stack.c stack.h stack_tests.c
	$(CC) $(CFLAGS) stack.c stack_tests.c -o stack_unittests -lcunit
	./stack_unittests
