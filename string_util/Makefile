CC=gcc
FLAGS= -Wall -ggdb -std=c99 -pedantic

all: string_util

rebuild: clean all

string_util: string_util.c
	$(CC) $(FLAGS) -o string_util string_util.c

.PHONY: clean

test: string_util_test.c 
	$(CC) $(FLAGS) string_util_test.c string_util.c -o t -lcunit
	./t

clean:
	rm -f main

run: 
	./string_util
