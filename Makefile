all: test_all

# Tex settings
CC     = gcc
CFLAGS = -ggdb -Wall -std=c99

SRC_FOLDER    = src
TARGET_FOLDER = target

# Clean settings
GEN_EXTENSIONS = *.o *.out

test_all: test_header test_heap test_heapIterator test_linkedlist

clean:
	rm -f $(GEN_EXTENSIONS) unittests *.orig

%:	%.c
	$(CC) $(CFLAGS) $< -o $@
	
build: $(SRC_FOLDER)/*
	$(CC) $(CFLAGS) $(SRC_FOLDER)/gc.c $(SRC_FOLDER)/header.c $(SRC_FOLDER)/heap.c $(SRC_FOLDER)/heapIterator.c $(SRC_FOLDER)/stack.c $(SRC_FOLDER)/string_util.c -o $(TARGET_FOLDER)/gc.o

# test_header: $(SRC_FOLDER)header.c $(SRC_FOLDER)header.h $(SRC_FOLDER)header_tests.c $(SRC_FOLDER)string_util/string_util.c $(SRC_FOLDER)string_util/string_util.h $(SRC_FOLDER)heap.c $(SRC_FOLDER)heap.h $(SRC_FOLDER)heap_rep.h
# 	$(CC) $(CFLAGS) $(SRC_FOLDER)header_tests.c $(SRC_FOLDER)header.c $(SRC_FOLDER)string_util/string_util.c $(SRC_FOLDER)heap.c -o $(TARGET_FOLDER)header_unittests -lcunit
# 	./$(TARGET_FOLDER)header_unittests
# 
# test_heap: $(SRC_FOLDER)heap.c $(SRC_FOLDER)heap_rep.h $(SRC_FOLDER)heap.h $(SRC_FOLDER)heap_tests.c $(SRC_FOLDER)header.h $(SRC_FOLDER)header.c $(SRC_FOLDER)string_util/string_util.c $(SRC_FOLDER)string_util/string_util.h $(SRC_FOLDER)debug.c $(SRC_FOLDER)debug.h
# 	$(CC) $(CFLAGS) $(SRC_FOLDER)heap_tests.c $(SRC_FOLDER)heap.c $(SRC_FOLDER)header.c $(SRC_FOLDER)string_util/string_util.c $(SRC_FOLDER)debug.c -o $(TARGET_FOLDER)heap_unittests -lcunit
# 	./$(TARGET_FOLDER)heap_unittests
# 
# test_heapIterator: $(SRC_FOLDER)heapIterator.c $(SRC_FOLDER)heapIterator.h $(SRC_FOLDER)heapIterator_tests.c $(SRC_FOLDER)header.c $(SRC_FOLDER)header.h $(SRC_FOLDER)string_util/string_util.c $(SRC_FOLDER)string_util/string_util.h $(SRC_FOLDER)heap.c $(SRC_FOLDER)heap.h $(SRC_FOLDER)heap_rep.h
# 	$(CC) $(CFLAGS) $(SRC_FOLDER)heapIterator.c $(SRC_FOLDER)heapIterator_tests.c $(SRC_FOLDER)header.c $(SRC_FOLDER)string_util/string_util.c $(SRC_FOLDER)heap.c -o $(TARGET_FOLDER)heapIterator_unittests -lcunit
# 	./$(TARGET_FOLDER)heapIterator_unittests
# 
# test_linkedlist: $(SRC_FOLDER)linkedlist.c $(SRC_FOLDER)linkedlist.h $(SRC_FOLDER)linkedlist_tests.c
# 	$(CC) $(CFLAGS) $(SRC_FOLDER)linkedlist.c $(SRC_FOLDER)linkedlist_tests.c -o $(TARGET_FOLDER)linkedlist_unittests -lcunit
# 	./$(TARGET_FOLDER)linkedlist_unittests
# 
# test_stack: $(SRC_FOLDER)stack.c $(SRC_FOLDER)stack.h $(SRC_FOLDER)stack_tests.c
# 	$(CC) $(CFLAGS) $(SRC_FOLDER)stack.c $(SRC_FOLDER)stack_tests.c -o $(TARGET_FOLDER)stack_unittests -lcunit
# 	./$(TARGET_FOLDER)stack_unittests
