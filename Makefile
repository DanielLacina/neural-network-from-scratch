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

# Source files for the main program
MAIN_SRC = $(SRC_DIR)/main.c
MAIN_OBJ = $(BUILD_DIR)/main.o

# Source files for the test program
TEST_SRC = $(TEST_DIR)/test_multidim_array.c
TEST_OBJ = $(BUILD_DIR)/test_multidim_array.o

# Source files for shared code (e.g., array.c, multidim_array.c)
SHARED_SRC = $(SRC_DIR)/array.c $(SRC_DIR)/multidim_array.c
SHARED_OBJ = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SHARED_SRC))

# Main program executable
MAIN_EXEC = $(BUILD_DIR)/myprogram

# Test program executable
TEST_EXEC = $(BUILD_DIR)/test_multidim_array

# Main target (build the main program)
all: $(MAIN_EXEC)

# Rule to build the main program
$(MAIN_EXEC): $(MAIN_OBJ) $(SHARED_OBJ) | $(BUILD_DIR)
	$(CC) $(MAIN_OBJ) $(SHARED_OBJ) -o $@

# Rule to build the test program
$(TEST_EXEC): $(TEST_OBJ) $(SHARED_OBJ) | $(BUILD_DIR)
	$(CC) $(TEST_OBJ) $(SHARED_OBJ) -o $@

# Rule to compile main.c
$(BUILD_DIR)/main.o: $(MAIN_SRC) | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $(MAIN_SRC) -o $@

# Rule to compile test_multidim_array.c
$(BUILD_DIR)/test_multidim_array.o: $(TEST_SRC) | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $(TEST_SRC) -o $@

# Rule to compile shared source files (e.g., array.c, multidim_array.c)
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Target to run tests
test: $(TEST_EXEC)
	@echo "Running tests..."
	@$(TEST_EXEC)

# Clean build files
clean:
	rm -rf $(BUILD_DIR)

.PHONY: all test clean