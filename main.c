#include "./a_Pattern_Translator/trans.h"
#include "./b_Pattern_Info_Loader/pat_info_loader.h"
#include "./c_Process_Unit/process_unit.h"

#define input_file "input.txt"
#define weight_file "weight.txt"
#define threshold_file "threshold.txt"

#define DEBUG 1

/* argc: # of arguments argv[0]: executable file name argv[1...]: argument name */
int main(int argc, const char* argv[]){
    
    /* Load Input pattern data from input.txt file  */
    int* input_len = (int*)malloc(sizeof(int));
    int* input_pattern = input_to_bit_translation(input_file,input_len);
    print_pattern(input_pattern, input_len);

    /* Calculate the dimension size of input data */
    int dim_length = *input_len;
    int dim_size = dim_length*dim_length;
    
    /* Initialize Pattern info from weight.txt and threshold.txt file */
    Pattern_info pat;
    pat.num_of_patterns = (int*)malloc(sizeof(int));
    pat.weights = weight_load(weight_file, dim_size, pat.num_of_patterns);
    pat.thresholds = threshold_load(threshold_file, *pat.num_of_patterns);
    
    /* print data on DEBUG MODE*/
    if(DEBUG) _print_weight(dim_size, *pat.num_of_patterns, pat.weights);
    if(DEBUG) _print_threshold(*pat.num_of_patterns, pat.thresholds);

    int* output_result = process_unit(input_pattern, dim_size, pat.weights, *pat.num_of_patterns, pat.thresholds);
    if(DEBUG)output_print(output_result, *pat.num_of_patterns);

    return 0;
}