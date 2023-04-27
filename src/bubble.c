//
// Created by Michał Oleniacz on 25/04/2023.
//
#include <string.h>
#include <stdlib.h>
#include "utils.h"
#include "bubble.h"

#define FN_NAME "bubble_sort"

void bubble_sort(TestObj *testObj)
{
    int i, j;
    testObj->name = FN_NAME;
    for(i = 0; i < testObj->Arr->size - 1; i++)
        for (j = 0; j < testObj->Arr->size - i - 1; j++)
            if(testObj->Arr->elements[j] > testObj->Arr->elements[j + 1])
                swap(&testObj->Arr->elements[j], &testObj->Arr->elements[j + 1]);
}
