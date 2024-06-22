# Compiler
CC = gcc

# Directories
BUILD_DIR = ../build/client
BIN_DIR = ../bin/client

# Source files
SRCS = client.c messageclient.c
OBJS = $(SRCS:.c=.o)
OBJS := $(addprefix $(BUILD_DIR)/, $(OBJS))

# Include directories
INCLUDES = -I.

# Compiler flags
CFLAGS = -Wall -Wextra -g -I. -I../include

# Create build and bin directories if they don't exist
$(shell mkdir -p $(BUILD_DIR) $(BIN_DIR))

# Target to build the executable
.PHONY: all
all: $(BIN_DIR)/client

$(BIN_DIR)/client: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

# Compile .c files to .o files
$(BUILD_DIR)/%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Clean target to remove build and bin files
.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)/*.o $(BIN_DIR)/client
