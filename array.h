#ifndef ARRAY_H
#define ARRAY_H

#include <stdlib.h>

typedef struct {
    int *data;
    int capacity;
    int size;
} Array;

void array_init(Array *arr);
void array_add(Array *arr, int value);
void array_add_arr(Array *arr, int arr_data[], int size);
void array_print(Array *arr);
Array* multiply_arrays(Array *arr1, Array *arr2);
Array* multiply_array_by_scalar(Array *arr, int value);
Array* add_arrays(Array *arr1, Array *arr2);
int sum_array(Array *arr);


#endif