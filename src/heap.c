//
// Created by Michał Oleniacz on 29/04/2023.
//

#include "heap.h"
#include "utils.h"

#define FN_NAME "heap_sort"

void heapify(Array *A, int n, int i)
{
    int largest = i;

    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && A->elements[left] > A->elements[largest])
        largest = left;

    if( right < n && A->elements[right] > A->elements[largest])
        largest = right;

    if (largest != i)
    {
        swap(&A->elements[i], &A->elements[largest]);

        heapify(A, n, largest);
    }
}

void heap_sort(TestObj *testObj)
{
    testObj->name = FN_NAME;
    for ( int i = testObj->Arr->size/2; i >= 0; i--)
        heapify(testObj->Arr, testObj->Arr->size, i);

    for( int i = testObj->Arr->size; i >= 0; i--)
    {
        swap(&testObj->Arr->elements[0], &testObj->Arr->elements[i]);
        heapify(testObj->Arr, i, 0);
    }
}