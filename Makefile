# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -pedantic -g -std=c99

# Program name
TARGET = demographics
# Default target
all: $(TARGET)

# Build the executable
$(TARGET): $(TARGET).c
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).c

# Clean up build artifacts
clean:
	rm -f $(TARGET)
