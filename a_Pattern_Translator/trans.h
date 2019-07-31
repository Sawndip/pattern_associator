#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define _on_signal 'o'
#define _off_signal 'x'

int* _encoding_to_bit(char* input_pattern, int _length, int _size);
int* input_to_bit_translation(const char* filename, int* len);
void print_pattern(int* stream, int* length);