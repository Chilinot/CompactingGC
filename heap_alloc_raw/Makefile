CC=gcc
FLAGS= -Wall -ggdb -std=c99

all: heap_alloc

heap_alloc: heap_alloc.c
	$(CC) $(FLAGS) -o heap_alloc heap_alloc.c

.PHONY: clean

test: test_heap_alloc.c 
	$(CC) $(FLAGS) test_heap_alloc.c heap_alloc.c -o t -lcunit
	./t

clean:
	rm -f main

