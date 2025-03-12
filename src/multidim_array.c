#include "multidim_array.h"

void multidim_array_init(MultiDimensionalArray *mda) {
    mda->data = NULL;
    mda->capacity = 0;
    mda->size = 0;
}

void multidim_array_print(MultiDimensionalArray *mda) {
    if (mda == NULL) {return;}
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
    if (arr->size == 0 || arr -> data[0] -> size == 0) {
        return NULL;
    }
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


MultiDimensionalArray* multiply_arrays_as_matrix(MultiDimensionalArray *arr1, MultiDimensionalArray * arr2) {
    // arr2 is the matrix getting transformed by arr1 matrix
    MultiDimensionalArray* multi_result = malloc(sizeof(MultiDimensionalArray));
    multidim_array_init(multi_result);
    if (arr1->size == 0 || arr2->size == 0 ) {
        return multi_result;
    } 
    for (int h = 0; h < arr1->size; h++) {
        Array* row_result = malloc(sizeof(Array)); 
        array_init(row_result); 
        multidim_array_add(multi_result, row_result);
    }
    for (int i = 0; i < arr2-> data[0] -> size; i++) {
        for (int h = 0; h < arr1->size; h++) { 
            int scalar_r = 0;
            for (int k = 0; k < arr1->data[h]->size; k++) {
                int arr2_h_row_i_col = (arr2 -> data[k] -> data[i]); 
                int arr1_h_row_j_col = (arr1 -> data[h] -> data[k]); 
                scalar_r += (arr1_h_row_j_col * arr2_h_row_i_col); 
            }
            array_add(multi_result -> data[h], scalar_r); 
        }
    }
    return multi_result;
}