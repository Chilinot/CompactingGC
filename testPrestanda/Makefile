CC = gcc
FLAGS = -Wall -ggdb -std=c99



run: prestanda.c
	$(CC) $(FLAGS) -DNO_GC_MAIN -o prestanda prestanda.c linkedListLong.c ../src/gc.c ../src/heap.c ../src/header.c ../src/stack.c ../src/heapIterator.c ../src/string_util.c 
	./prestanda


cpkod: paronet/performance_testing.c
	$(CC) $(FLAGS) -DNO_GC_MAIN -o oliver paronet/performance_testing.c paronet/linked_int_list.c ../src/gc.c ../src/heap.c ../src/header.c ../src/stack.c ../src/heapIterator.c ../src/string_util.c 
	./oliver


valgrind: 

.PHONY: run


clean:
	rm -f *o d