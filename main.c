#include <stdlib.h>
#include <stdio.h>

typedef struct {
    int *data;
    int capacity;
    int size;
} Array;

void array_init(Array *arr) {
    arr->data = NULL;
    arr->capacity = 0; 
    arr->size = 0;
}

void array_add(Array *arr, int value) {
    if (arr->size == arr->capacity) {
        arr->capacity = arr->capacity == 0 ? 1 : arr->capacity * 2; 
        arr->data = realloc(arr->data, arr->capacity * sizeof(int));
    }
    arr->data[arr->size++] = value;
}

void array_add_arr(Array *arr, int arr_data[], int size) {
    for (int i = 0; i < size; i++) {
        array_add(arr, arr_data[i]);
    }
}

void array_print(Array *arr) {
    printf("[");
    for (int i = 0; i < arr->size; i++) {
        printf("%d ", arr->data[i]);
    }
    printf("],\n");
}

typedef struct {
    Array **data;
    int capacity; 
    int size;
} MultiDimensionalArray;

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

Array* multiply_arrays(Array *arr1, Array *arr2) {
    if (arr1->size != arr2->size) {
        return NULL; 
    }
    Array *result_array = malloc(sizeof(Array));  
    array_init(result_array);
    for (int i = 0; i < arr1->size; i++) {
        array_add(result_array, arr1->data[i] * arr2->data[i]);   
    }
    return result_array;
}

Array* multiply_array_by_scalar(Array *arr, int value) {
    Array *result_array = malloc(sizeof(Array));  
    array_init(result_array);
    for (int i = 0; i < arr->size; i++) {
        array_add(result_array, arr->data[i] * value);   
    }
    return result_array;
}

Array* add_arrays(Array *arr1, Array *arr2) {
    if (arr1->size != arr2->size) {
        return NULL; 
    }
    Array *result_array = malloc(sizeof(Array));  
    array_init(result_array);
    for (int i = 0; i < arr1->size; i++) {
        array_add(result_array, arr1->data[i] + arr2->data[i]);   
    }
    return result_array;
}

int main() {
    Array arr1;
    Array arr2; 
    MultiDimensionalArray mda; 
    int arr_data[] = {1, 2};
    array_init(&arr1);
    array_init(&arr2);
    array_add_arr(&arr1, arr_data, 2);
    array_add_arr(&arr2, arr_data, 2);
    multidim_array_add(&mda, &arr1); 
    multidim_array_add(&mda, &arr2); 
    multidim_array_print(&mda);
    // multidim_array_print(multiply_two_multidimensional_arrays(&mda, &mda)); // Uncomment this to print result
}
