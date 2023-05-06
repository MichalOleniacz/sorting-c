//
// Created by Michał Oleniacz on 25/04/2023.
//

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "io.h"
#include "array.h"
#include "driver.h"

#define UPPER 100
#define LOWER (-100)
#define CSV_FILE "output_rand.csv"
#define NO_ELEMENTS_STR "No. elements"
#define NO_ELEMENTS_STRLEN 13

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
    int i = 0;

    while(!feof(datafile) && i < arr->size ){
        fscanf(datafile, "%d", &arr->elements[i]);
        i++;
    }

    fclose(datafile);
}

void initialize_csv(TestObj **testObjArr, int no_functions)
{
    unsigned long names_len = NO_ELEMENTS_STRLEN + no_functions + 1;
    for(int i = 0; i < no_functions; i++)
        names_len += strlen(testObjArr[i]->name);

    char *buff = (char*)malloc(sizeof(char)*names_len);
    strcat(buff,NO_ELEMENTS_STR);
    strcat(buff,",");

    for(int i = 0; i < no_functions; i++)
    {
        strcat(buff,testObjArr[i]->name);
        if( i != no_functions - 1)
            strcat(buff,",");
    }

    remove(CSV_FILE);
    FILE *csv = fopen(CSV_FILE, "a");
    fputs(buff, csv);
    fputs("\n", csv);
    fclose(csv);
    free(buff);
}

void write_to_csv(TestObj** testObjArr, int no_functions, int no_elements) {
    unsigned long results_len = no_functions + log10(no_elements + 1) + 1;

    for (int i = 0; i < no_functions; i++) {
        int tmp = (int) log10((double) testObjArr[i]->result);
        if (tmp > 0)
            results_len += tmp;
        else results_len += 1;
    }

    char *buff = (char *) malloc(sizeof(char) * results_len);
    char *temp = malloc(sizeof(char)*(log10(no_elements + 1)+1)+1);
    sprintf(temp, "%d,", no_elements);
    strcat(buff,temp);
    free(temp);

    for (int i = 0; i < no_functions; i++) {
        int digits = (int) log10((double) testObjArr[i]->result) + 1;
        char *tmp;
        if (digits > 0)
            tmp = (char *) malloc(sizeof(char) * (digits + no_functions));
        else tmp = (char *) malloc(sizeof(char) * no_functions);
        if (i == no_functions - 1)
            sprintf(tmp, "%d", (int) testObjArr[i]->result);
        else
            sprintf(tmp, "%d,", (int) testObjArr[i]->result);
        strcat(buff, tmp);
        free(tmp);
    }


    FILE *csv = fopen(CSV_FILE, "a");
    fputs(buff, csv);
    fputs("\n", csv);
    fclose(csv);
    free(buff);
}

void batchwrite_to_csv(TestObj **testObjArray, int total_count, int no_functions)
{
    unsigned long results_len = 512;

    for(int i = 0; i < total_count; i += no_functions)
    {
        char *buff = (char *) malloc(sizeof(char) * results_len);
        char *temp = malloc(sizeof(char)*results_len);
        sprintf(temp, "%d,", testObjArray[i]->Arr->size);
        strcat(buff,temp);
        free(temp);

        for(int j = i; j < total_count; j++) {
            int digits = (int) log10((double) testObjArray[j]->result) + 1;
            char *tmp;
            if (digits > 0)
                tmp = (char *) malloc(sizeof(char) * (digits + no_functions));
            else tmp = (char *) malloc(sizeof(char) * no_functions);
            if (i == no_functions - 1)
                sprintf(tmp, "%d", (int) testObjArray[j]->result);
            else
                sprintf(tmp, "%d,", (int) testObjArray[j]->result);
            strcat(buff, tmp);
            free(tmp);
        }

        FILE *csv = fopen(CSV_FILE, "a");
        fputs(buff, csv);
        fputs("\n", csv);
        fclose(csv);
        free(buff);
    }
}