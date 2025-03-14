#ifndef ARRAY_H
#define ARRAY_H

#include <stdio.h>
#include <stdlib.h>

// Macro to declare an array for a specific type
#define DECLARE_ARRAY(TYPE)                                               \
    typedef struct {                                                     \
        TYPE *data;                                                      \
        size_t size;                                                     \
        size_t capacity;                                                 \
    } Array_##TYPE;                                                      \
                                                                         \
    void array_init_##TYPE(Array_##TYPE *arr);                           \
    Array_##TYPE *array_##TYPE();                                        \
    Array_##TYPE* cloned_array_##TYPE(Array_##TYPE *arr);                \
    void array_add_##TYPE(Array_##TYPE *arr, TYPE value);                \
    void array_add_arr_##TYPE(Array_##TYPE *arr, TYPE arr_data[], int size); \
    void array_print_##TYPE(Array_##TYPE *arr);                          \
    Array_##TYPE* multiply_arrays_##TYPE(Array_##TYPE *arr1, Array_##TYPE *arr2); \
    Array_##TYPE* multiply_array_by_scalar_##TYPE(Array_##TYPE *arr, TYPE value); \
    Array_##TYPE* add_arrays_##TYPE(Array_##TYPE *arr1, Array_##TYPE *arr2); \
    TYPE sum_array_##TYPE(Array_##TYPE *arr);                            \
    void array_free_##TYPE(Array_##TYPE *arr);

// Declare arrays for float, int, and char
DECLARE_ARRAY(float)
DECLARE_ARRAY(int)
DECLARE_ARRAY(char)

#endif // ARRAY_H