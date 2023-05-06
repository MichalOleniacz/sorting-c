//
// Created by Michał Oleniacz on 25/04/2023.
//

#include <time.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>
#include <stdio.h>
#include "benchmark.h"
#include "utils.h"
#include "io.h"

void benchmark(void (*func)(TestObj *testObj), TestObj *testObjIn)
{
    struct timeval start, end;

    gettimeofday(&start, NULL);
    func(testObjIn);
    gettimeofday(&end, NULL);

    testObjIn->result = ((double)end.tv_sec * (double)SECOND_TO_MICROSECOND_RATIO + (double)end.tv_usec)
                        - ((double)start.tv_sec * (double)SECOND_TO_MICROSECOND_RATIO + (double)start.tv_usec);

    print_array(testObjIn->Arr);
}

void benchmark_single(Array* A, void (*func)(TestObj *testObj))
{
    TestObj* testObj = testObj_constructor(A);
    benchmark(func, testObj);
    printf("%s %Lf\n", testObj->name, testObj->result);
//    print_array(testObj->Arr);
    testObj_destructor(testObj);
}

void *benchmark_thread(void *testObjVoid)
{
    TestObj* testObj = testObjVoid;

    struct timeval start, end;

    gettimeofday(&start, NULL);
    testObj->func(testObj);
    gettimeofday(&end, NULL);

    testObj->result = ((double)end.tv_sec * (double)SECOND_TO_MICROSECOND_RATIO + (double)end.tv_usec)
                      - ((double)start.tv_sec * (double)SECOND_TO_MICROSECOND_RATIO + (double)start.tv_usec);
    testObj = NULL;
    free(testObj);
    pthread_exit(NULL);
}

void benchmark_set(int starting_count, int max_elements, int step, TestFnArray funcArray, char* datafile, int benchmark_size, int toggle, int save, int _F_READ_FROM_FILE, int _F_RAND_ASC, int _F_RAND_DESC)
{
    int test_count = (max_elements / step) * benchmark_size;

    pthread_t ptid[test_count];

    TestObj **testObjArray = (TestObj**)malloc(sizeof(TestObj)*test_count);

    int thread_id = 0;

    for(int size = starting_count; size < max_elements; size += step) {
        Array *A = int_array_constructor(size);
        read_to_array(A, datafile);
        for(int i = 0; i < benchmark_size; i++) {
            Array *testArray = array_copy(A);
            TestObj *testObj = testObj_constructor(testArray);
            testObj->func = funcArray[i];
            pthread_create(&ptid[thread_id], NULL, benchmark_thread, testObj);
            testObjArray[thread_id] = testObj;
            thread_id++;
        }
        array_destructor(A);
    }

    for(int i = 0; i < test_count; i++) {
        pthread_join(ptid[i], NULL);
    }

    if(save == 1)
    {
//        initialize_csv(testObjArray, benchmark_size);
        for(int i = 0; i < thread_id; i += benchmark_size)
        {
            TestObj **batch = (TestObj**)malloc(sizeof(TestObj)*benchmark_size);
            int k = 0;
            for(int j = i; j < i+benchmark_size; j++)
            {
                batch[k] = testObjArray[j];
                k++;
            }

            write_to_csv(batch, k, batch[0]->Arr->size);
            k = 0;
            free(batch);
        }
//        batchwrite_to_csv(testObjArray, test_count, benchmark_size);
    }

    for (int i = 0; i < benchmark_size; i++) {
        testObj_destructor(testObjArray[i]);
    }

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
        printf("%s\n", testObjArray[i]->name);
        print_array(testObjArray[i]->Arr);
    }


    for (int i = 0; i < benchmark_size; i++) {
        printf("%s %d %Lf\n", testObjArray[i]->name, testObjArray[i]->Arr->size, testObjArray[i]->result);
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
