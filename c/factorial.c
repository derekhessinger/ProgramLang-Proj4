/**
 * Derek Hessinger
 * Prof. Ying Li
 * CS 333
 * 10/21/24
 * 
 * This file calculates the factorial of any integer input
 * 
 * gcc -o factorial factorial.c
 * ./factorial (integer)
 */

#include <stdio.h>
#include <stdlib.h>

int factorial(int input){
    int input_idx;
    int orig_input = input;
    for (input_idx = 1; input_idx<orig_input; input_idx++){
        input *= input_idx;
    }
    return input;
}

int main(int argc, char* argv[]){
    // check if argument is provided
    if (argc != 2) {
        printf("Usage: %s <positive integer>\n", argv[0]);
        return 1;
    }
    // cast arg to int
    int N = atoi(argv[1]);
    int (*calc)(const int);
    calc = factorial;
    int result = calc(N);
    printf("%d", result);
}