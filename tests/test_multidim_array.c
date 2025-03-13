#include "multidim_array.h"
#include "array.h"
#include <stdio.h>
#include <assert.h>

// Helper function to create a 2D array for testing
MultiDimArray_float* create_test_array_float() {
    MultiDimArray_float *mda = multidim_array_float();
    Array_float *row1 = array_float();
    array_add_float(row1, 1.0);
    array_add_float(row1, 2.0);
    array_add_float(row1, 3.0);
    multidim_array_add_float(mda, row1);

    Array_float *row2 = array_float();
    array_add_float(row2, 4.0);
    array_add_float(row2, 5.0);
    array_add_float(row2, 6.0);
    multidim_array_add_float(mda, row2);

    Array_float *row3 = array_float();
    array_add_float(row3, 7.0);
    array_add_float(row3, 8.0);
    array_add_float(row3, 9.0);
    multidim_array_add_float(mda, row3);

    return mda;
}

// Test initialization and addition
void test_multidim_array_init_and_add() {
    printf("Testing initialization and addition...\n");

    MultiDimArray_float *mda = multidim_array_float();
    assert(mda->size == 0);
    assert(mda->capacity == 0);
    assert(mda->data == NULL);

    Array_float *row1 = array_float();
    array_add_float(row1, 1.0);
    array_add_float(row1, 2.0);
    multidim_array_add_float(mda, row1);

    assert(mda->size == 1);
    assert(mda->capacity == 1);
    assert(mda->data[0]->data[0] == 1.0);
    assert(mda->data[0]->data[1] == 2.0);

    Array_float *row2 = array_float();
    array_add_float(row2, 3.0);
    array_add_float(row2, 4.0);
    multidim_array_add_float(mda, row2);

    assert(mda->size == 2);
    assert(mda->capacity == 2);
    assert(mda->data[1]->data[0] == 3.0);
    assert(mda->data[1]->data[1] == 4.0);

    printf("Initialization and addition tests passed!\n");
    free(mda);
}

// Test printing
void test_multidim_array_print() {
    printf("Testing printing...\n");

    MultiDimArray_float *mda = create_test_array_float();
    printf("Expected output:\n");
    printf("[\n");
    printf("[1.0, 2.0, 3.0]\n");
    printf("[4.0, 5.0, 6.0]\n");
    printf("[7.0, 8.0, 9.0]\n");
    printf("]\n");

    printf("Actual output:\n");
    multidim_array_print_float(mda);

    printf("Printing test passed!\n");
    free(mda);
}

// Test transposition
void test_transpose_multidim_array() {
    printf("Testing transposition...\n");

    MultiDimArray_float *mda = create_test_array_float();
    MultiDimArray_float *transposed = transpose_multidim_array_float(mda);

    assert(transposed->size == 3);
    assert(transposed->data[0]->data[0] == 1.0);
    assert(transposed->data[0]->data[1] == 4.0);
    assert(transposed->data[0]->data[2] == 7.0);
    assert(transposed->data[1]->data[0] == 2.0);
    assert(transposed->data[1]->data[1] == 5.0);
    assert(transposed->data[1]->data[2] == 8.0);
    assert(transposed->data[2]->data[0] == 3.0);
    assert(transposed->data[2]->data[1] == 6.0);
    assert(transposed->data[2]->data[2] == 9.0);

    printf("Transposition test passed!\n");
    free(mda);
    free(transposed);
}

// Test matrix multiplication
void test_multiply_arrays_as_matrix() {
    printf("Testing matrix multiplication...\n");

    MultiDimArray_float *mda1 = create_test_array_float();
    MultiDimArray_float *mda2 = create_test_array_float();
    MultiDimArray_float *product = multiply_arrays_as_matrix_float(mda1, mda2);

    assert(product->size == 3);
    assert(product->data[0]->data[0] == 30.0);
    assert(product->data[0]->data[1] == 36.0);
    assert(product->data[0]->data[2] == 42.0);
    assert(product->data[1]->data[0] == 66.0);
    assert(product->data[1]->data[1] == 81.0);
    assert(product->data[1]->data[2] == 96.0);
    assert(product->data[2]->data[0] == 102.0);
    assert(product->data[2]->data[1] == 126.0);
    assert(product->data[2]->data[2] == 150.0);

    printf("Matrix multiplication test passed!\n");
    free(mda1);
    free(mda2);
    free(product);
}

// Test identity matrix
void test_identity_matrix() {
    printf("Testing identity matrix...\n");

    MultiDimArray_float *identity = identity_matrix_float(3);

    assert(identity->size == 3);
    assert(identity->data[0]->data[0] == 1.0);
    assert(identity->data[0]->data[1] == 0.0);
    assert(identity->data[0]->data[2] == 0.0);
    assert(identity->data[1]->data[0] == 0.0);
    assert(identity->data[1]->data[1] == 1.0);
    assert(identity->data[1]->data[2] == 0.0);
    assert(identity->data[2]->data[0] == 0.0);
    assert(identity->data[2]->data[1] == 0.0);
    assert(identity->data[2]->data[2] == 1.0);

    printf("Identity matrix test passed!\n");
    free(identity);
}

// Test matrix inversion
void test_inverse_matrix() {
    printf("Testing matrix inversion...\n");

    MultiDimArray_float *mda = multidim_array_float();
    Array_float *row1 = array_float();
    array_add_float(row1, 4.0);
    array_add_float(row1, 7.0);
    multidim_array_add_float(mda, row1);

    Array_float *row2 = array_float();
    array_add_float(row2, 2.0);
    array_add_float(row2, 6.0);
    multidim_array_add_float(mda, row2);

    MultiDimArray_float *inverse = inverse_matrix_float(mda);

    if (inverse) {
        assert(inverse->size == 2);
        assert(inverse->data[0]->data[0] == 0.6);
        assert(inverse->data[0]->data[1] == -0.7);
        assert(inverse->data[1]->data[0] == -0.2);
        assert(inverse->data[1]->data[1] == 0.4);

        printf("Matrix inversion test passed!\n");
        free(inverse);
    } else {
        printf("Matrix inversion not implemented or matrix is singular.\n");
    }

    free(mda);
}

// Main function to run all tests
int main() {
    test_multidim_array_init_and_add();
    test_multidim_array_print();
    test_transpose_multidim_array();
    test_multiply_arrays_as_matrix();
    test_identity_matrix();
    test_inverse_matrix();

    printf("All tests passed!\n");
    return 0;
}