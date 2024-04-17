# Makefile for Raspberry Pi LED Blink Exercise
# Compiler
CC = gcc
# Compiler flags
CFLAGS = -Wall -lwiringPi
# Source files
SRCS = ex_1.c
# Object files
OBJS = $(SRCS:.c=.o)
# Executable name
TARGET = led_blink

# Default target
all: $(TARGET)

# Rule to build the executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

# Rule to compile source files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean target
clean:
	rm -f $(OBJS) $(TARGET)

# PHONY targets
.PHONY: all clean
