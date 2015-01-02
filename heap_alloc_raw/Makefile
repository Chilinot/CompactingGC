CC=gcc
FLAGS= -Wall -ggdb -std=c99

all: string_util

string_util: string_util.c
	$(CC) $(FLAGS) -o string_util string_util.c

.PHONY: clean

test: test_string_util.c 
	$(CC) $(FLAGS) test_string_util.c string_util.c -o t -lcunit
	./t

clean:
	rm -f main

