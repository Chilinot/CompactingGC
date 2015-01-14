CC = gcc
FLAGS = -Wall -ggdb -std=c99



run: prestanda.c
	$(CC) $(FLAGS) -o prestanda prestanda.c linkedListLong.c ../gc.c ../heap.c ../header.c ../stack.c ../heapIterator.c ../string_util/string_util.c 
	./prestanda
valgrind: 

.PHONY: run


clean:
	rm -f *o d