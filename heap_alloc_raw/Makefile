CC=gcc
FLAGS= -Wall -ggdb -std=c99

all: heap_alloc

heap_alloc: heap_alloc.c
	$(CC) $(FLAGS) -o heap_alloc heap_alloc.c

.PHONY: clean

clean:
	rm -f main
