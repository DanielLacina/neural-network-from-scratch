#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "multidim_array.h"
#include "array.h"

// Function to free memory for MultiDimensionalArray
void multidim_array_free(MultiDimensionalArray *mda) {
    for (int i = 0; i < mda->size; i++) {
        free(mda->data[i]->data);  // Free individual array data
        free(mda->data[i]);        // Free array structure
    }
    free(mda->data);  // Free multidimensional array
    free(mda);
}

void test_matrix_multiplication_basic() {
    MultiDimensionalArray mda1, mda2, *result;
    multidim_array_init(&mda1);
    multidim_array_init(&mda2);

    // Creating 2x2 matrix mda1 = {{1, 2}, {3, 4}}
    Array row1, row2;
    array_init(&row1);
    array_init(&row2);
    array_add(&row1, 1);
    array_add(&row1, 2);
    array_add(&row2, 3);
    array_add(&row2, 4);
    multidim_array_add(&mda1, &row1);
    multidim_array_add(&mda1, &row2);

    // Creating 2x2 matrix mda2 = {{5, 6}, {7, 8}}
    Array row3, row4;
    array_init(&row3);
    array_init(&row4);
    array_add(&row3, 5);
    array_add(&row3, 6);
    array_add(&row4, 7);
    array_add(&row4, 8);
    multidim_array_add(&mda2, &row3);
    multidim_array_add(&mda2, &row4);

    // Perform matrix multiplication
    result = multiply_arrays_as_matrix(&mda1, &mda2);

    // Expected result = {{19, 22}, {43, 50}}
    assert(result->data[0]->data[0] == 19);
    assert(result->data[0]->data[1] == 22);
    assert(result->data[1]->data[0] == 43);
    assert(result->data[1]->data[1] == 50);

    printf("Test passed: Basic 2x2 matrix multiplication\n");

    // Free memory
    multidim_array_free(result);
}

void test_matrix_multiplication_identity() {
    MultiDimensionalArray identity, arr, *result;
    multidim_array_init(&identity);
    multidim_array_init(&arr);

    // Creating Identity Matrix (2x2)
    Array irow1, irow2;
    array_init(&irow1);
    array_init(&irow2);
    array_add(&irow1, 1);
    array_add(&irow1, 0);
    array_add(&irow2, 0);
    array_add(&irow2, 1);
    multidim_array_add(&identity, &irow1);
    multidim_array_add(&identity, &irow2);

    // Creating a 2x2 matrix arr = {{3, 4}, {5, 6}}
    Array row1, row2;
    array_init(&row1);
    array_init(&row2);
    array_add(&row1, 3);
    array_add(&row1, 4);
    array_add(&row2, 5);
    array_add(&row2, 6);
    multidim_array_add(&arr, &row1);
    multidim_array_add(&arr, &row2);

    // Multiply identity matrix with arr
    result = multiply_arrays_as_matrix(&identity, &arr);

    // Expected result: It should remain unchanged
    assert(result->data[0]->data[0] == 3);
    assert(result->data[0]->data[1] == 4);
    assert(result->data[1]->data[0] == 5);
    assert(result->data[1]->data[1] == 6);

    printf("Test passed: Identity matrix multiplication\n");

    // Free memory
    multidim_array_free(result);
}

void test_matrix_multiplication_empty() {
    MultiDimensionalArray mda1, mda2, *result;
    multidim_array_init(&mda1);
    multidim_array_init(&mda2);

    // Empty matrices
    result = multiply_arrays_as_matrix(&mda1, &mda2);

    // Expecting an empty result
    assert(result->size == 0);

    printf("Test passed: Multiplication with empty matrices\n");

    // Free memory
    multidim_array_free(result);
}

void test_matrix_multiplication_rectangular() {
    MultiDimensionalArray mda1, mda2, *result;
    multidim_array_init(&mda1);
    multidim_array_init(&mda2);

    // Creating 2x3 matrix mda1 = {{1, 2, 3}, {4, 5, 6}}
    Array row1, row2;
    array_init(&row1);
    array_init(&row2);
    array_add(&row1, 1);
    array_add(&row1, 2);
    array_add(&row1, 3);
    array_add(&row2, 4);
    array_add(&row2, 5);
    array_add(&row2, 6);
    multidim_array_add(&mda1, &row1);
    multidim_array_add(&mda1, &row2);

    // Creating 3x2 matrix mda2 = {{7, 8}, {9, 10}, {11, 12}}
    Array row3, row4, row5;
    array_init(&row3);
    array_init(&row4);
    array_init(&row5);
    array_add(&row3, 7);
    array_add(&row3, 8);
    array_add(&row4, 9);
    array_add(&row4, 10);
    array_add(&row5, 11);
    array_add(&row5, 12);
    multidim_array_add(&mda2, &row3);
    multidim_array_add(&mda2, &row4);
    multidim_array_add(&mda2, &row5);

    // Perform multiplication (2x3 * 3x2 = 2x2)
    result = multiply_arrays_as_matrix(&mda1, &mda2);

    // Expected result: {{58, 64}, {139, 154}}
    assert(result->data[0]->data[0] == 58);
    assert(result->data[0]->data[1] == 64);
    assert(result->data[1]->data[0] == 139);
    assert(result->data[1]->data[1] == 154);

    printf("Test passed: Rectangular matrix multiplication (2x3 * 3x2)\n");

    // Free memory
    multidim_array_free(result);
}

float main() {
    test_matrix_multiplication_basic();
    test_matrix_multiplication_identity();
    test_matrix_multiplication_empty();
    test_matrix_multiplication_rectangular();
    printf("All tests passed!\n");
    return 0;
}
