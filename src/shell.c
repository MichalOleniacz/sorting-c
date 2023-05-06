//
// Created by Michał Oleniacz on 29/04/2023.
//

#include "shell.h"

#define FN_NAME "shell_sort"

void shell_sort(TestObj* testObj)
{
    testObj->name = FN_NAME;
    for( int gap = (testObj->Arr->size)/2; gap > 0; gap /= 2)
    {
        for ( int i = gap; i < testObj->Arr->size; i++)
        {
            int tmp = testObj->Arr->elements[i];

            int j;
            for( j = i; j >= gap && testObj->Arr->elements[j - gap] > tmp; j -= gap)
                testObj->Arr->elements[j] = testObj->Arr->elements[j - gap];

            testObj->Arr->elements[j] = tmp;
        }
    }
}