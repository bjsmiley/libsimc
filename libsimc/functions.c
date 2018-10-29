#include <stdio.h>
#include "functions.h"

#define ERROR -1
#define SUCCESS 0

int map(int* numlist, func_t func){
    /*
     * map - Call a function on each element of an integer pointer
     * @numlist: the array of int's
     * @func: the function to call
     *
     * iterate through the numbers and call @func on each one.
     *
     * Return: -1 there are NULL arguments, 0 otherwise.
     */

    if( numlist == NULL || func == NULL){
        return ERROR;
    }

    for( int* ptr = numlist; *ptr; ptr++){
        (func)(ptr);
    }

    return SUCCESS;
}