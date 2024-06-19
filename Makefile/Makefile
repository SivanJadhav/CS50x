# Makefile to compile any .c file using clang and link with the cs50 library

# Compiler
CC = clang

# Flags
CFLAGS = -lcs50

# Default target
all: $(patsubst %.c,%,$(wildcard *.c))

# Rule to build each .c file into an executable
%: %.c
	$(CC) -o $@ $< $(CFLAGS)

# Phony targets
.PHONY: all clean

# Clean target to remove all executables
clean:
	rm -f $(patsubst %.c,%,$(wildcard *.c))