# Subdirectories
CLIENT_DIR = client
SERVER_DIR = server

# Build and bin directories
CLIENT_BUILD_DIR = build/client
SERVER_BUILD_DIR = build/server
CLIENT_BIN_DIR = bin/client
SERVER_BIN_DIR = bin/server

# Targets
.PHONY: all client server clean
all: client server

client:
	$(MAKE) -C $(CLIENT_DIR) all

server:
	$(MAKE) -C $(SERVER_DIR) all

# Clean target to remove build and bin files
clean:
	$(MAKE) -C $(CLIENT_DIR) clean
	$(MAKE) -C $(SERVER_DIR) clean
	rm -rf $(CLIENT_BUILD_DIR) $(SERVER_BUILD_DIR) $(CLIENT_BIN_DIR) $(SERVER_BIN_DIR)
