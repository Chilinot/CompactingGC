all: test_header

# Tex settings
C_COMPILER   = gcc
C_OPTIONS    = -ggdb -Wall -std=c99

# Clean settings
GEN_EXTENSIONS = *.o *.out

clean:
	rm -f $(GEN_EXTENSIONS) unittests *.orig

%:	%.c
	$(C_COMPILER) $(C_OPTIONS) $< -o $@
	
test_header: header.c header.h header_tests.c
	$(C_COMPILER) $(C_OPTIONS) header_tests.c header.c -o header_unittests -lcunit
	./header_unittests

#test: unittests.c istring.c istring.h
#	$(C_COMPILER) $(C_OPTIONS) unittests.c istring.c -o unittests -lcunit
#	./unittests

