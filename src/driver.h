//
// Created by Michał Oleniacz on 25/04/2023.
//

#ifndef SORTOWANIE_DRIVER_H
#define SORTOWANIE_DRIVER_H

#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "array.h"

#define SECOND_TO_MICROSECOND_RATIO 1000000


typedef struct TestObj {
    Array *Arr;
    long double result;
    char *name;
    void (*func)(struct TestObj*);
} TestObj;

typedef void (*TestFn)(TestObj* testObj);
typedef void (**TestFnArray)(TestObj* testObj);


extern void benchmark(void (*func)(TestObj *testObj), TestObj *testObjIn);
void benchmark_single(Array* A, void (*func)(TestObj *testObj));
void benchmark_group(Array *A, TestFnArray funcArray, int benchmark_size, int toggle, int save);
void benchmark_set(int starting_count, int max_elements, int step, TestFnArray funcArray, char* datafile, int benchmark_size, int toggle, int save, int F_READ_FROM_FILE, int F_RAND_ASC, int F_RAND_DESC);
void *benchmark_thread(void *testObjVoid);
TestObj *testObj_constructor(Array *A);
void testObj_destructor(TestObj *testObj);

#endif //SORTOWANIE_DRIVER_H
