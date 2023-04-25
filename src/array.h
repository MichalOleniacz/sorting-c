//
// Created by Michał Oleniacz on 25/04/2023.
//

#ifndef SORTOWANIE_ARRAY_H
#define SORTOWANIE_ARRAY_H

typedef struct Array {
    int size;
    int *elements;
} Array;

Array *array_constructor(int size);
void array_destructor(Array* A);
Array *array_copy(Array *A);
void populate_from_datafile(Array *A, const char *name);
void populate_rand(Array* A);

#endif //SORTOWANIE_ARRAY_H
