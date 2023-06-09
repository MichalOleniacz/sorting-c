//
// Created by Michał Oleniacz on 25/04/2023.
//

#ifndef SORTOWANIE_IO_H
#define SORTOWANIE_IO_H

#include "array.h"
#include "benchmark.h"

extern int get_arr_size(void);
int get_benchmark_increment(void);
int get_algorithm_selection(void);
void generate_data_file(int n, const char* filename);
void initialize_csv(TestObj **testObjArr, int no_functions);
void read_to_array(Array *arr, const char* filename);
void write_to_csv(TestObj** testObjArr, int no_functions, int no_elements);
void batchwrite_to_csv(TestObj **testObjArray, int total_count, int no_functions);

#endif //SORTOWANIE_IO_H
