#include "log.h"
#include "src/insertion.h"
#include "src/selection.h"
#include "src/bubble.h"
#include "src/utils.h"
#include "src/driver.h"
#include "src/io.h"
#include "src/array.h"
#include <time.h>
#include <stdio.h>

#define FLAG_GENERATE_DATAFILE          0
#define FLAG_POPULATE_FROM_DATAFILE     1
#define FLAG_POPULATE_RANDOM            0

#define FLAG_USE_MANUAL_SELECTION       1
#define FLAG_TEST_GROUP_ONE             1

#define DATAFILE_100                    "dane"
#define DATAFILE_10000                  "dane10000"
#define DATAFILE_100000                 "dane100000"
#define DATAFILE_1000000                "dane1000000"

#define SELECTION_ALL_GROUP_I           6
#define SELECTION_ALL_GROUP_II          7
#define SELECTION_ALL                   8


int main() {
    int n = get_arr_size();
    Array *A = array_constructor(n);

    int selection = SELECTION_ALL;

    if(FLAG_USE_MANUAL_SELECTION == 1)
        selection = get_algorithm_selection();

    if(FLAG_GENERATE_DATAFILE == 1)
        generate_data_file(n, DATAFILE_1000000);
    else if(FLAG_POPULATE_RANDOM == 1)
        populate_rand(A);
    else if(FLAG_POPULATE_FROM_DATAFILE == 1)
        populate_from_datafile(A, DATAFILE_1000000);

    print_array(A);

    TestFn funcArray[3] = {selection_sort, bubble_sort, insertion_sort};
    TestObj *testObjArray[3] = {};

    if(selection < 3)
    {
        TestObj* testObj = testObj_constructor(A);
        benchmark(funcArray[selection], testObj);
        printf("%s %lf\n", testObj->name, testObj->result);
        testObj_destructor(testObj);
    } else if( selection == SELECTION_ALL_GROUP_I ) {
        for (int i = 0; i < 3; i++) {
            Array *testArray = array_copy(A);
            TestObj* testObj = testObj_constructor(testArray);
            benchmark(funcArray[i], testObj);
            testObjArray[i] = testObj;
            printf("%s %lf\n", testObj->name, testObj->result);
        }

        for (int i = 0; i < 3; i++) {
            testObj_destructor(testObjArray[i]);
        }

        array_destructor(A);
    }

    return 0;
}
