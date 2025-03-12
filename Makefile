# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -g -I src

# Directories
SRC_DIR = src
TEST_DIR = tests
BUILD_DIR = build

# Ensure the build directory exists
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Source files
SRC_FILES = $(SRC_DIR)/array.c $(SRC_DIR)/multidim_array.c
OBJ_FILES = $(BUILD_DIR)/array.o $(BUILD_DIR)/multidim_array.o

# Test files
TEST_SRC = $(TEST_DIR)/test_multidim_array.c
TEST_OBJ = $(BUILD_DIR)/test_multidim_array.o
TEST_EXEC = $(BUILD_DIR)/test_multidim

# Main target
all: $(BUILD_DIR)/myprogram

$(BUILD_DIR)/myprogram: $(OBJ_FILES) $(BUILD_DIR)/main.o | $(BUILD_DIR)
	$(CC) $(OBJ_FILES) $(BUILD_DIR)/main.o -o $@

$(BUILD_DIR)/main.o: $(SRC_DIR)/main.c $(SRC_DIR)/array.h $(SRC_DIR)/multidim_array.h | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/main.c -o $@

$(BUILD_DIR)/array.o: $(SRC_DIR)/array.c $(SRC_DIR)/array.h | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/array.c -o $@

$(BUILD_DIR)/multidim_array.o: $(SRC_DIR)/multidim_array.c $(SRC_DIR)/multidim_array.h $(SRC_DIR)/array.h | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/multidim_array.c -o $@

# Compile and run tests
test: $(TEST_EXEC)
	@echo "Running tests..."
	@$(TEST_EXEC)

$(TEST_EXEC): $(OBJ_FILES) $(TEST_OBJ) | $(BUILD_DIR)
	$(CC) $(OBJ_FILES) $(TEST_OBJ) -o $(TEST_EXEC)

$(BUILD_DIR)/test_multidim_array.o: $(TEST_SRC) $(SRC_DIR)/array.h $(SRC_DIR)/multidim_array.h | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $(TEST_SRC) -o $@

# Clean build files
clean:
	rm -rf $(BUILD_DIR)

.PHONY: all test clean

				