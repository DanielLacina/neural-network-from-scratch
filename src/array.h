#ifndef ARRAY_H
#define ARRAY_H

#include <stdio.h>
#include <stdlib.h>

// Define the Array structure
#define DEFINE_ARRAY_STRUCT(TYPE) \
    typedef struct { \
        TYPE *data; \
        size_t size; \
        size_t capacity; \
    } Array_##TYPE;

// Declare the Array structure for float and int
DEFINE_ARRAY_STRUCT(float)
DEFINE_ARRAY_STRUCT(int)

// Declare functions for float arrays
void array_init_float(Array_float *arr);
Array_float *array_float();
Array_float* cloned_array_float(Array_float *arr);
void array_add_float(Array_float *arr, float value);
void array_add_arr_float(Array_float *arr, float arr_data[], int size);
void array_print_float(Array_float *arr);
Array_float* multiply_arrays_float(Array_float *arr1, Array_float *arr2);
Array_float* multiply_array_by_scalar_float(Array_float *arr, float value);
Array_float* add_arrays_float(Array_float *arr1, Array_float *arr2);
float sum_array_float(Array_float *arr);
void array_free_float(Array_float *arr);

// Declare functions for int arrays
void array_init_int(Array_int *arr);
Array_int *array_int();
Array_int* cloned_array_int(Array_int *arr);
void array_add_int(Array_int *arr, int value);
void array_add_arr_int(Array_int *arr, int arr_data[], int size);
void array_print_int(Array_int *arr);
Array_int* multiply_arrays_int(Array_int *arr1, Array_int *arr2);
Array_int* multiply_array_by_scalar_int(Array_int *arr, int value);
Array_int* add_arrays_int(Array_int *arr1, Array_int *arr2);
int sum_array_int(Array_int *arr);
void array_free_int(Array_int *arr);

#endif // ARRAY_H