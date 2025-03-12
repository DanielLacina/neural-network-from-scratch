#include "array.h"
#include <stdio.h>

void array_init(Array *arr) {
    arr->data = NULL;
    arr->capacity = 0; 
    arr->size = 0;
}

Array *array() {
    Array* array = malloc(sizeof(Array)); 
    array_init(array);
    return array;
}

void array_add(Array *arr, float value) {
    if (arr->size == arr->capacity) {
        arr->capacity = arr->capacity == 0 ? 1 : arr->capacity * 2; 
        arr->data = realloc(arr->data, arr->capacity * sizeof(float));
    }
    arr->data[arr->size++] = value;
}

void array_add_arr(Array *arr, float arr_data[], int size) {
    for (int i = 0; i < size; i++) {
        array_add(arr, arr_data[i]);
    }
}

void array_print(Array *arr) {
    printf("[");
    for (int i = 0; i < arr->size; i++) {
        printf("%f ", arr->data[i]);
    }
    printf("],\n");
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

Array* multiply_array_by_scalar(Array *arr, float value) {
    Array *result_array = array();  
    for (int i = 0; i < arr->size; i++) {
        array_add(result_array, arr->data[i] * value);   
    }
    return result_array;
}

Array* add_arrays(Array *arr1, Array *arr2) {
    if (arr1->size != arr2->size) {
        return NULL; 
    }
    Array *result_array = array();  
    for (int i = 0; i < arr1->size; i++) {
        array_add(result_array, arr1->data[i] + arr2->data[i]);   
    }
    return result_array;
}

float sum_array(Array *arr) {
    float sum = 0;
    for (int i = 0; i < arr->size; i++) {
        sum += arr->data[i];
    }
    return sum;
}