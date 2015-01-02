CC=gcc
FLAGS= -Wall -ggdb -std=c99

all: string_util

<<<<<<< HEAD
=======
rebuild: clean all

>>>>>>> b130b15ca44dc1ed935d84752d9158aa525d4a98
string_util: string_util.c
	$(CC) $(FLAGS) -o string_util string_util.c

.PHONY: clean

<<<<<<< HEAD
test: test_string_util.c 
	$(CC) $(FLAGS) test_string_util.c string_util.c -o t -lcunit
=======
test: string_util_test.c 
	$(CC) $(FLAGS) string_util_test.c string_util.c -o t -lcunit
>>>>>>> b130b15ca44dc1ed935d84752d9158aa525d4a98
	./t

clean:
	rm -f main

run: 
	./string_util
