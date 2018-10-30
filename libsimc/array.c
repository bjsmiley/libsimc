#include <stdlib.h>
#include <stdio.h>
#include "array.h"

#define ERROR -1
#define SUCCESS 0


struct Array{
    void* data;
    unsigned int length;
    unsigned int data_size;
};

array_t array_create(void* data, unsigned int length, unsigned int data_size){
    /*
     *  array_create - creates an array_t datatype
     *  @data: a pointer to that data that will be manipulated
     *  @length: the number of elements alreadt in an array
     *  @data_size: the size of data stored in this array (ex: sizeof(int))
     * 
     *  malloc space for a new array_t and correctly passes new values
     *  into the struct depending on what the user passes into the function
     * 
     *  returns: a typedef pointer to thr Array struct, or NULL if invalid input
     */

    if( length < 0 && data_size < 0 ){
        return NULL;
    } // invalid input

    if(data == NULL ){
        array_t new  = (array_t)malloc(sizeof(array_t));
        new->data = NULL; // no data specified
        new->length = length;
        new->data_size = data_size;
        return new;
    } // no data has been passed in yet
    else{
        array_t new  = (array_t)malloc(sizeof(array_t));
        new->data = data;
        new->length = length;
        new->data_size = data_size;
        return new;
    } // initialize the entire struct
}

int array_delete(array_t array){
    /*
     * array_delete - Deallocate a given array
     * @array: the array to delete
     * 
     * free's the array if it is empty
     * 
     * returns: 1 if successful, 0 otherwise
     */

    if(array == NULL || array_length(array) > 0){
        return ERROR;
    } // invalid or still storing data

    free(array);
    return SUCCESS;
}

int array_length(array_t array){
    /*
     * array_length - get the length of a given array
     * @array: the array to get the length from
     * 
     * return the length of the array
     */

    if( array == NULL){
        return ERROR;
    }
    return array->length;
}

void array_print(array_t array){
    /*
     * array_print - print the array
     * @array: the array to print
     * 
     * iterate through the array and cast the data, then print
     * 
     * return: Void 
     */
    if( array == NULL){
        return;
    }
    void* ptr = array->data;
    for( int i = 0 ; i < array->length ; i ++ ){
        printf("[");
        switch(array->data_size){
            case sizeof(char):
            printf("%c", *(char*)ptr );
            ptr = (char*)ptr + 1 ;
            break;

            case sizeof(char)*10:
            printf("%s", (char*)ptr );
            ptr = (char*)ptr + 1 ;
            break;
                
            case sizeof(int):
            printf("%d", *(int*)ptr );
            ptr = (int*)ptr + 1 ;
            break;

            case sizeof(array_t):
            array_print( (array_t)ptr );
            ptr = (array_t*)ptr + 1 ;
            break;

            default:
            printf("BAD");

        }
        printf("]");

    }
    puts("");
    
}