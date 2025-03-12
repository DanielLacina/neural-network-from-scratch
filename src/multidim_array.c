#include "multidim_array.h"

void multidim_array_init(MultiDimensionalArray *mda) {
    mda->data = NULL;
    mda->capacity = 0;
    mda->size = 0;
}

MultiDimensionalArray *multidim_array() {
    MultiDimensionalArray *mda = malloc(sizeof(MultiDimensionalArray));
    multidim_array_init(mda);
    return mda;
}

MultiDimensionalArray* cloned_multidim_array(MultiDimensionalArray *mda) {
    MultiDimensionalArray *cloned_mda = multidim_array();
    for (int i = 0; i < mda->size; i++) {
        Array* cloned_arr = array(); 
        for (int j = 0; j < mda->data[i]->size; j++) {
            array_add(cloned_arr, mda->data[i]->data[j]);
        }
        multidim_array_add(cloned_mda, cloned_arr); 
    }
    return cloned_mda;
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
    MultiDimensionalArray* multi_result = multidim_array(); 
    for (int i = 0; i < arr -> data[0] -> size; i++) {
        Array* result = array(); 
        for (int j = 0; j < arr -> size; j++) {
             array_add(result, arr -> data[j] -> data[i]); 
        } 
        multidim_array_add(multi_result, result); 
    }
    return multi_result;
} 

MultiDimensionalArray* allocated_multidim_array(int arr_count) {
    MultiDimensionalArray* multi_result = multidim_array(); 
    for (int i = 0; i < arr_count; i++) { 
       Array* row = array(); 
       multidim_array_add(multi_result, row); 
    }
    return multi_result;
}

MultiDimensionalArray* multiply_arrays_as_matrix(MultiDimensionalArray *mda1, MultiDimensionalArray * mda2) {
    // mda2 is the matrix getting transformed by mda1 matrix
    if (mda1 -> size == 0 || mda2 -> size == 0) {
        return multidim_array();
    }
    if (mda1 -> size == 0 || mda2 -> size == 0) {
        return NULL;
    }
    if (mda1 -> data[0] -> size != mda2 -> size) {
        return NULL;
    }
    if (mda1 -> data[0] -> size == 0 || mda2 -> data[0] -> size == 0) { 
        if (mda1 -> data[0] -> size != mda2 -> data[0] -> size) {
            return NULL;
        } else {
            return multidim_array();
        }
    }
    MultiDimensionalArray* multi_result = allocated_multidim_array(mda1 -> size);
    for (int i = 0; i < mda2-> data[0] -> size; i++) {
        for (int h = 0; h < mda1->size; h++) { 
            float scalar_r = 0;
            for (int k = 0; k < mda1->data[h]->size; k++) {
                float mda2_h_row_i_col = (mda2 -> data[k] -> data[i]); 
                float mda1_h_row_j_col = (mda1 -> data[h] -> data[k]); 
                scalar_r += (mda1_h_row_j_col * mda2_h_row_i_col); 
            }
            array_add(multi_result -> data[h], scalar_r); 
        }
    }
    return multi_result;
}

MultiDimensionalArray* identity_matrix(int size) {
    MultiDimensionalArray* multi_result = allocated_multidim_array(size);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) { 
            if (i == j) {
                 array_add(multi_result -> data[i], 1);
            } else {
                 array_add(multi_result -> data[i], 0); 
            }
        }
    } 
    return multi_result;
}
MultiDimensionalArray* find_inverse_matrix(MultiDimensionalArray *mda) {
    if (mda -> size == 0 || mda -> data[0] -> size == 0) {
        return multidim_array(); 
    }
    if (mda -> size != mda -> data[0] -> size) {
        return NULL;
    } 
    MultiDimensionalArray* i_mda = identity_matrix(mda -> size);
    MultiDimensionalArray* cloned_mda = cloned_multidim_array(mda);
    for (int i = 0; i < mda -> size; i++) {
        for (int j = 0; j < mda -> size; j++) {
            float cur_cell_value = cloned_mda -> data[j] -> data[i];
            if (i == j && cur_cell_value != 0) {
               cloned_mda -> data[i] = multiply_array_by_scalar(cloned_mda -> data[i], 1 / cur_cell_value);
               i_mda -> data[i] = multiply_array_by_scalar(i_mda -> data[i], 1 / cur_cell_value);
            }
            else if (i != j && cur_cell_value == 0) {}
            else {
                for (int h = 0; h < mda -> size; h++) { 
                    // h is the row that is being added to the current row  
                    float row_value = cloned_mda -> data[h] -> data[i]; 
                    if (row_value != 0 && h != j) {
                        float scalar;
                        if (i == j) {
                            scalar = (cur_cell_value - 1)/-row_value;
                        } else {
                            scalar = cur_cell_value/-row_value;
                        }
                        cloned_mda -> data[i] = add_arrays(cloned_mda -> data[i], multiply_array_by_scalar(cloned_mda -> data[h], scalar));  
                        i_mda -> data[i] = add_arrays(i_mda -> data[i], multiply_array_by_scalar(i_mda -> data[h], scalar));
                        break;
                    } 
                }
            }  
        }
    }
}