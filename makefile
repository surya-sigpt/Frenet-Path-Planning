# Compiler
CC = gcc

# Flags
CFLAGS = -I$(INC_DIR) -Wall -O2

# Directories
SRC_DIR = src
INC_DIR = include
BUILD_DIR = build
OUT_DIR = output

# Files
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRCS))
TARGET = $(BUILD_DIR)/a.out

# Default target
all: $(BUILD_DIR) $(OUT_DIR) $(TARGET)

# Linking
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $@ -lm

# Compilation
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Ensure build dir exists
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Ensure output dir exists
$(OUT_DIR):
	mkdir -p $(OUT_DIR)

# Run the program
run: $(TARGET)
	./$(TARGET)

# Clean all
clean:
	rm -rf $(BUILD_DIR) $(OUT_DIR)

.PHONY: all clean run
