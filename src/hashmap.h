#ifndef HASHMAP_H
#define HASHMAP_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "array.h"

typedef const char* string_t;
// Declare the Node type
#define DECLARE_NODE(Key_Type, Value_Type) \
    typedef struct Node_##Key_Type##_##Value_Type Node_##Key_Type##_##Value_Type; \
    Node_##Key_Type##_##Value_Type* node_##Key_Type##_##Value_Type(Key_Type key, Value_Type value);

// Declare the Array_Node type and function prototype
#define DECLARE_NODE_ARRAY(Key_Type, Value_Type) \
    typedef struct { \
        Node_##Key_Type##_##Value_Type **data; \
        size_t size; \
    } Array_Node_##Key_Type##_##Value_Type; \
    Array_Node_##Key_Type##_##Value_Type* array_Node_##Key_Type##_##Value_Type();

// Declare the HashMap type and function prototypes
#define DECLARE_HASHMAP(Key_Type, Value_Type) \
    typedef struct { \
        Array_Node_##Key_Type##_##Value_Type *buckets; \
        size_t size; \
        size_t capacity; \
        double load_factor; \
        size_t threshold; \
    } HashMap_##Key_Type##_##Value_Type; \
    HashMap_##Key_Type##_##Value_Type* hashmap_##Key_Type##_##Value_Type(size_t capacity); \
    void hashmap_##Key_Type##_##Value_Type##_resize(HashMap_##Key_Type##_##Value_Type *map);

// Declare the hash function and compare function prototypes
#define DECLARE_HASH_FUNCTION(Key_Type) \
    size_t hash_function_##Key_Type(Key_Type key, size_t capacity);

#define DECLARE_COMPARE_KEYS(Key_Type) \
    bool compare_key_##Key_Type(Key_Type key1, Key_Type key2);

// Declare the CRUD operations
#define DECLARE_HASHMAP_CRUD_OPERATIONS(Key_Type, Value_Type) \
    void hashmap_##Key_Type##_##Value_Type##_insert(HashMap_##Key_Type##_##Value_Type *map, Key_Type key, Value_Type value); \
    void hashmap_##Key_Type##_##Value_Type##_remove(HashMap_##Key_Type##_##Value_Type *map, Key_Type key); \
    Value_Type hashmap_##Key_Type##_##Value_Type##_get(HashMap_##Key_Type##_##Value_Type *map, Key_Type key, Value_Type default_value);

// Declare types and functions
DECLARE_NODE(int, int)
DECLARE_NODE_ARRAY(int, int)
DECLARE_HASHMAP(int, int)
DECLARE_HASH_FUNCTION(int)
DECLARE_COMPARE_KEYS(int)
DECLARE_HASHMAP_CRUD_OPERATIONS(int, int)
DECLARE_NODE(string_t, Array_float)
DECLARE_NODE_ARRAY(string_t, Array_float)
DECLARE_HASHMAP(string_t, Array_float)
DECLARE_HASHMAP_CRUD_OPERATIONS(string_t, Array_float)

// Declare non-macro functions
size_t hash_function_string_t(const char *key, size_t capacity);
bool compare_key_string_t(const char *key1, const char *key2);

#endif // HASHMAP_H