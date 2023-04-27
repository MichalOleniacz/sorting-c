//
// Created by Michał Oleniacz on 25/04/2023.
//

#include <time.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>
#include <stdio.h>
#include "driver.h"
#include "utils.h"
#include "io.h"

void benchmark(void (*func)(TestObj *testObj), TestObj *testObjIn)
{
    struct timeval start, end;

    gettimeofday(&start, NULL);
    func(testObjIn);
    gettimeofday(&end, NULL);

    testObjIn->result = (end.tv_sec * SECOND_TO_MICROSECOND_RATIO + end.tv_usec)
                        - (start.tv_sec * SECOND_TO_MICROSECOND_RATIO + start.tv_usec);

    print_array(testObjIn->Arr);
}

void *benchmark_thread(void *testObjVoid)
{
    TestObj* testObj = testObjVoid;

    struct timeval start, end;

    gettimeofday(&start, NULL);
    testObj->func(testObj);
    gettimeofday(&end, NULL);

    testObj->result = (end.tv_sec * SECOND_TO_MICROSECOND_RATIO + end.tv_usec)
                      - (start.tv_sec * SECOND_TO_MICROSECOND_RATIO + start.tv_usec);
    testObj = NULL;
    free(testObj);
    pthread_exit(NULL);
}

void benchmark_group(Array *A, TestFnArray funcArray, int benchmark_size, int toggle, int save)
{
    pthread_t ptid[benchmark_size];
    TestObj **testObjArray = (TestObj**)malloc(sizeof(TestObj)*benchmark_size);

    printf("Starting benchmark for %d elements...\n", A->size);
    for (int i = 0; i < benchmark_size; i++) {
        Array *testArray = array_copy(A);
        TestObj* testObj = testObj_constructor(testArray);
        testObj->func = funcArray[i];

        pthread_create(&ptid[i], NULL, benchmark_thread, testObj);
        testObjArray[i] = testObj;
    }



    for(int i = 0; i < benchmark_size; i++)
        pthread_join(ptid[i], NULL);

    if(save == 1)
    {
        if(toggle == 1)
            initialize_csv(testObjArray, benchmark_size);
        write_to_csv(testObjArray, benchmark_size, A->size);
    }

    for (int i = 0; i < benchmark_size; i++) {
        printf("%s %d %ld\n", testObjArray[i]->name, testObjArray[i]->Arr->size, testObjArray[i]->result);
        testObj_destructor(testObjArray[i]);
    }

    array_destructor(A);
    free(testObjArray);
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
    free(testObj);
}
