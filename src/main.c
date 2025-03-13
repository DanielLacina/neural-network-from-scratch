#include <stdlib.h>
#include <stdio.h>
#include "array.h"
#include "multidim_array.h"



int main() {
    MultiDimensionalArray* mda = multidim_array();

    // Manually defining a 3x3 matrix
    float matrix_values[4][4] = {
        {1, 5, 8, 9},
        {7, 4, 3, 10},
        {2, 3, 1, 11},
        {5, 8, 9 , 10}
    };

    // Fill mda with the values
    for (int i = 0; i < 4; i++) {
        Array* row = array();
        for (int j = 0; j < 4; j++) {
            array_add(row, matrix_values[i][j]);
        }
        multidim_array_add(mda, row);
    }

    printf("Original Matrix:\n");
    multidim_array_print(mda);

    MultiDimensionalArray* inv_mda = inverse_matrix(mda);

    if (inv_mda == NULL) {
        printf("Inverse Matrix: Not invertible (singular matrix)\n");
    } else {
        printf("Inverse Matrix:\n");
        multidim_array_print(inv_mda);

        printf("Verification (Original * Inverse):\n");
        multidim_array_print(multiply_arrays_as_matrix(inv_mda, mda));
    }

    return 0;
}