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

# Source files for the test programs
TEST_MULTIDIM_SRC = $(TEST_DIR)/test_multidim_array.c
TEST_MULTIDIM_OBJ = $(BUILD_DIR)/test_multidim_array.o

TEST_HASHMAP_SRC = $(TEST_DIR)/test_hashmap.c
TEST_HASHMAP_OBJ = $(BUILD_DIR)/test_hashmap.o

# Source files for shared code (e.g., array.c, multidim_array.c, hashmap.c, csv_reader.c)
SHARED_SRC = $(SRC_DIR)/array.c $(SRC_DIR)/multidim_array.c $(SRC_DIR)/hashmap.c $(SRC_DIR)/csv_reader.c
SHARED_OBJ = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SHARED_SRC))

# Main program executable
MAIN_EXEC = $(BUILD_DIR)/myprogram

# Test program executables
TEST_MULTIDIM_EXEC = $(BUILD_DIR)/test_multidim_array
TEST_HASHMAP_EXEC = $(BUILD_DIR)/test_hashmap

# Main target (build the main program)
all: $(MAIN_EXEC)

# Rule to build the main program
$(MAIN_EXEC): $(MAIN_OBJ) $(SHARED_OBJ) | $(BUILD_DIR)
	$(CC) $(MAIN_OBJ) $(SHARED_OBJ) -o $@

# Rule to build the multidim array test program
$(TEST_MULTIDIM_EXEC): $(TEST_MULTIDIM_OBJ) $(SHARED_OBJ) | $(BUILD_DIR)
	$(CC) $(TEST_MULTIDIM_OBJ) $(SHARED_OBJ) -o $@

# Rule to build the hashmap test program
$(TEST_HASHMAP_EXEC): $(TEST_HASHMAP_OBJ) $(SHARED_OBJ) | $(BUILD_DIR)
	$(CC) $(TEST_HASHMAP_OBJ) $(SHARED_OBJ) -o $@

# Rule to compile main.c
$(BUILD_DIR)/main.o: $(MAIN_SRC) | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $(MAIN_SRC) -o $@

# Rule to compile test_multidim_array.c
$(BUILD_DIR)/test_multidim_array.o: $(TEST_MULTIDIM_SRC) | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $(TEST_MULTIDIM_SRC) -o $@

# Rule to compile test_hashmap.c
$(BUILD_DIR)/test_hashmap.o: $(TEST_HASHMAP_SRC) | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $(TEST_HASHMAP_SRC) -o $@

# Rule to compile shared source files (e.g., array.c, multidim_array.c, hashmap.c, csv_reader.c)
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Target to run all tests
test: $(TEST_MULTIDIM_EXEC) $(TEST_HASHMAP_EXEC)
	@echo "Running multidim array tests..."
	@$(TEST_MULTIDIM_EXEC)
	@echo "Running hashmap tests..."
	@$(TEST_HASHMAP_EXEC)

# Clean build files
clean:
	rm -rf $(BUILD_DIR)

.PHONY: all test clean