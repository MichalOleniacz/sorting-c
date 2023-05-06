//
// Created by Michał Oleniacz on 24/04/2023.
//
#include "selection.h"

#define FN_NAME "selection_sort"

void selection_sort(TestObj *testObj)
{
    int min_idx = 0, i = 0;
    testObj->name = FN_NAME;

    while(i < testObj->Arr->size)
    {
        for(int j = i; j < testObj->Arr->size; j++)
            if(testObj->Arr->elements[j] < testObj->Arr->elements[min_idx])
                min_idx = j;

        int tmp = testObj->Arr->elements[i];
        testObj->Arr->elements[i] = testObj->Arr->elements[min_idx];
        testObj->Arr->elements[min_idx] = tmp;
        i++;
    }
}