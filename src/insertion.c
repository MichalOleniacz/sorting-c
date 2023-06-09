//
// Created by Michał Oleniacz on 17/04/2023.
//

#include "insertion.h"

#define FN_NAME "insertion_sort"

void insertion_sort(TestObj *testObj) {
    int i, j, key;

    testObj->name = FN_NAME;
    for ( i = 1; i < testObj->Arr->size; i++)
    {
        key = testObj->Arr->elements[i];
        j = i-1;

        while(j >= 0 && testObj->Arr->elements[j] > key)
        {
            testObj->Arr->elements[j+1] = testObj->Arr->elements[j];
            j = j - 1;
        }
        testObj->Arr->elements[j+1] = key;
    }
}