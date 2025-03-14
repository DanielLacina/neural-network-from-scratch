#ifndef HASHMAP_H
#define HASHMAP_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEFINE_NODE(Key_Type, Value_Type) \
    typedef struct Node_##Key_Type##_##Value_Type { \
        Key_Type key; \
        Value_Type value; \
        struct Node_##Key_Type##_##Value_Type *next; \
    } Node_##Key_Type##_##Value_Type; \
    \
    Node_##Key_Type##_##Value_Type* node_##Key_Type##_##Value_Type(Key_Type key, Value_Type value) { \
        Node_##Key_Type##_##Value_Type *node = (Node_##Key_Type##_##Value_Type*)malloc(sizeof(Node_##Key_Type##_##Value_Type)); \
        if (!node) { \
            fprintf(stderr, "Memory allocation failed\n"); \
            exit(EXIT_FAILURE); \
        } \
        node->key = key; \
        node->value = value; \
        node->next = NULL; \
        return node; \
    }

#define DEFINE_ARRAY(Key_Type, Value_Type) \
    typedef struct { \
        Node_##Key_Type##_##Value_Type **data; \
        size_t size; \
    } Array_Node_##Key_Type##_##Value_Type; \
    \
    Array_Node_##Key_Type##_##Value_Type* array_Node_##Key_Type##_##Value_Type() { \
        Array_Node_##Key_Type##_##Value_Type *array = (Array_Node_##Key_Type##_##Value_Type*)malloc(sizeof(Array_Node_##Key_Type##_##Value_Type)); \
        if (!array) { \
            fprintf(stderr, "Memory allocation failed\n"); \
            exit(EXIT_FAILURE); \
        } \
        array->data = NULL; \
        array->size = 0; \
        return array; \
    }

#define DEFINE_HASHMAP(Key_Type, Value_Type) \
    typedef struct { \
        Array_Node_##Key_Type##_##Value_Type *buckets; \
        size_t size; \
        size_t capacity; \
        double load_factor; \
        size_t threshold; \
    } HashMap_##Key_Type##_##Value_Type; \
    \
    HashMap_##Key_Type##_##Value_Type* hashmap_##Key_Type##_##Value_Type(size_t capacity) { \
        HashMap_##Key_Type##_##Value_Type *map = (HashMap_##Key_Type##_##Value_Type*)malloc(sizeof(HashMap_##Key_Type##_##Value_Type)); \
        if (!map) { \
            fprintf(stderr, "Memory allocation failed\n"); \
            exit(EXIT_FAILURE); \
        } \
        map->buckets = array_Node_##Key_Type##_##Value_Type(); \
        map->size = 0; \
        map->capacity = capacity; \
        map->buckets->data = (Node_##Key_Type##_##Value_Type**)calloc(map->capacity, sizeof(Node_##Key_Type##_##Value_Type*)); \
        map->load_factor = 0.75; \
        map->threshold = (size_t)(map->load_factor * map->capacity); \
        return map; \
    } \
    \
    void hashmap_##Key_Type##_##Value_Type##_resize(HashMap_##Key_Type##_##Value_Type *map) { \
        size_t new_capacity = map->capacity == 0 ? 1 : map->capacity * 2; \
        Node_##Key_Type##_##Value_Type **new_buckets = (Node_##Key_Type##_##Value_Type**)calloc(new_capacity, sizeof(Node_##Key_Type##_##Value_Type*)); \
        for (size_t i = 0; i < map->capacity; i++) { \
            Node_##Key_Type##_##Value_Type *current = map->buckets->data[i]; \
            while (current != NULL) { \
                Node_##Key_Type##_##Value_Type *next = current->next; \
                size_t new_hash = hash_function_##Key_Type(current->key, new_capacity); \
                current->next = new_buckets[new_hash]; \
                new_buckets[new_hash] = current; \
                current = next; \
            } \
        } \
        free(map->buckets->data); \
        map->buckets->data = new_buckets; \
        map->capacity = new_capacity; \
        map->threshold = (size_t)(map->load_factor * map->capacity); \
    }

#define DEFINE_HASH_FUNCTION(Key_Type) \
    size_t hash_function_##Key_Type(Key_Type key, size_t capacity) { \
        return (size_t)(key % capacity); \
    }

#define DEFINE_HASHMAP_CRUD_OPERATIONS(Key_Type, Value_Type) \
    void hashmap_##Key_Type##_##Value_Type##_insert(HashMap_##Key_Type##_##Value_Type *map, Key_Type key, Value_Type value) { \
        Node_##Key_Type##_##Value_Type *node = node_##Key_Type##_##Value_Type(key, value); \
        if (!node) { \
            return; \
        } \
        if (map->size >= map->threshold) { \
            hashmap_##Key_Type##_##Value_Type##_resize(map); \
        } \
        size_t hash = hash_function_##Key_Type(key, map->capacity); \
        if (map->buckets->data[hash] == NULL) { \
            map->buckets->data[hash] = node; \
        } else { \
            Node_##Key_Type##_##Value_Type *current = map->buckets->data[hash]; \
            while (current->next != NULL) { \
                current = current->next; \
            } \
            current->next = node; \
        } \
        map->size++; \
    } \
    \
    void hashmap_##Key_Type##_##Value_Type##_remove(HashMap_##Key_Type##_##Value_Type *map, Key_Type key) { \
        size_t hash = hash_function_##Key_Type(key, map->capacity); \
        Node_##Key_Type##_##Value_Type *current = map->buckets->data[hash]; \
        Node_##Key_Type##_##Value_Type *prev = NULL; \
        while (current != NULL && current->key != key) { \
            prev = current; \
            current = current->next; \
        } \
        if (current != NULL) { \
            if (prev == NULL) { \
                map->buckets->data[hash] = current->next; \
            } else { \
                prev->next = current->next; \
            } \
            free(current); \
            map->size--; \
        } \
    } \
    \
    Value_Type hashmap_##Key_Type##_##Value_Type##_get(HashMap_##Key_Type##_##Value_Type *map, Key_Type key, Value_Type default_value) { \
        size_t hash = hash_function_##Key_Type(key, map->capacity); \
        Node_##Key_Type##_##Value_Type *current = map->buckets->data[hash]; \
        while (current != NULL && current->key != key) { \
            current = current->next; \
        } \
        if (current != NULL) { \
            return current->value; \
        } else { \
            return default_value; \
        } \
    }

size_t hash_function_string(const char *key, size_t capacity) {
    unsigned long hash = 5381;
    int c;
    while ((c = *key++)) {
        hash = ((hash << 5) + hash) + c; 
    }
    return hash % capacity;
}

DEFINE_NODE(int, int)
DEFINE_ARRAY(int, int)
DEFINE_HASH_FUNCTION(int)
DEFINE_HASHMAP(int, int)
DEFINE_HASHMAP_CRUD_OPERATIONS(int, int)
     
#endif 