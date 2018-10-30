#ifndef _ARRAY_H
#define _ARRAY_H
/*
 * 
 */
typedef struct Array* array_t;

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
array_t array_create(void* data, unsigned int length, unsigned int data_size);

/*
* array_delete - Deallocate a given array
* @array: the array to delete
* 
* free's the array if it is empty
* 
* returns: 1 if successful, 0 otherwise
*/
int array_delete(array_t array);

/*
* array_length - get the length of a given array
* @array: the array to get the length from
* 
* return the length of the array
*/
int array_length(array_t array);

/*
* array_print - print the array
* @array: the array to print
* 
* iterate through the array and cast the data, then print
* 
* return: Void 
*/
void array_print(array_t array);

#endif 