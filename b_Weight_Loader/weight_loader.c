#include "weight_loader.h"
#define DEBUG 1


int** weight_load(const char* filename, int _input_length, int* _output_line_count_){
    
    FILE* _input_file = fopen(filename, "r");
    int lines = count_lines(_input_file, _input_length);
    
    *_output_line_count_ = lines;
    
    int** weight_buff = _weight_read_and_load_(_input_file, lines, _input_length);
    
    return weight_buff;
}

int** _weight_read_and_load_(FILE* _input_file, int _line_count, int _input_length){
    int size = _line_count*(_input_length+1);
    char* temp_buff = (char*)malloc(sizeof(char)*(size));
    temp_buff[size-1] = '\0';
    fread(temp_buff, size, 1, _input_file);
    fclose(_input_file);

       
    int** _weight_buff = (int**)malloc(sizeof(int*)*_line_count);

    int k=0;

    for(int i=0; i<_line_count; i++){
        _weight_buff[i] = (int*)malloc(sizeof(int)*_input_length);
        for(int j=0; j<_input_length; j++){
            if(temp_buff[k] == '\n') k++;
            _weight_buff[i][j] = temp_buff[k] - 0x30;
            k++;
        }
    }

    free(temp_buff);
    return _weight_buff;
}

int count_lines(FILE* fp, int _line_length){   //check the length of line & count the total line of outputs 
    char buffer[30];

    fscanf(fp, "%s", buffer);
    if(strlen(buffer) != _line_length)  perror("Error: Weight Dimension incompatible");

    fseek(fp, 0, SEEK_END); // seek to end of file
    int size = ftell(fp); // get current file pointer
    fseek(fp, 0, SEEK_SET); // seek back to beginning of file
    int _lines_ = (size+1)/(_line_length+1);
    // proceed with allocating memory and reading the file
    

    return _lines_;
}

void _print_weight(int _length, int lines, int** weight){
    printf("lines: %d\n", lines); 
     for(int i=0; i<lines; i++){
        for (int j=0; j<_length; j++){
            printf("%d ",weight[i][j]);
            }
        printf("\n");
    }
}
int main(int argc, const char** argv){
    int* output_lines = (int*)malloc(sizeof(int));
    int** weights = weight_load(argv[1], 5, output_lines);
    
    if(DEBUG) _print_weight(5, *output_lines, weights);

    return 0;

}