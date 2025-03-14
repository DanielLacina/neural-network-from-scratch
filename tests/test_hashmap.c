#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "hashmap.h"

// Function prototypes for the hashmap operations
void hashmap_int_int_insert(HashMap_int_int *map, int key, int value);
void hashmap_int_int_remove(HashMap_int_int *map, int key);
int hashmap_int_int_get(HashMap_int_int *map, int key, int default_value);

// Test function for the hashmap
void test_hashmap_int_int() {
    // Create a hashmap with an initial capacity of 10
    HashMap_int_int *map = hashmap_int_int(10);

    // Test 1: Insert key-value pairs
    hashmap_int_int_insert(map, 42, 100);
    hashmap_int_int_insert(map, 13, 200);
    hashmap_int_int_insert(map, 25, 300);

    // Verify the size of the hashmap
    assert(map->size == 3);

    // Test 2: Retrieve values
    assert(hashmap_int_int_get(map, 42, -1) == 100);
    assert(hashmap_int_int_get(map, 13, -1) == 200);
    assert(hashmap_int_int_get(map, 25, -1) == 300);

    // Test 3: Retrieve a non-existent key
    assert(hashmap_int_int_get(map, 99, -1) == -1);

    // Test 4: Remove a key
    hashmap_int_int_remove(map, 13);
    assert(map->size == 2);

    // Verify that the removed key is no longer present
    assert(hashmap_int_int_get(map, 13, -1) == -1);

    // Test 5: Insert more key-value pairs to trigger resizing
    for (int i = 0; i < 20; i++) {
        hashmap_int_int_insert(map, i, i * 10);
    }

    // Verify the size after resizing
    assert(map->size == 22);

    // Test 6: Retrieve values after resizing
    assert(hashmap_int_int_get(map, 42, -1) == 100);
    assert(hashmap_int_int_get(map, 25, -1) == 300);
    assert(hashmap_int_int_get(map, 15, -1) == 150);

    // Test 7: Remove all keys
    for (int i = 0; i < 20; i++) {
        hashmap_int_int_remove(map, i);
    }
    hashmap_int_int_remove(map, 42);
    hashmap_int_int_remove(map, 25);

    // Verify that the hashmap is empty
    assert(map->size == 0);

    // Test 8: Retrieve values from an empty hashmap
    assert(hashmap_int_int_get(map, 42, -1) == -1);
    assert(hashmap_int_int_get(map, 13, -1) == -1);
    assert(hashmap_int_int_get(map, 25, -1) == -1);

    // Free the hashmap
    free(map->buckets->data);
    free(map->buckets);
    free(map);

    printf("All tests passed!\n");
}

int main() {
    test_hashmap_int_int();
    return 0;
}