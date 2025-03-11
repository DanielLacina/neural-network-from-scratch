#include "multidim_array.h"

void multidim_array_init(MultiDimensionalArray *mda) {
    mda->data = NULL;
    mda->capacity = 0;
    mda->size = 0;
}

void multidim_array_print(MultiDimensionalArray *mda) {
    printf("[\n");
    for (int i = 0; i < mda->size; i++) {
        array_print(mda->data[i]);
    }
    printf("]\n");
} 

void multidim_array_add(MultiDimensionalArray *mda, Array *inner_array) {
    if (mda->size == mda->capacity) {
        mda->capacity = mda->capacity == 0 ? 1 : mda->capacity * 2;
        mda->data = realloc(mda->data, mda->capacity * sizeof(Array *));
    }
    mda->data[mda->size++] = inner_array;
}

MultiDimensionalArray* transpose_multidim_array(MultiDimensionalArray *arr) {
    MultiDimensionalArray* multi_result = malloc(sizeof(MultiDimensionalArray)); 
    multidim_array_init(multi_result);    
    for (int i = 0; i < arr -> data[0] -> size; i++) {
        Array* result = malloc(sizeof(Array)); 
        array_init(result);
        for (int j = 0; j < arr -> size; j++) {
             array_add(result, arr -> data[j] -> data[i]); 
        } 
        multidim_array_add(multi_result, result); 
    }
    return multi_result;
} 


// MultiDimensionalArray* multiply_arrays_as_matrix(MultiDimensionalArray *arr1, MultiDimensionalArray * arr2) {
//     MultiDimensionalArray* multidim_arr_result = malloc(sizeof(MultiDimensionalArray));
//     MultiDimensionalArray *arr2 = transpose_multidim_array(arr2); 
// }