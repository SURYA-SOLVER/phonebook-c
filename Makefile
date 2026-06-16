# Makefile for Phone Book Application

CC = gcc
CFLAGS = -Wall -Wextra -std=c99
TARGET = phonebook
SRCS = phonebook.c
OBJS = $(SRCS:.c=.o)

# Default target
all: $(TARGET)

# Build the executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Compile source files to object files
%.o: %.c
	$(CC) $(CFLAGS) -c $<

# Run the program
run: $(TARGET)
	./$(TARGET)

# Clean up object files and executable
clean:
	rm -f $(OBJS) $(TARGET) contacts.bin temp.bin

# Clean everything including generated files
distclean: clean

# Rebuild from scratch
rebuild: clean all

.PHONY: all run clean distclean rebuild
