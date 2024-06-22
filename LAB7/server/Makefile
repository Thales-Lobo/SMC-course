# Compiler
CC = gcc

# Directories
BUILD_DIR = ../build/server
BIN_DIR = ../bin/server
INCLUDE_DIR = ../include

# Source files
SRCS = server.c echoserver.c
OBJS = $(SRCS:.c=.o)
OBJS := $(addprefix $(BUILD_DIR)/, $(OBJS))

# Include directories
INCLUDES = -I. -I$(INCLUDE_DIR)

# Compiler flags
CFLAGS = -Wall -Wextra -g

# Create build and bin directories if they don't exist
$(shell mkdir -p $(BUILD_DIR) $(BIN_DIR))

# Target to build the executable
.PHONY: all
all: $(BIN_DIR)/server

$(BIN_DIR)/server: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

# Compile .c files to .o files
$(BUILD_DIR)/%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Clean target to remove build and bin files
.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)/*.o $(BIN_DIR)/server
