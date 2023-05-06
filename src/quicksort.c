//
// Created by Michał Oleniacz on 29/04/2023.
//

#include "quicksort.h"
#include "utils.h"

#define FN_NAME "quick_sort"

void quicksort_adapter(TestObj *testObj)
{
    testObj->name = FN_NAME;
    quicksort(testObj, 0, testObj->Arr->size-1);
}

void quicksort(TestObj *testObj, int left, int right)
{
    if (right <= left) return;

    int i = left - 1;
    int j = right + 1;
    int pivot = testObj->Arr->elements[(left+right)/2];

    while(1)
    {
        while(pivot>testObj->Arr->elements[++i]);
        while(pivot<testObj->Arr->elements[--j]);

        if (i <= j)
            swap(&testObj->Arr->elements[i], &testObj->Arr->elements[j]);
        else break;
    }

    if (j > left)
        quicksort(testObj, left, j);
    if (i < right)
        quicksort(testObj, i, right);
}