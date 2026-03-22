/*PointerBasicsA.c 
Practical 7, Part 1 (a)
Siddhartha Lama Dong*/

#include <stdio.h>

int main() {

    int num = 42;
    int *ptr;  

    ptr = &num;

  
    printf("Value of num: %d\n", num);
    printf("Address of num: %p\n", (void*)&num);
    printf("Value of ptr: %p\n", (void*)ptr);
    printf("Value pointed to by ptr: %d\n", *ptr);

    
    *ptr = 100;

    printf("\nAfter modification through pointer:\n");
    printf("Value of num: %d\n", num);
    printf("Value pointed to by ptr: %d\n", *ptr);

    return 0;
}