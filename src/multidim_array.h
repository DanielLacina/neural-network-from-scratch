#ifndef MULTIDIM_ARRAY_H
#define MULTIDIM_ARRAY_H

#include "array.h"
#include <stdio.h>
#include <stdlib.h>

// Macro to declare a multi-dimensional array for a specific type
#define DECLARE_MULTIDIM_ARRAY(TYPE)                                      \
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
    void multidim_array_free_##TYPE(MultiDimArray_##TYPE *mda);

// Declare the MultiDimArray for float
DECLARE_MULTIDIM_ARRAY(float)

#endif // MULTIDIM_ARRAY_H