#include "process_unit.h"

/* Functionality
1) Compute multiplication of input and weight
2) Sum all the result from 1)
3) Compare the thresholding level and result from 2)
4) return if the output detects pattern
5) make output result as file or array */

int* process_unit(int* input_arr, int input_dim, int** weights, int pattern_count, int* threshold){

    int* compute_result= compute_unit(input_arr, input_dim, weights, pattern_count, threshold);
    int* threshold_result = threshold_unit(compute_result, threshold, pattern_count, 1);
    return threshold_result;
}

int* compute_unit(int* input_arr, int input_dim, int** weights, int pattern_count, int* threshold){
    int* process_result= malloc(sizeof(int)*pattern_count);

    for(int i=0; i<pattern_count; i++){
        process_result[i] = 0;
        for(int j=0; j<input_dim ; j++){
            process_result[i]+=input_arr[j]*weights[i][j];
        }
    }
    return process_result;
}

int* threshold_unit(int* compute_result, int* threshold, int pattern_count, int dbg){
    int* threshold_result = (int*)malloc(sizeof(int)*pattern_count);
    for(int i=0; i<pattern_count; i++){
        if (dbg){
            printf("%dth Compute/Threshold: %2d / %2d\n", i, compute_result[i], threshold[i]);
        }
        if(compute_result[i]>=threshold[i]) threshold_result[i] = 1;
        else    threshold_result[i] = 0;
    }

    return threshold_result;
}

void output_print(int* output_arr, int pattern_count){
    printf("<Result of Pattern Associator>\n");
    for(int i=0; i<pattern_count; i++){
        printf("%dth pattern: %d\n",i, output_arr[i] );
    }
}
