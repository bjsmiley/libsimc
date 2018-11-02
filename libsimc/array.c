#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "array.h"

#define ERROR -1
#define SUCCESS 0

#define INT_SIZE sizeof( int )
#define CHAR_SIZE sizeof( char )

/*
 * Array - an array data structure a data struct defining a pointer to data, the size of an individual data item, and the total sum
 * @data: a pointer to the data
 * @length: the number of elements in the array
 * @data_size: the size of an indivual data item
 * @total_memory: the total memory @data takes up (@length * @data_size)
 * 
 */
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

// void convert(void* address, void* data, unsigned int size, unsigned int length ){
//     for(int i = 0 ; i < length ; i++ ){
//         switch(size){
//             case INT_SIZE:
//             ((int*)address)[i] = ((int*)data)[i];
//             break;
//             case CHAR_SIZE:
//             ((char*)address)[i] = ((char*)data)[i];
//             break;
//         }
//     }
// }

// void update_data(void* address_to_update, void* ptr_to_new_data, unsigned int size_of_data){
//     switch(size_of_data){
//         case CHAR_SIZE:
//         *(char*)address_to_update = *(char*)ptr_to_new_data;
//         break;
//         case INT_SIZE:
//         *(int*)address_to_update = *(int*)ptr_to_new_data;
//         break;
//     }
// }







//  ====================================================================================
//                                Library Functions:
//  ====================================================================================

array_t array_create(void* data, unsigned int length, unsigned int data_size, int fflag){
    /*
     *  array_create - creates an array_t datatype
     *  @data: a pointer to that data that will be manipulated
     *  @length: the number of elements alreadt in an array
     *  @data_size: the size of data stored in this array (ex: sizeof(int))
     *  @fflag: (free flag) if set, will free what is located at @data
     * 
     *  malloc space for a new array_t and correctly passes new values
     *  into the struct depending on what the user passes into the function
     * 
     *  returns: a typedef pointer to thr Array struct, or NULL if invalid input
     */

    if( length < 0 && data_size < 0 ){
        return NULL;
    } // invalid input

    array_t new  = (array_t)malloc(sizeof(array_t)); // create a new array

    if( new == NULL){
        return NULL;
    } // no more memory

    // set the length, data_size & total memory of this array
    new->length = length; 
    new->data_size = data_size;
    new->total_memory = length * data_size;

    if(data == NULL ){
        new->data = NULL; // no data has been specified
        new->length = 0; // set length to zero incase @length is greater than 0
        new->total_memory = 0; // update total memory
    }
    else{
        new->data = malloc(length * data_size); // create space for @data in the array
        if(new->data == NULL){
            return NULL;
        } // no more memory
        
        //convert(new->data, data, data_size, length); // copy everything @data is pointing to, into the newly malloced memory space
                                                     // TODO: TEST IF MEMCPY WILL WORK THE SAME
        memcpy(new->data, data, new->length * data_size);

        if( fflag ){
            free(data); // if fflag is set, free what @data points to
        }
    }

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


    if ( array == NULL || array->length < index || array->data == NULL){
        return NULL;
    } // check for a valid index

    void* rt_ptr = array->data; // make a new pointer, pointing to @data

    jump_ptr(&rt_ptr, array->data_size, index); // jump to that index in the array and save the pointer to @rt_ptr
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



    if( array == NULL || array->length < index || array->data == NULL ){
        return NULL;
    } // confirm input

    void* data = array->data; // create a temp pointer for the data

    void* dest_ptr = malloc((size_t)array->data_size); // create new memory for the copy
    if( dest_ptr == NULL ){
        return NULL;
    } // no more memory

    jump_ptr(&data, array->data_size, index); // @data will now point to data at @index in the array

    return memcpy(dest_ptr, data, (size_t)array->data_size); // copy @data_size bytes from @data to @dest_ptr & return  a pointer to dest_ptr


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

    if( array == NULL || data == NULL || array->data == NULL ){
        return ERROR;
    } // invalid input
    
    array->data = realloc( array->data, (array->data_size * (array->length + 1 )) ); // create more memory
    if( array->data == NULL){
        return ERROR;
    } // no more memory

    array->total_memory += array->data_size; // update to total memory space

    // point to the new address and update what is stored there
    // length refers to the last index here because it hasn't been updated yet
    // TODO: TEST IF MEMCPY WILL WORK THE SAME
    //update_data( array_get(array, array->length), data, array->data_size ); // update what's at ptr's address with whats at data's address
    memcpy( array_get(array, array->length) , data , array->data_size );
    array->length++; // now length is properly updated


    return SUCCESS;

}

int array_insert(array_t array, unsigned int index, void* data, int wflag){
/*
 * array_insert - insert data into the array
 * @array: array data structure
 * @index: index of location for new data
 * @wflag: write over a value instead of adding memory
 * 
 * Shift memory and data if @wflag is not set, then save @data to its new place in memory.
 * 
 */

    if(array == NULL || data == NULL || array->length < index ){
        return ERROR;
    } // invalid input

    if( wflag ){
        memcpy( array_get(array, index)  , data , array->data_size );
        return SUCCESS;
    }

    array->data = realloc( array->data, (array->data_size * (array->length + 1 )) );
    array->total_memory += array->data_size; // update the total memory space


    // shift each element over before inserting @data at @index in the array
    for(int i = array->length - 1 ; i >= index ; i-- ){
        //update_data( array_get(array, i+1)  , array_get(array, i) , array->data_size ); //TODO: See if memcpy will work here
        memcpy( array_get(array, i+1)  , array_get(array, i) , array->data_size );
    } 
    //update_data( array_get(array, index)  , data , array->data_size ); // insert data into the array at position @index
    memcpy( array_get(array, index)  , data , array->data_size );

    array->length++; // increment the length

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
    } // invalid input

    if( data != NULL ){
        *data = array_get_new(array, index); // exactly like array_get() but malloc new space and return a pointer to it
    } // set the extraced value to what *data points to

    int len = array->length;
    for(int i = index + 1 ; i < len ; i++){
        //update_data( array_get(array, i-1), array_get(array, i), array->data_size ); // shift all the elements correctly
        memcpy( array_get(array, i-1), array_get(array, i), array->data_size );
    }

    array->data = realloc( array->data, (array->data_size * (array->length - 1 )) ); // take off extra space from the end
    array->total_memory -= array->data_size; // update to total memory space
    array->length--; // update length

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
    
    if( array == NULL || array->data == NULL || array->length == 0){
        return ERROR;
    } // invalid input

    if(data != NULL){
        *data = array_get_new(array, array->length - 1); // get a copy of data at index (length-1)
    } // if the user wants to save the data being removed, it will be stored at *data

    array->data = realloc( array->data, (array->data_size * (array->length - 1 )) ); // update memory
    array->total_memory -= array->data_size; // update to total memory space
    array->length--; // decrement length

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
    } // invalid input

    return array_get(array, 0); // return the head of @array
}

// array_t array_overwrite_data( array_t array, void* data, unsigned int length, unsigned int data_size, int fflag ){
//     /*
//      * array_overwrite_data - completely overwrite the array
//      * 
//      * free the data @array points to. update the member variables and if
//      * the fflag is set, free the data
//      * 
//      * FIXME: THIS FUNCTION IS INCORRECT WILL FIX LATER ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//      *        IF fflag IS SET, WE'D BE FREEING THE DATA WE WANNA KEEP
//      */
//     if(array == NULL){
//         return NULL;
//     }

//     free(array->data);

//     array->data = data;
//     array->length = length;
//     array->data_size = data_size;
//     array->total_memory = length* data_size;

//     if( fflag ){
//         free(data);
//     }

//     return array;
    
// }



/* Up Next:
 * 
 * 
 * array_combine() "a1 + a2"
 * array_map()
 * 
 * 
 * 
 * 
 */