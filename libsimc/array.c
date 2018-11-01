#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "array.h"

#define ERROR -1
#define SUCCESS 0

#define INT_SIZE sizeof( int )
#define CHAR_SIZE sizeof( char )


struct Array{
    void* data;
    unsigned int length;
    unsigned int data_size;
    unsigned int total_memory;
};


//  ====================================================================================
//                                Helper Functions:
//  ====================================================================================


void increment_ptr( void** ptr, unsigned int size){
    switch(size){
        case INT_SIZE:
        *ptr = (int*)*ptr + 1;
        break;
        case CHAR_SIZE:
        *ptr = (char*)*ptr + 1;
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
    }
}

void convert(void* address, void* data, unsigned int size, unsigned int length ){
    for(int i = 0 ; i < length ; i++ ){
        switch(size){
            case INT_SIZE:
            ((int*)address)[i] = ((int*)data)[i];
            break;
            case CHAR_SIZE:
            ((char*)address)[i] = ((char*)data)[i];
            break;
        }
    }
}

void update_data(void* address_to_update, void* ptr_to_new_data, unsigned int size_of_data){
    switch(size_of_data){
        case CHAR_SIZE:
        *(char*)address_to_update = *(char*)ptr_to_new_data;
        break;
        case INT_SIZE:
        *(int*)address_to_update = *(int*)ptr_to_new_data;
        break;
    }
}







//  ====================================================================================
//                                Library Functions:
//  ====================================================================================

array_t array_create(void* data, unsigned int length, unsigned int data_size, int fflag){
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

    array_t new  = (array_t)malloc(sizeof(array_t));
    if( new == NULL){
        puts("UUUH OHHH");
        return NULL;
    }
    new->length = length;
    new->data_size = data_size;
    if(data == NULL ){
        new->data = NULL; // no data specified
    }
    else{
        new->data = malloc(length * data_size);
        if(new->data == NULL){
            return NULL;
        }
        convert(new->data, data, data_size, length);
        if( fflag ){
            free(data);
        }
        //free(data);

        //new->data = data;
    }
    new->total_memory = length * data_size;

    return new;
        
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

            // case sizeof(char)*10:
            // printf("%s", (char*)ptr );
            // ptr = (char*)ptr + 1 ;
            // break;
                
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
    printf(" total memory: %d, length: %d, data size: %d", array->total_memory, array->length, array->data_size);
    puts("");
    
}


void* array_get(array_t array, unsigned int index){
    /*
     * array_get - get the value at an index
     * @array - the array
     * @index - the index where the value is stored
     * 
     * Iterates through @array until it reaches the index
     * 
     *  return: a pointer to the data, or NULL if unable to get
     */


    if ( array == NULL || array->length < index ){
        return NULL;
    } // check for a valid index

    void* rt_ptr = array->data;
    unsigned int size = array->data_size;

    jump_ptr(&rt_ptr, size, index);
    
    // for( int i = 0 ; i < index ; i++){
    //     increment_ptr(&rt_ptr, size);
    // } // increment the rt_ptr until it gets to the correct address

    return rt_ptr;
}

void* array_get_new(array_t array, unsigned int index){
    /*
     * array_get_new - get the value at an index and copy it into new memory
     * @array: array data structure
     * @index: the index where the data wanted is stored
     * 
     * Jump to the place in memory where index is stored and
     * copy data at that memory location to a new place in memory.
     * 
     * return: a pointer to the new copy of the data, else, NULL
     */



    if( array == NULL || array->length < index ){
        return NULL;
    }

    void* data = array->data;
    void* dest_ptr = malloc((size_t)array->data_size);

    jump_ptr(&data, array->data_size, index);

    return memcpy(dest_ptr, data, (size_t)array->data_size);

}



int array_append(array_t array, void* data){
    /* 
     * array_append - append to the end of an array
     * @array: the array to append to
     * @data: the new data to be stored
     * 
     * make space for the new data then insert it at the address
     * 
     * return: -1 if there and is error, otherwise, 0
     */
    

  //  if( (array->data_size * (array->length + 1) ) > array->total_memory  ){
        // realloc the memory to make space for another item of data
   //     printf("--I have to remalloc!--\n");
        array->data = realloc( array->data, (array->data_size * (array->length + 1 )) );
        array->total_memory += array->data_size; // update to total memory space
  //  }

    // confirm no errors occurred
    if( array->data == NULL){
        perror("Error in array_append()");
        return ERROR;
    }

    // point to the new address and update what is stored there
    // length refers to the last index here because it hasn't been updated yet
    update_data( array_get(array, array->length), data, array->data_size ); // update what's at ptr's address with whats at data's address
    
    array->length++; // now length is properly updated


    return SUCCESS;

}

int array_insert(array_t array, unsigned int index, void* data){
/*
 * array_insert - insert data into the array
 * @array: array data structure
 * @index: index of location for new data
 * 
 * Shift memory and data, then save @data to its new place in memory.
 * 
 */

    if(array == NULL || data == NULL || array->length < index ){
        return ERROR;
    }

   // if( (array->data_size * (array->length + 1) ) > array->total_memory  ){
        // realloc the memory to make space for another item of data
     //   printf("--I have to remalloc!--\n");
        array->data = realloc( array->data, (array->data_size * (array->length + 1 )) );
        array->total_memory += array->data_size; // update to total memory space
  //  }


    for(int i = array->length - 1 ; i >= index ; i-- ){
        update_data( array_get(array, i+1)  , array_get(array, i) , array->data_size );
    }
    update_data( array_get(array, index)  , data , array->data_size );

    array->length++;

    return SUCCESS;

}

int array_remove(array_t array, unsigned int index, void** data){ 
    /*
     * array_remove - remove data from an array and store it elsewhere
     * @array: array data structure
     * @index: position of data to remove
     * @data: address of a pointer to store the removed data (can be null)
     * 
     * if @data is not null, save the value (from a different address) to @data. Next,
     * update the array to reflect the changed value locations and reduce the memory
     * so there is no waste. 
     * 
     * WARNING: this function mallocs space with array_get_new() so free your pointer
     *          when/if you are done with it.
     * 
     * return: 0 if successful, -1 otherwise
     */


    if(array == NULL || index >= array->length){
        return ERROR;
    }

    if( data != NULL ){
        *data = array_get_new(array, index); // exactly like get but malloc new space and returna pointer to it
    }

    int len = array->length;
    for(int i = index + 1 ; i < len ; i++){
        update_data( array_get(array, i-1), array_get(array, i), array->data_size );
    }

    array->data = realloc( array->data, (array->data_size * (array->length - 1 )) );
    array->total_memory -= array->data_size; // update to total memory space
    array->length--;

    return SUCCESS;
}

int array_pop(array_t array, void** data){
    /*
     * array_pop - remove the last element and store it
     * @array: array data structure
     * @data: a pointer to the address of where to store the value
     * 
     * If @data is not null, save the data value (with a different address) to @data.
     * realloc space for the data in @array and update member variable.
     * 
     * WARNING: this function mallocs space with array_get_new() so free your pointer
     *          when/if you are done with it.
     * 
     * return: 0 if successful, -1 otherwise
     */
    
    if( array == NULL ){
        return ERROR;
    }

    if(data != NULL){
        *data = array_get_new(array, array->length - 1);
    }

    array->data = realloc( array->data, (array->data_size * (array->length - 1 )) );
    array->total_memory -= array->data_size; // update to total memory space
    array->length--;

    return SUCCESS;


}

void* array_get_head( array_t array ){
    /*
     * array_get_head - get the head of data
     * @array: array data structure
     * 
     * check for valid input first.
     * 
     * return: the data head of @array, or NULL
     */
    if( array == NULL ){
        return NULL;
    }

    return array->data;
}

array_t array_overwrite_data( array_t array, void* data, unsigned int length, unsigned int data_size, int fflag ){
    /*
     * array_overwrite_data - completely overwrite the array
     * 
     * free the data @array points to. update the member variables and if
     * the fflag is set, free the data
     * 
     * FIXME: THIS FUNCTION IS INCORRECT WILL FIX LATER ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
     *        IF fflag IS SET, WE'D BE FREEING THE DATA WE WANNA KEEP
     */
    if(array == NULL){
        return NULL;
    }

    free(array->data);

    array->data = data;
    array->length = length;
    array->data_size = data_size;
    array->total_memory = length* data_size;

    if( fflag ){
        free(data);
    }

    return array;
    
}



/* Up Next:
 * 
 * 
 * array_combine() "a1 + a2"
 * array_map()
 * 
 * array_get_next() // given a pointer to a data item, set that pointer to the next one
 * 
 * 
 */