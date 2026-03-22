/* SecureArrayProcessing.c
   Practical 7, Part 2 (b)
   Siddhartha Lama Dong */

#include <stdio.h>
#include <stdbool.h>

#define MAX_ARRAY_SIZE 1000
#define ARRAY_SIZE 5


bool validateArrayParams(int *arr, int size) {
    
    if (arr == NULL) {
        printf("Error: Array pointer is NULL\n");
        return false;
    }

    
    if (size <= 0) {
        printf("Error: Invalid array size (%d)\n", size);
        return false;
    }

    
    if (size > MAX_ARRAY_SIZE) {
        printf("Error: Array size too large (%d > %d)\n",
               size, MAX_ARRAY_SIZE);
        return false;
    }

    return true;
}


bool secureCalculateSum(int *arr, int size, int *result) {
    
    if (result == NULL) {
        printf("Error: Result pointer is NULL\n");
        return false;
    }

    
    if (!validateArrayParams(arr, size)) {
        return false;
    }

    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += *(arr + i);  
    }

    *result = sum;
    return true;
}


bool secureFindMax(int *arr, int size, int *maxValue) {
    
    if (maxValue == NULL) {
        printf("Error: Max value pointer is NULL\n");
        return false;
    }


    if (!validateArrayParams(arr, size)) {
        return false;
    }

   
    int max = *arr;  
    for (int i = 1; i < size; i++) {
        if (*(arr + i) > max) {
            max = *(arr + i);
        }
    }

    *maxValue = max;
    return true;
}


bool secureAccessElement(int *arr, int size, int index, int *value) {
    
    if (!validateArrayParams(arr, size) || value == NULL) {
        return false;
    }

    
    if (index < 0 || index >= size) {
        printf("Error: Index %d out of bounds [0, %d)\n",
               index, size);
        return false;
    }

    
    *value = *(arr + index);
    return true;
}

int main() {
    int numbers[ARRAY_SIZE] = {10, 20, 30, 40, 50};
    int sum, max, value;


    printf("=== Test 1: Valid Operations ===\n");

    if (secureCalculateSum(numbers, ARRAY_SIZE, &sum)) {
        printf("Sum: %d\n", sum);
    }

    if (secureFindMax(numbers, ARRAY_SIZE, &max)) {
        printf("Maximum: %d\n", max);
    }

    
    printf("\n=== Test 2: NULL Pointer ===\n");
    if (!secureCalculateSum(NULL, ARRAY_SIZE, &sum)) {
        printf("Handled NULL pointer safely\n");
    }

    
    printf("\n=== Test 3: Invalid Size ===\n");
    if (!secureCalculateSum(numbers, -5, &sum)) {
        printf("Rejected negative size\n");
    }

   
    printf("\n=== Test 4: Bounds Checking ===\n");

  
    if (secureAccessElement(numbers, ARRAY_SIZE, 2, &value)) {
        printf("Element at index 2: %d\n", value);
    }

    
    if (!secureAccessElement(numbers, ARRAY_SIZE, 10, &value)) {
        printf("Prevented buffer overflow\n");
    }

    
    if (!secureAccessElement(numbers, ARRAY_SIZE, -1, &value)) {
        printf("Prevented negative index access\n");
    }

    printf("\nAll tests completed successfully!\n");

    return 0;
}