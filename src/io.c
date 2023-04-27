//
// Created by Michał Oleniacz on 25/04/2023.
//

#include <stdlib.h>
#include <stdio.h>
#include "io.h"
#include "array.h"
#include "driver.h"

#define UPPER 100
#define LOWER (-100)

int get_arr_size(void)
{
    int x;
    printf("Podaj ilosc elementow: ");
    scanf("%d", &x);
    return x;
}

int get_benchmark_increment(void)
{
    int x;
    printf("Podaj przyrost ilosci elementow: ");
    scanf("%d", &x);
    return x;
}

int get_algorithm_selection(void)
{
    int selection;
    printf("Wybierz jedna z opcji:\n"
           "0: Selection sort\n"
           "1: Bubble sort\n"
           "2: Insertion sort\n"
           "3: Quicksort\n"
           "4: Shell sort\n"
           "5: Kopcowanie\n"
           "6: Wszystkie - grupa I\n"
           "7: Wszystkie - grupa II\n"
           "8: Wszystkie\n");
    scanf("%d", &selection);
    return selection;
}

void generate_data_file(int n, const char* filename)
{
    FILE *datafile = fopen(filename, "w");
    for(int i = 0; i < n; i++)
        fprintf(datafile, "%d\n", (rand() % (UPPER - LOWER + 1)) + LOWER);
    fclose(datafile);
}

void read_to_array(Array *arr, const char* filename)
{
    FILE *datafile = fopen(filename, "r");
    char *line = NULL;
    char *end = NULL;
    size_t len = 0;
    ssize_t read;
    int i = 0;
    int count = 0;

    while(!feof(datafile) && i < arr->size ){
        fscanf(datafile, "%d", &arr->elements[i]);
        i++;
    }

    fclose(datafile);
}

void write_to_csv(TestObj** testObjArr, int n, int no_elements)
{
    for(int i = 0; i < n; i++)
    {
        char buff[256];
    }
}