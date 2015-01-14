all: test_all

# MACROS
CC     = gcc
CFLAGS = -ggdb -Wall -std=c99

SRC_FOLDER    = src
TARGET_FOLDER = target
TEST_FOLDER   = tests

GEN_EXTENSIONS = *.o *.out

# GENERAL RULES
clean:
	rm -f $(GEN_EXTENSIONS) unittests *.orig

# Builds the garbage collector under the name "GarbageCollector.o" and places it in the target folder.
build: $(SRC_FOLDER)/gc.c $(SRC_FOLDER)/gc.h header.o heap.o heapIterator.o stack.o string_util.o
	$(CC) $(CFLAGS) -o $(TARGET_FOLDER)/GarbageCollector.o \
	$(SRC_FOLDER)/gc.c \
	$(SRC_FOLDER)/gc.h \
	$(TARGET_FOLDER)/header.o \
	$(TARGET_FOLDER)/heap.o \
	$(TARGET_FOLDER)/heapIterator.o \
	$(TARGET_FOLDER)/stack.o \
	$(TARGET_FOLDER)/string_util.o


# MODULES
debug.o: $(SRC_FOLDER)/debug.c $(SRC_FOLDER)/debug.h
	$(CC) $(CFLAGS) -c $(SRC_FOLDER)/debug.c -o $(TARGET_FOLDER)/debug.o

header.o: $(SRC_FOLDER)/header.c $(SRC_FOLDER)/header.h $(SRC_FOLDER)/heap.h $(SRC_FOLDER)/string_util.h
	$(CC) $(CFLAGS) -c $(SRC_FOLDER)/header.c -o $(TARGET_FOLDER)/header.o

heap.o: $(SRC_FOLDER)/heap.c $(SRC_FOLDER)/heap.h $(SRC_FOLDER)/header.h
	$(CC) $(CFLAGS) -c $(SRC_FOLDER)/heap.c -o $(TARGET_FOLDER)/heap.o

heapIterator.o: $(SRC_FOLDER)/heapIterator.c $(SRC_FOLDER)/heapIterator.h $(SRC_FOLDER)/heap.h $(SRC_FOLDER)/header.h
	$(CC) $(CFLAGS) -c $(SRC_FOLDER)/heapIterator.c -o $(TARGET_FOLDER)/heapIterator.o

stack.o: $(SRC_FOLDER)/stack.c $(SRC_FOLDER)/stack.h
	$(CC) $(CFLAGS) -c $(SRC_FOLDER)/stack.c -o $(TARGET_FOLDER)/stack.o

string_util.o: $(SRC_FOLDER)/string_util.c $(SRC_FOLDER)/string_util.h 
	$(CC) $(CFLAGS) -c $(SRC_FOLDER)/string_util.c -o $(TARGET_FOLDER)/string_util.o


# TESTS
test_all: test_header test_heap test_heapIterator test_stack

test_header: $(SRC_FOLDER)/header.c $(SRC_FOLDER)/header.h $(TEST_FOLDER)/header_tests.c $(SRC_FOLDER)/string_util.c $(SRC_FOLDER)/string_util.h $(SRC_FOLDER)/heap.c $(SRC_FOLDER)/heap.h
	$(CC) $(CFLAGS) $(TEST_FOLDER)/header_tests.c $(SRC_FOLDER)/header.c $(SRC_FOLDER)/string_util.c $(SRC_FOLDER)/heap.c -o $(TARGET_FOLDER)/header_unittests -lcunit
	./$(TARGET_FOLDER)/header_unittests

test_heap: $(SRC_FOLDER)/heap.c $(SRC_FOLDER)/heap.h $(TEST_FOLDER)/heap_tests.c $(SRC_FOLDER)/header.h $(SRC_FOLDER)/header.c $(SRC_FOLDER)/string_util.c $(SRC_FOLDER)/string_util.h $(SRC_FOLDER)/debug.c $(SRC_FOLDER)/debug.h
	$(CC) $(CFLAGS) $(TEST_FOLDER)/heap_tests.c $(SRC_FOLDER)/heap.c $(SRC_FOLDER)/header.c $(SRC_FOLDER)/string_util.c $(SRC_FOLDER)/debug.c -o $(TARGET_FOLDER)/heap_unittests -lcunit
	./$(TARGET_FOLDER)/heap_unittests

test_heapIterator: $(SRC_FOLDER)/heapIterator.c $(SRC_FOLDER)/heapIterator.h $(TEST_FOLDER)/heapIterator_tests.c $(SRC_FOLDER)/header.c $(SRC_FOLDER)/header.h $(SRC_FOLDER)/string_util.c $(SRC_FOLDER)/string_util.h $(SRC_FOLDER)/heap.c $(SRC_FOLDER)/heap.h
	$(CC) $(CFLAGS) $(SRC_FOLDER)/heapIterator.c $(TEST_FOLDER)/heapIterator_tests.c $(SRC_FOLDER)/header.c $(SRC_FOLDER)/string_util.c $(SRC_FOLDER)/heap.c -o $(TARGET_FOLDER)/heapIterator_unittests -lcunit
	./$(TARGET_FOLDER)/heapIterator_unittests

test_stack: $(SRC_FOLDER)/stack.c $(SRC_FOLDER)/stack.h $(TEST_FOLDER)/stack_tests.c
	$(CC) $(CFLAGS) $(SRC_FOLDER)/stack.c $(TEST_FOLDER)/stack_tests.c -o $(TARGET_FOLDER)/stack_unittests -lcunit
	./$(TARGET_FOLDER)/stack_unittests
