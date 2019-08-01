#include "pat_info_loader.h"

int** weight_load(const char* filename, int _input_dim, int* _output_line_count_){
    FILE* _input_file = fopen(filename, "r");
    if(_input_file == NULL) perror("Error: FILE OPEN ERROR");

    *_output_line_count_ = count_lines(_input_file, _input_dim);
    int** weight_buff = _weight_read_and_load_(_input_file, *_output_line_count_, _input_dim);
    return weight_buff;
}

int** _weight_read_and_load_(FILE* _input_file, int _line_count, int _input_dim){
    int size = _line_count*(_input_dim+1);
    char* temp_buff = (char*)malloc(sizeof(char)*(size));
    temp_buff[size-1] = '\0';
    fread(temp_buff, size, 1, _input_file);
    fclose(_input_file);

       
    int** _weight_buff = (int**)malloc(sizeof(int*)*_line_count);

    int k=0;

    for(int i=0; i<_line_count; i++){
        _weight_buff[i] = (int*)malloc(sizeof(int)*_input_dim);
        for(int j=0; j<_input_dim; j++){
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

void _print_weight(int _input_dim, int lines, int** weight){
    printf("**Pattern Weight Info**\n");
    printf("Pattern count: %d\n", lines); 
     for(int i=0; i<lines; i++){
        for (int j=0; j<_input_dim; j++){
            printf("%d ",weight[i][j]);
            }
        printf("\n");
    }
}

int* threshold_load(const char* filename, int _pattern_counts){
    FILE* _input_file = fopen(filename, "r");
    if(_input_file == NULL) perror("Error: FILE OPEN ERROR");
    int* buffer = (int*)malloc(sizeof(int)*_pattern_counts);
    int i = 0;

    while(!feof(_input_file)){
        fscanf(_input_file,"%d", &buffer[i++]);
    }
    fclose(_input_file);

    return buffer;
}

void _print_threshold(int count, int* array){
    printf("**Threshold Info**\n");
    for(int i=0; i<count; i++){
        printf("%d / %d\n",i, array[i]);
    }
}

