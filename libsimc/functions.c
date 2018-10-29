#include <stdio.h>
#include <stdbool.h>
#include "functions.h"

#define ERROR -1
#define SUCCESS 0

// #define COUNT_OF(x) ((sizeof(x)/sizeof(0[x])) / ((size_t)(!(sizeof(x) % sizeof(0[x])))))

int map(int* numlist, func_map_t func){
    /*
     * map - Call a function on each element of an integer pointer
     * @numlist: the array of int's
     * @func: the function to call
     *
     * Iterate through the numbers and call @func on each one.
     *
     * Return: -1 if there are NULL arguments, 0 otherwise.
     */

    if( numlist == NULL || func == NULL){
        return ERROR;
    }

    for( int* ptr = numlist; *ptr; ptr++){
        (func)(ptr);
    }

    return SUCCESS;
}

int reduce(int* numlist, func_reduce_t func, int* data ){
    /*
     * reduce - Combine all elements
     * @numlist: the array to be used
     * @func: a function to call on each element and the final result
     * @data: a pointer to where the resulting data will be stored
     * 
     * Iterate through the numbers and call @func on each one.
     * 
     * Return: -1 if there are NULL arguments, 0 otherwise.
     * 
     */

    if( numlist == NULL || func == NULL || data == NULL){
        return ERROR;
    }

    *data = *numlist++;
    for( int* ptr = numlist; *ptr; ptr++){
        (func)(data, *ptr);
    }

    return SUCCESS;

}

int length(int* numlist){
    if(numlist == NULL){
        return ERROR;
    }
    int length = 0;
    for( int* ptr = numlist; *ptr; ptr++){
        length++;
    }
    return length;
}