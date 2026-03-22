/* PointerArraysB.c
   Practical 7, Part 1 (b)
   Siddhartha Lama Dong */

#include <stdio.h>

#define ARRAY_SIZE 5

int main() {
    int numbers[ARRAY_SIZE] = {10, 20, 30, 40, 50};
    int *ptr = numbers;  


    printf("Using array indexing:\n");
    for (int i = 0; i < ARRAY_SIZE; i++) {
        printf("numbers[%d] = %d\n", i, numbers[i]);
    }

 
    printf("\nUsing pointer arithmetic:\n");
    for (int i = 0; i < ARRAY_SIZE; i++) {
        printf("*(ptr + %d) = %d\n", i, *(ptr + i));
    }

    printf("\nUsing pointer indexing:\n");
    for (int i = 0; i < ARRAY_SIZE; i++) {
        printf("ptr[%d] = %d\n", i, ptr[i]);
    }

    return 0;
}