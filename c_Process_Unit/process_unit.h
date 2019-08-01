#include<stdio.h>
#include<stdlib.h>


int* process_unit(int* input_arr, int input_dim, int** weights, int pattern_count, int* threshold);
int* compute_unit(int* input_arr, int input_dim, int** weights, int pattern_count, int* threshold);
int* threshold_unit(int* compute_result, int* threshold, int pattern_count, int dbg);
void output_print(int* output_arr, int pattern_count);