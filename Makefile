all: 
	echo "Makefile unfinished!"

# Tex settings
C_COMPILER   = gcc
C_OPTIONS    = -ggdb -Wall -std=c99

# Clean settings
GEN_EXTENSIONS = *.o *.out

clean:
	rm -f $(GEN_EXTENSIONS) unittests *.orig

%:	%.c
	$(C_COMPILER) $(C_OPTIONS) $< -o $@

heap.o: heap.c heap.h heap_rep.h
	$(C_COMPILER) $ (C_OPTIONS) heap.c -o heap.o

#test: unittests.c istring.c istring.h
#	$(C_COMPILER) $(C_OPTIONS) unittests.c istring.c -o unittests -lcunit
#	./unittests

