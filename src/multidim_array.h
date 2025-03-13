#ifndef MULTIDIM_ARRAY_H
#define MULTIDIM_ARRAY_H

#include "array.h"
#include <stdio.h>
#include <stdlib.h>

// Macro to define a multi-dimensional array for a specific type
#define DEFINE_MULTIDIM_ARRAY(TYPE)                                      \
    typedef struct {                                                     \
        Array_##TYPE **data;                                             \
        size_t size;                                                     \
        size_t capacity;                                                 \
    } MultiDimArray_##TYPE;                                              \
                                                                         \
    void multidim_array_init_##TYPE(MultiDimArray_##TYPE *mda);          \
    MultiDimArray_##TYPE *multidim_array_##TYPE();                       \
    void multidim_array_add_##TYPE(MultiDimArray_##TYPE *mda, Array_##TYPE *inner_array); \
    void multidim_array_print_##TYPE(MultiDimArray_##TYPE *mda);         \
    MultiDimArray_##TYPE* transpose_multidim_array_##TYPE(MultiDimArray_##TYPE *mda); \
    MultiDimArray_##TYPE* multiply_arrays_as_matrix_##TYPE(MultiDimArray_##TYPE *mda1, MultiDimArray_##TYPE *mda2); \
    MultiDimArray_##TYPE* identity_matrix_##TYPE(size_t size);           \
    MultiDimArray_##TYPE* inverse_matrix_##TYPE(MultiDimArray_##TYPE *mda); \
    void swap_rows_##TYPE(MultiDimArray_##TYPE *mda, size_t row1, size_t row2); \
    MultiDimArray_##TYPE* cloned_multidim_array_##TYPE(MultiDimArray_##TYPE *mda); \
    void multidim_array_free_##TYPE(MultiDimArray_##TYPE *mda);          \
                                                                         \
    void multidim_array_init_##TYPE(MultiDimArray_##TYPE *mda) {         \
        mda->data = NULL;                                                \
        mda->size = 0;                                                   \
        mda->capacity = 0;                                               \
    }                                                                    \
                                                                         \
    MultiDimArray_##TYPE *multidim_array_##TYPE() {                      \
        MultiDimArray_##TYPE *mda = malloc(sizeof(MultiDimArray_##TYPE));\
        multidim_array_init_##TYPE(mda);                                 \
        return mda;                                                      \
    }                                                                    \
                                                                         \
    void multidim_array_add_##TYPE(MultiDimArray_##TYPE *mda, Array_##TYPE *inner_array) { \
        if (mda->size == mda->capacity) {                                \
            mda->capacity = (mda->capacity == 0) ? 1 : mda->capacity * 2;\
            mda->data = realloc(mda->data, mda->capacity * sizeof(Array_##TYPE*)); \
        }                                                                \
        mda->data[mda->size++] = inner_array;                            \
    }                                                                    \
                                                                         \
    void multidim_array_print_##TYPE(MultiDimArray_##TYPE *mda) {        \
        printf("[\n");                                                   \
        for (size_t i = 0; i < mda->size; i++) {                         \
            array_print_##TYPE(mda->data[i]);                            \
        }                                                                \
        printf("]\n");                                                   \
    }                                                                    \
                                                                         \
    MultiDimArray_##TYPE* transpose_multidim_array_##TYPE(MultiDimArray_##TYPE *mda) { \
        if (mda->size == 0) return NULL;                                 \
        size_t cols = mda->data[0]->size;                                \
        MultiDimArray_##TYPE *transposed = multidim_array_##TYPE();      \
        for (size_t j = 0; j < cols; j++) {                              \
            Array_##TYPE *new_row = array_##TYPE();                      \
            for (size_t i = 0; i < mda->size; i++) {                     \
                array_add_##TYPE(new_row, mda->data[i]->data[j]);        \
            }                                                            \
            multidim_array_add_##TYPE(transposed, new_row);              \
        }                                                                \
        return transposed;                                               \
    }                                                                    \
                                                                         \
    MultiDimArray_##TYPE* multiply_arrays_as_matrix_##TYPE(MultiDimArray_##TYPE *mda1, MultiDimArray_##TYPE *mda2) { \
        if (mda1->size == 0 || mda2->size == 0 || mda1->data[0]->size != mda2->size) return NULL; \
        MultiDimArray_##TYPE *result = multidim_array_##TYPE();          \
        for (size_t i = 0; i < mda1->size; i++) {                        \
            Array_##TYPE *new_row = array_##TYPE();                      \
            for (size_t j = 0; j < mda2->data[0]->size; j++) {           \
                TYPE sum = 0;                                            \
                for (size_t k = 0; k < mda2->size; k++) {                \
                    sum += mda1->data[i]->data[k] * mda2->data[k]->data[j]; \
                }                                                        \
                array_add_##TYPE(new_row, sum);                          \
            }                                                            \
            multidim_array_add_##TYPE(result, new_row);                  \
        }                                                                \
        return result;                                                   \
    }                                                                    \
                                                                         \
    MultiDimArray_##TYPE* identity_matrix_##TYPE(size_t size) {          \
        MultiDimArray_##TYPE *identity = multidim_array_##TYPE();        \
        for (size_t i = 0; i < size; i++) {                              \
            Array_##TYPE *row = array_##TYPE();                          \
            for (size_t j = 0; j < size; j++) {                          \
                array_add_##TYPE(row, (i == j) ? 1 : 0);                 \
            }                                                            \
            multidim_array_add_##TYPE(identity, row);                    \
        }                                                                \
        return identity;                                                 \
    }                                                                    \
                                                                         \
    MultiDimArray_##TYPE* inverse_matrix_##TYPE(MultiDimArray_##TYPE *mda) { \
        MultiDimArray_##TYPE* i_mda = identity_matrix_##TYPE(mda->size);  \
        MultiDimArray_##TYPE* mda_copy = cloned_multidim_array_##TYPE(mda); \
        for (size_t i = 0; i < mda->size; i++) {                         \
            size_t pivet_row_i = i;                                      \
            while (pivet_row_i < mda_copy->size && mda_copy->data[pivet_row_i]->data[i] == 0) { \
                pivet_row_i++;                                          \
            }                                                            \
            if (pivet_row_i == mda_copy->size) {                         \
                return NULL;                                             \
            }                                                            \
            if (pivet_row_i != i) {                                     \
                swap_rows_##TYPE(mda_copy, pivet_row_i, i);             \
                swap_rows_##TYPE(i_mda, pivet_row_i, i);                \
            }                                                            \
            TYPE pivet_value = mda_copy->data[i]->data[i];               \
            mda_copy->data[i] = multiply_array_by_scalar_##TYPE(mda_copy->data[i], 1/pivet_value); \
            i_mda->data[i] = multiply_array_by_scalar_##TYPE(i_mda->data[i], 1/pivet_value); \
            for (size_t j = 0; j < mda_copy->size; j++) {               \
                if (j != i) {                                           \
                    TYPE factor = mda_copy->data[j]->data[i];            \
                    mda_copy->data[j] = add_arrays_##TYPE(mda_copy->data[j], multiply_array_by_scalar_##TYPE(mda_copy->data[i], -factor)); \
                    i_mda->data[j] = add_arrays_##TYPE(i_mda->data[j], multiply_array_by_scalar_##TYPE(i_mda->data[i], -factor)); \
                }                                                       \
            }                                                            \
        }                                                                \
        return i_mda;                                                   \
    }                                                                    \
                                                                         \
    void swap_rows_##TYPE(MultiDimArray_##TYPE *mda, size_t row1, size_t row2) { \
        Array_##TYPE *temp = mda->data[row1];                            \
        mda->data[row1] = mda->data[row2];                              \
        mda->data[row2] = temp;                                          \
    }                                                                    \
                                                                         \
    MultiDimArray_##TYPE* cloned_multidim_array_##TYPE(MultiDimArray_##TYPE *mda) { \
        MultiDimArray_##TYPE *cloned_mda = multidim_array_##TYPE();      \
        for (size_t i = 0; i < mda->size; i++) {                         \
            Array_##TYPE *cloned_arr = array_##TYPE();                  \
            for (size_t j = 0; j < mda->data[i]->size; j++) {           \
                array_add_##TYPE(cloned_arr, mda->data[i]->data[j]);    \
            }                                                            \
            multidim_array_add_##TYPE(cloned_mda, cloned_arr);           \
        }                                                                \
        return cloned_mda;                                               \
    }                                                                    \
                                                                         \
    void multidim_array_free_##TYPE(MultiDimArray_##TYPE *mda) {         \
        for (size_t i = 0; i < mda->size; i++) {                         \
            array_free_##TYPE(mda->data[i]);                             \
        }                                                                \
        free(mda->data);                                                 \
        free(mda);                                                       \
    }

// Define the MultiDimArray for float
DEFINE_MULTIDIM_ARRAY(float)

#endif // MULTIDIM_ARRAY_H