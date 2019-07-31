
#include "trans.h"

#define DEBUG 0

int* input_to_bit_translation(const char* filename, int* len){
    
    char _input_row[30];
    
    FILE* input_file = fopen(filename, "r");
    fscanf(input_file,"%s",_input_row);
    int _dim_row_size = (int)strlen(_input_row);
    int _dim_size = _dim_row_size*_dim_row_size*sizeof(const char)+_dim_row_size;
    *len = _dim_row_size; 
    if(DEBUG){
        printf(" *INPUT FILE INFO*\n");
        printf("FILENAME: input.txt\n");
        printf("DIM: %2d x%2d\n", _dim_row_size,_dim_row_size);
    }

    char* input_buff = (char*) malloc(_dim_size);
    input_buff[_dim_size]= '\0';

    fseek(input_file, 0, SEEK_SET);
    fread(input_buff, _dim_size, 1, input_file);
    fclose(input_file);

    if(DEBUG) printf("%s\n", input_buff); 

    return _encoding_to_bit(input_buff, _dim_row_size, _dim_size);
}
int* _encoding_to_bit(char* input_pattern, int _length, int _size){
    int* _encoded_pattern = (int*)malloc(sizeof(int)*_length*_length);
    int j = 0;

    for(int i=0; i<_size; i++){
        
        if(input_pattern[i]==_on_signal)     _encoded_pattern[j++] = 1;
        if(input_pattern[i]==_off_signal)     _encoded_pattern[j++] = 0;
    }
        
    free(input_pattern);
    return _encoded_pattern;
}

void print_pattern(int* stream, int* length){
    int len = *length;
    printf("Input pattern(%dx%d): ",len,len);
    for(int i=0; i<len; i++){
        for(int j=0; j<len; j++){
            printf("%d",stream[i*len + j]);
        }
        printf(" ");
    }
    printf("\n");
}
