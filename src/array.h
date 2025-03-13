#ifndef ARRAY_H
#define ARRAY_H

#include <stdio.h>
#include <stdlib.h>

// Macro to define an array for a specific type
#define DEFINE_ARRAY(TYPE)                                               \
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
    void array_free_##TYPE(Array_##TYPE *arr);                           \
                                                                         \
    void array_init_##TYPE(Array_##TYPE *arr) {                          \
        arr->data = NULL;                                                \
        arr->size = 0;                                                   \
        arr->capacity = 0;                                               \
    }                                                                    \
                                                                         \
    Array_##TYPE *array_##TYPE() {                                       \
        Array_##TYPE *arr = malloc(sizeof(Array_##TYPE));                \
        array_init_##TYPE(arr);                                          \
        return arr;                                                      \
    }                                                                    \
                                                                         \
    Array_##TYPE* cloned_array_##TYPE(Array_##TYPE *arr) {               \
        Array_##TYPE *cloned_arr = array_##TYPE();                       \
        for (size_t i = 0; i < arr->size; i++) {                         \
            array_add_##TYPE(cloned_arr, arr->data[i]);                  \
        }                                                                \
        return cloned_arr;                                               \
    }                                                                    \
                                                                         \
    void array_add_##TYPE(Array_##TYPE *arr, TYPE value) {               \
        if (arr->size == arr->capacity) {                                \
            arr->capacity = arr->capacity == 0 ? 1 : arr->capacity * 2;  \
            arr->data = realloc(arr->data, arr->capacity * sizeof(TYPE)); \
        }                                                                \
        arr->data[arr->size++] = value;                                  \
    }                                                                    \
                                                                         \
    void array_add_arr_##TYPE(Array_##TYPE *arr, TYPE arr_data[], int size) { \
        for (int i = 0; i < size; i++) {                                 \
            array_add_##TYPE(arr, arr_data[i]);                          \
        }                                                                \
    }                                                                    \
                                                                         \
    void array_print_##TYPE(Array_##TYPE *arr) {                         \
        printf("[");                                                     \
        for (size_t i = 0; i < arr->size; i++) {                         \
            printf("%f ", arr->data[i]);                                 \
        }                                                                \
        printf("],\n");                                                  \
    }                                                                    \
                                                                         \
    Array_##TYPE* multiply_arrays_##TYPE(Array_##TYPE *arr1, Array_##TYPE *arr2) { \
        if (arr1->size != arr2->size) {                                  \
            return NULL;                                                 \
        }                                                                \
        Array_##TYPE *result_array = array_##TYPE();                     \
        for (size_t i = 0; i < arr1->size; i++) {                        \
            array_add_##TYPE(result_array, arr1->data[i] * arr2->data[i]); \
        }                                                                \
        return result_array;                                             \
    }                                                                    \
                                                                         \
    Array_##TYPE* multiply_array_by_scalar_##TYPE(Array_##TYPE *arr, TYPE value) { \
        Array_##TYPE *result_array = array_##TYPE();                     \
        for (size_t i = 0; i < arr->size; i++) {                         \
            array_add_##TYPE(result_array, arr->data[i] * value);        \
        }                                                                \
        return result_array;                                             \
    }                                                                    \
                                                                         \
    Array_##TYPE* add_arrays_##TYPE(Array_##TYPE *arr1, Array_##TYPE *arr2) { \
        if (arr1->size != arr2->size) {                                  \
            return NULL;                                                 \
        }                                                                \
        Array_##TYPE *result_array = array_##TYPE();                     \
        for (size_t i = 0; i < arr1->size; i++) {                        \
            array_add_##TYPE(result_array, arr1->data[i] + arr2->data[i]); \
        }                                                                \
        return result_array;                                             \
    }                                                                    \
                                                                         \
    TYPE sum_array_##TYPE(Array_##TYPE *arr) {                           \
        TYPE sum = 0;                                                    \
        for (size_t i = 0; i < arr->size; i++) {                         \
            sum += arr->data[i];                                         \
        }                                                                \
        return sum;                                                      \
    }                                                                    \
                                                                         \
    void array_free_##TYPE(Array_##TYPE *arr) {                          \
        free(arr->data);                                                 \
        free(arr);                                                       \
    }

// Define the Array for float
DEFINE_ARRAY(float)

#endif // ARRAY_H