#ifndef ARRAY_H
#define ARRAY_H

#include <stdlib.h>

typedef struct {
    float *data;
    int capacity;
    int size;
} Array;

void array_init(Array *arr);
Array *array();
void array_add(Array *arr, float value);
void array_add_arr(Array *arr, float arr_data[], int size);
void array_print(Array *arr);
Array* multiply_arrays(Array *arr1, Array *arr2);
Array* multiply_array_by_scalar(Array *arr, float value);
Array* add_arrays(Array *arr1, Array *arr2);
float sum_array(Array *arr);


#endif