#include "src/insertion.h"
#include "src/selection.h"
#include "src/bubble.h"
#include "src/utils.h"
#include "src/driver.h"
#include "src/io.h"
#include "src/array.h"
#include <stdio.h>

#define FLAG_GENERATE_DATAFILE          0
#define FLAG_POPULATE_FROM_DATAFILE     1
#define FLAG_POPULATE_RANDOM            0
#define FLAG_AUTOMATED_BENCHMARK        0

#define FLAG_USE_MANUAL_SELECTION       1
#define FLAG_TEST_GROUP_ONE             1

#define DATAFILE_100                    "dane"
#define DATAFILE_10000                  "dane10000"
#define DATAFILE_100000                 "dane100000"
#define DATAFILE_1000000                "dane1000000"

#define SELECTION_ALL_GROUP_I           6
#define SELECTION_ALL_GROUP_II          7
#define SELECTION_ALL                   8

#define SIZE_GROUP_I                    3
#define SIZE_GROUP_II                   3
#define SIZE_ALL                        6

/**
 * Add missing algorithms
 * Refactor main
 * Upgrade algorithm selection
*/

int main() {
    int n = get_arr_size();
    int selection = SELECTION_ALL, increment;

    TestFn fn_group_one[SIZE_GROUP_I] = {selection_sort, bubble_sort, insertion_sort};
    TestFn fn_group_two[SIZE_GROUP_II] = {selection_sort, bubble_sort, insertion_sort};
    TestFn fn_all[SIZE_ALL] = {selection_sort, bubble_sort, insertion_sort};

    if(FLAG_USE_MANUAL_SELECTION == 1 && FLAG_AUTOMATED_BENCHMARK == 0)
        selection = get_algorithm_selection();

    if(FLAG_GENERATE_DATAFILE == 1)
        generate_data_file(n, DATAFILE_1000000);

    if(FLAG_AUTOMATED_BENCHMARK == 1)
    {
        increment = get_benchmark_increment();
        int toggle = 1;

        for(int i = 0; i <= n; i=i+increment)
        {
            Array *A = int_array_constructor(i);
            if(FLAG_POPULATE_RANDOM == 1)
                populate_rand(A);
            else if(FLAG_POPULATE_FROM_DATAFILE == 1)
                populate_from_datafile(A, DATAFILE_1000000);
            benchmark_group(A, fn_all, SIZE_GROUP_I, toggle, 1);
            toggle = 0;
        }
        return 0;
    }

    Array *A = int_array_constructor(n);

    if(FLAG_POPULATE_RANDOM == 1)
        populate_rand(A);
    else if(FLAG_POPULATE_FROM_DATAFILE == 1)
        populate_from_datafile(A, DATAFILE_1000000);

    print_array(A);

    if(selection < 3)
    {
        TestObj* testObj = testObj_constructor(A);
        benchmark(fn_all[selection], testObj);
        printf("%s %ld\n", testObj->name, testObj->result);
        testObj_destructor(testObj);
    } else if( selection == SELECTION_ALL_GROUP_I ) {
        benchmark_group(A, fn_group_one, SIZE_GROUP_I, 0, 0);
    } else if( selection == SELECTION_ALL_GROUP_II ) {
        benchmark_group(A, fn_group_two, SIZE_GROUP_I, 0, 0);
    }

    return 0;
}
