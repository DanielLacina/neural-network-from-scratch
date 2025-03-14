#ifndef HASHMAP_H
#define HASHMAP_H

#include <stdio.h>
#include <stdlib.h>
#include "array.h"

#define DEFINE_NODE(KEY_TYPE, VALUE_TYPE)                                      \
    typedef struct Node_##KEY_TYPE_##VALUE_TYPE {                            \
        KEY_TYPE key;                                                          \
        VALUE_TYPE value;                                                      \
        struct Node_##KEY_TYPE_##VALUE_TYPE *next;                           \
    } Node_##KEY_TYPE_##VALUE_TYPE;                                          \
                                                                               \
    Node_##KEY_TYPE_##VALUE_TYPE* node_##KEY_TYPE_##VALUE_TYPE(KEY_TYPE key, VALUE_TYPE value) { \
        Node_##KEY_TYPE_##VALUE_TYPE *node = (Node_##KEY_TYPE_##VALUE_TYPE*)malloc(sizeof(Node_##KEY_TYPE_##VALUE_TYPE)); \
        if (!node) {                                                           \
            fprintf(stderr, "Memory allocation failed\n");                      \
            exit(EXIT_FAILURE);                                                \
        }                                                                      \
        node->key = key;                                                       \
        node->value = value;                                                   \
        node->next = NULL;                                                     \
        return node;                                                           \
    }


#define DEFINE_HASHMAP(KEY_TYPE, VALUE_TYPE)                                   \
    typedef struct {                                                           \
        Array_Node_##KEY_TYPE_##VALUE_TYPE *buckets;                         \
        size_t size;                                                           \
        size_t capacity;                                                       \
        double load_factor;                                                     \
        ssize_t threshold;                                                     \
    } HashMap_##KEY_TYPE_##VALUE_TYPE;                                       \
                                                                               \
    HashMap_##KEY_TYPE_##VALUE_TYPE* hashmap_##KEY_TYPE_##VALUE_TYPE(size_t capacity) { \
        HashMap_##KEY_TYPE_##VALUE_TYPE *map = (HashMap_##KEY_TYPE_##VALUE_TYPE*)malloc(sizeof(HashMap_##KEY_TYPE_##VALUE_TYPE)); \
        if (!map) {                                                            \
            fprintf(stderr, "Memory allocation failed\n");                      \
            exit(EXIT_FAILURE);                                                \
        }                                                                      \
        map->buckets = array_Node_##KEY_TYPE_##VALUE_TYPE();                  \
        map->size = 0;                                                         \
        map->capacity = capacity;                                              \
        map->buckets->data = calloc(map -> capacity, sizeof(Node_##KEY_TYPE_##VALUE_TYPE*)); \
        map -> load_factor = 0.75;                                               \
        map -> threshold = (size_t)(map -> load_factor * map -> capacity);      \
        return map;                                                            \
     }\
     void hashmap_##Key_Type##Value_Type_resize(HashMap_##Key_Type_##Value_Type *map) { \
        size_t new_capacity = map->capacity == 0 ? 1 : map->capacity * 2;       \
        Array_Node_##Key_Type_##Value_Type *new_buckets = calloc(new_capacity, sizeof(Node_##Key_Type_##Value_Type*)); \
     }\
     void hashmap_##Key_Type_##Value_Type_insert(Node_##Key_Type_##Value_Type *map) { \
     }\
 
DEFINE_NODE(char, int);
DEFINE_ARRAY(Node_char_int);

DEFINE_HASHMAP(char, int);

#endif 