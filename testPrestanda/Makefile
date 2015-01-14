CC = gcc
FLAGS = -Wall -ggdb -std=c99



run: prestanda.c
	$(CC) $(FLAGS) -o prestanda prestanda.c linkedListLong.c ../src/gc.c ../src/heap.c ../src/header.c ../src/stack.c ../src/heapIterator.c ../src/string_util.c 
	./prestanda
valgrind: 

.PHONY: run


clean:
	rm -f *o d