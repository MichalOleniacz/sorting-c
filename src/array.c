//
// Created by Michał Oleniacz on 25/04/2023.
//
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "array.h"
#include "io.h"

#define UPPER 100
#define LOWER (-100)

Array *int_array_constructor(int size)
{
    Array* arr = malloc(sizeof(Array));
    arr->size = size;
    arr->elements = (int*) malloc(size*sizeof(int));
    return arr;
};

void array_destructor(Array *A)
{
    free(A->elements);
    free(A);
}

Array *array_copy(Array *A)
{
    Array *newArr = (Array*)malloc(sizeof(struct Array));
    newArr->elements = (int*) malloc(A->size*(sizeof(int)));
    newArr->size = A->size;
    memcpy(newArr->elements, A->elements, A->size*sizeof(int));
    return newArr;
}

void populate_rand(Array *A)
{
    srand(time(0));
    for(int i = 0; i < A->size; i++)
        A->elements[i] = (rand() % (UPPER - LOWER + 1)) + LOWER;
}

void populate_from_datafile(Array *A, const char *name)
{
    read_to_array(A, name);
}