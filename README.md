# pattern_associator
Pattern associator utilizing associative memory architecture for neural network

- Input.txt: Textfile of charaters representing specific patterns
ex)
    w....
    .w...
    ..w..
    ....w.
    ....w

- weight.txt: Textfile of integers representing weights in our pattern associator
- threshold.txt: Textfile of integers representing Thresholding value in our pattern associator

# usage
compile: gcc -o "executable filename" main.c ./a_Pattern_Translator/trans.c ./b_Pattern_Info_Loader/pat_info_loader.c ./c_Process_Unit/process_unit.c  
execute: ./pa

Copyright by Geesun Jang
