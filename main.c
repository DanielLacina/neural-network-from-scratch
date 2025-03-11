#include <stdlib.h>
#include <stdio.h>
#include "array.h"
#include "multidim_array.h"



int main() {
    Array arr1;
    Array arr2; 
    MultiDimensionalArray mda; 
    int arr_data[] = {1, 2};
    array_init(&arr1);
    array_init(&arr2);
    array_add_arr(&arr1, arr_data, 2);
    array_add_arr(&arr2, arr_data, 2);
    // multidim_array_add(&mda, &arr1); 
    // multidim_array_add(&mda, &arr2); 
    // multidim_array_print(&mda);
    // multidim_array_print(transpose_multidim_array(&mda));
    // multidim_array_print(multiply_two_multidimensional_arrays(&mda, &mda)); // Uncomment this to print result
}
