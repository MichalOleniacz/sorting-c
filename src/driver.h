//
// Created by Michał Oleniacz on 25/04/2023.
//

#ifndef SORTOWANIE_DRIVER_H
#define SORTOWANIE_DRIVER_H

#include <stdlib.h>
#include <string.h>
#include "array.h"

typedef struct TestObj {
    Array *Arr;
    double result;
    char *name;
} TestObj;

typedef void* TestFn;

extern TestObj *benchmark(void (*func)(TestObj *testObj), TestObj *testObjIn);
TestObj *testObj_constructor(Array *A);
void testObj_destructor(TestObj *testObj);

#endif //SORTOWANIE_DRIVER_H
