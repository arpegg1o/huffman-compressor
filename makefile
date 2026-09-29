# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -g -I$(INC_DIR)

# Directories
SRC_DIR = src
INC_DIR = include
OBJ_DIR = obj
BIN_DIR = bin

# Shared files (exclude the files containing main() functions)
COMMON_SRCS = $(filter-out $(SRC_DIR)/compress.c $(SRC_DIR)/decompress.c, $(wildcard $(SRC_DIR)/*.c))
COMMON_OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(COMMON_SRCS))

# Targets
COMPRESS_BIN = $(BIN_DIR)/compress
DECOMPRESS_BIN = $(BIN_DIR)/decompress

# Default rule builds both executables
all: $(COMPRESS_BIN) $(DECOMPRESS_BIN)

# Link the compress executable
$(COMPRESS_BIN): $(OBJ_DIR)/compress.o $(COMMON_OBJS)
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) $^ -o $@

# Link the decompress executable
$(DECOMPRESS_BIN): $(OBJ_DIR)/decompress.o $(COMMON_OBJS)
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) $^ -o $@

# Generic rule to compile any .c file into a .o file
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean rule
clean:
	rm -rf $(OBJ_DIR)/*.o $(BIN_DIR)/*

.PHONY: all clean
