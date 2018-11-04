#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

#define ERROR -1
#define SUCCESS 0

#define INT_SIZE sizeof( int )
#define CHAR_SIZE sizeof( char )
#define FLOAT_SIZE sizeof( float )
#define LONG_SIZE sizeof( long )
#define DOUBLE_SIZE sizeof ( double )

//  ====================================================================================
//                                Helper Functions:
//  ====================================================================================

void swap(void* x , void* y, size_t size){
        void* t = malloc( size );

        switch( size ){
        case INT_SIZE:
        memcpy( t , x, size );
        *(int*)x = *(int*)y;
        *(int*)y = *(int*)t; 
        break;
        case CHAR_SIZE:
        memcpy( t , x, size );
        *(char*)x = *(char*)y;
        *(char*)y = *(char*)t; 
        break;
        // case FLOAT_SIZE:
        // mempcpy( *pivot , (float*)list + right, size );
        // break;
        // case LONG_SIZE:
        // mempcpy( *pivot , (long*)list + right, size );
        // break;
        case DOUBLE_SIZE:
        memcpy( t , x, size );
        *(double*)x = *(double*)y;
        *(double*)y = *(double*)t;
        break;
    }
    free( t );

}

void store_pivot_data(void* list, int right, size_t size, void** pivot){

    switch( size ){
        case INT_SIZE:
        memcpy( *pivot , (int*)list + right, size );
        break;
        case CHAR_SIZE:
        memcpy( *pivot , (char*)list + right, size );
        break;
        // case FLOAT_SIZE:
        // mempcpy( *pivot , (float*)list + right, size );
        // break;
        // case LONG_SIZE:
        // mempcpy( *pivot , (long*)list + right, size );
        // break;
        case DOUBLE_SIZE:
        memcpy( *pivot , (double*)list + right, size );
        break;
    }
}

void jump_ptr(void** ptr, unsigned int size, unsigned int pos){
    switch(size){
        case INT_SIZE:
        *ptr = (int*)*ptr + pos;
        break;
        case CHAR_SIZE:
        *ptr = (char*)*ptr + pos;
        break;
        // case FLOAT_SIZE:
        // *ptr = (float*)*ptr + pos;
        // break;
        // case LONG_SIZE:
        // *ptr = (long*)*ptr + pos;
        // break;
        case DOUBLE_SIZE:
        *ptr = (double*)*ptr + pos;
        break;

    }
}

int compare( void* elem1 , void* elem2 , size_t size){
        switch( size ){
        case INT_SIZE:
        return *(int*)elem1 - *(int*)elem2;
        case CHAR_SIZE:
        return *(char*)elem1 - *(char*)elem2;
        break;
        // case FLOAT_SIZE:
        // return *(float*)elem1 - *(float*)elem2;
        // break;
        // case LONG_SIZE:
        // return *(long*)elem1 - *(long*)elem2;
        // break;
        case DOUBLE_SIZE:
        return *(double*)elem1 - *(double*)elem2;
        break;
        default:
        printf("Baaaad\n");
        return 0;
    }
}

int partition(void* list, int left, int right, size_t size, void* pivot_ptr){

    store_pivot_data(list, right, size, &pivot_ptr); // store the pivot value to @pivot_ptr

    
    int i = left - 1;  // Index of smaller element 
    // make helper pointers
    void* jth_ptr = list; 
    void* ith_ptr = list;

    jump_ptr(&ith_ptr, size, i);


    for (int j = left; j <= right- 1; j++) { 

        jump_ptr(&jth_ptr, size, j); // iterate through the pointer

        // If current element is smaller than or 
        // equal to pivot 
        if( compare(jth_ptr, pivot_ptr, size) <= 0 ){
        
            i++;    // increment index of smaller element 
            jump_ptr(&ith_ptr, size, i); // set the ith pointer
            swap( ith_ptr , jth_ptr, size ); // swap i and j pointers
        } 

        // reset the jth_ptr and ith_ptr for the next call to jump_ptr
        jth_ptr = list; 
        ith_ptr = list;
    } 

    jump_ptr(&ith_ptr, size, i+1);
    jump_ptr(&jth_ptr, size, right);
    swap( ith_ptr, jth_ptr , size); // swap @ith_ptr's value with @jth_ptr's value

    return (i + 1); 

}

void quicksort(void* list, int left, int right, size_t size, void* pivot_ptr){

    if( left >= right ){
        return;
    }

    int index = partition(list, left, right, size, pivot_ptr);

    quicksort(list, left,  index - 1, size, pivot_ptr );
    quicksort(list, index + 1, right, size, pivot_ptr );

}

//  ====================================================================================
//                                Library Functions:
//  ====================================================================================


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
    } // invalid arguments

    for( int* ptr = numlist; *ptr; ptr++){
        (func)(ptr);
    } // loop through and call @func on each element

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
    } // loop though and call @func

    return SUCCESS;

}




int sort(void* list, size_t length, size_t size){
    /*
     * sort - sort an array of elements
     * @list - a pointer to the list of elements
     * @length - the number of elements in @list
     * @size - the size of an element of @list
     * 
     * Sort the list using quicksort algorithm.
     * 
     * return -1 if invalid input, 0 otherwise
     */

    if( list == NULL ){
        return ERROR;
    } // invalid input

    void* pivot_ptr = malloc( size ); // create space for the pivot pointer

    if( pivot_ptr == NULL ){
        return ERROR;
    } // no more memory

    quicksort(list, 0, length - 1, size, pivot_ptr); // use the quicksort algorithm

    free( pivot_ptr ); // free the pivot_ptr
    
    return 0;
}