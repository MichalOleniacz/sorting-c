#include "src/insertion.h"
#include "src/selection.h"
#include "src/bubble.h"
#include "src/quicksort.h"
#include "src/shell.h"
#include "src/heap.h"
#include "src/utils.h"
#include "src/benchmark.h"
#include "src/io.h"
#include "src/array.h"
#include <stdio.h>

#define FLAG_GENERATE_DATAFILE          0
#define FLAG_POPULATE_FROM_DATAFILE     0
#define FLAG_POPULATE_RANDOM            1
#define FLAG_POPULATE_DESC              0
#define FLAG_POPULATE_ASC               0
#define FLAG_AUTOMATED_BENCHMARK        1
#define FLAG_AUTOMATED_BENCHMARK_SET    0

#define SET_START                       900000
#define SET_END                         1000001
#define SET_STEP                        100000

#define FLAG_USE_MANUAL_SELECTION       1

#define DATAFILE_MAIN                   "dane"
#define DATAFILE_10000                  "dane10000"
#define DATAFILE_100000                 "dane100000"
#define DATAFILE_1000000                "dane1000000"

#define SELECTION_SELECTION_SORT        0
#define SELECTION_BUBBLE_SORT           1
#define SELECTION_INSERTION_SORT        2
#define SELECTION_QUICKSORT             3
#define SELECTION_SHELL_SORT            4
#define SELECTION_HEAP_SORT             5
#define SELECTION_ALL_GROUP_I           6
#define SELECTION_ALL_GROUP_II          7
#define SELECTION_ALL                   8

#define SIZE_GROUP_I                    3
#define SIZE_GROUP_II                   3
#define SIZE_ALL                        6

int main() {
    int n = get_arr_size();
    int selection = SELECTION_ALL, increment;

    TestFn fn_group_one[SIZE_GROUP_I] = {selection_sort, bubble_sort, insertion_sort};
    TestFn fn_group_two[SIZE_GROUP_II] = {quicksort_adapter, shell_sort, heap_sort};
    TestFn fn_all[SIZE_ALL] = {selection_sort, bubble_sort, insertion_sort, quicksort_adapter, shell_sort, heap_sort};

    if(FLAG_USE_MANUAL_SELECTION == 1 && FLAG_AUTOMATED_BENCHMARK == 0 && FLAG_AUTOMATED_BENCHMARK_SET == 0)
        selection = get_algorithm_selection();

    if(FLAG_GENERATE_DATAFILE == 1)
        generate_data_file(n, DATAFILE_MAIN);

    if(FLAG_AUTOMATED_BENCHMARK == 1)
    {
        increment = get_benchmark_increment();
        int toggle = 1;

        for(int i = 900000; i <= n; i=i+increment)
        {
            Array *A = int_array_constructor(i);
            if(FLAG_POPULATE_RANDOM == 1)
                populate_rand(A);
            else if(FLAG_POPULATE_FROM_DATAFILE == 1)
                populate_from_datafile(A, DATAFILE_MAIN);
            else if (FLAG_POPULATE_ASC)
                populate_asc(A);
            else if (FLAG_POPULATE_DESC)
                populate_desc(A);
            benchmark_group(A, fn_group_one, SIZE_GROUP_II, toggle, 1);
            toggle = 0;
        }
        return 0;
    }

    if(FLAG_AUTOMATED_BENCHMARK_SET == 1) {
        benchmark_set(SET_START, SET_END, SET_STEP, fn_all, DATAFILE_MAIN, SIZE_ALL, 1, 1, FLAG_POPULATE_FROM_DATAFILE, FLAG_POPULATE_ASC, FLAG_POPULATE_DESC);
        return 0;
    }

    Array *A = int_array_constructor(n);

    if(FLAG_POPULATE_RANDOM == 1)
        populate_rand(A);
    if(FLAG_POPULATE_FROM_DATAFILE == 1)
        populate_from_datafile(A, DATAFILE_MAIN);
    if(FLAG_POPULATE_DESC == 1)
        populate_desc(A);
    if(FLAG_POPULATE_ASC == 1)
        populate_asc(A);

    print_array(A);

    switch (selection) {
        case SELECTION_INSERTION_SORT:
        case SELECTION_BUBBLE_SORT:
        case SELECTION_SELECTION_SORT:
        case SELECTION_QUICKSORT:
        case SELECTION_SHELL_SORT:
        case SELECTION_HEAP_SORT:
            benchmark_single(A, fn_all[selection]);
            break;
        case SELECTION_ALL_GROUP_I:
            benchmark_group(A, fn_group_one, SIZE_GROUP_I, 0, 0);
            break;
        case SELECTION_ALL_GROUP_II:
            benchmark_group(A, fn_group_two, SIZE_GROUP_II, 0, 0);
            break;
        case SELECTION_ALL:
            benchmark_group(A, fn_all, SIZE_ALL, 0, 0);
            break;
        default:
            printf("Wybrana opcja nie isnieje!\n");
            break;
    }

    return 0;
}
