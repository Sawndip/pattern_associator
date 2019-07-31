#include "trans.h"


/* argc: # of arguments argv[0]: executable file name argv[1...]: argument name */
int main(int argc, const char* argv[]){
    
    int* input_len = (int*)malloc(sizeof(int));
    int* input_pattern = input_to_bit_translation(argv[1],input_len);
    print_pattern(input_pattern, input_len);
    return 0;

}