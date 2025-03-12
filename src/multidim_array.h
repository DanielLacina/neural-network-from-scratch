#ifndef MULTIDIM_ARRAY_H
#define MULTIDIM_ARRAY_H

#include "array.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct {
    Array **data;
    int capacity; 
    int size;
} MultiDimensionalArray;

void multidim_array_init(MultiDimensionalArray *mda);

void multidim_array_print(MultiDimensionalArray *mda);

void multidim_array_add(MultiDimensionalArray *mda, Array *inner_array);

MultiDimensionalArray* transpose_multidim_array(MultiDimensionalArray *arr);
MultiDimensionalArray* multiply_arrays_as_matrix(MultiDimensionalArray *arr1, MultiDimensionalArray * arr2);

#endif