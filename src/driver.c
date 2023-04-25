//
// Created by Michał Oleniacz on 25/04/2023.
//

#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include "driver.h"

TestObj *benchmark(void (*func)(TestObj *testObj), TestObj *testObjIn)
{
    clock_t t;
    t = clock();
    func(testObjIn);
    t = clock() - t;

    testObjIn->result = ((double)t)/CLOCKS_PER_SEC;

    return testObjIn;
}

TestObj *testObj_constructor(Array *A)
{
    TestObj *testObj = (TestObj*)malloc(sizeof(TestObj));
    testObj->Arr = A;
    return testObj;
}

void testObj_destructor(TestObj *testObj)
{
    array_destructor(testObj->Arr);
    free(testObj->name);
    free(testObj);
}
