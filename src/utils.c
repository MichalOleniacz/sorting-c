//
// Created by Michał Oleniacz on 17/04/2023.
//
#include <stdio.h>
#include "array.h"

void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void print_array(Array *A) {
    int i;
    for (i = 0; i < A->size; i++)
        printf("%d ", A->elements[i]);
    printf("\n");
}