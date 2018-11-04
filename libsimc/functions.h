#ifndef _FUNCTIONS_H
#define _FUNCTIONS_H

/*
 * func_map_t - map callback function type
 * @elem_ptr: a pointer to a single element
 */
typedef void (*func_map_t)(int* elem_ptr);

/*
 * func_reduce_t - reduce callback function type
 * @result: the final value to be 'returned' from reduce() 
 * @elem: the value of a single element
 */
typedef void (*func_reduce_t)(int* result, int elem);


/*
 * map - map function to each element
 * @numlist: the integer array to iterate through
 * @func: the function to call on each element
 * 
 * Iterate through the numbers and call @func on each one.
 * 
 * Return: -1 if there are NULL arguments, 0 otherwise.
 */
int map(int* numlist, func_map_t func);

/*
 * reduce - reduce the array to a single result
 * @numlist: the integer array to iterate through
 * @func: the callback function 
 * @data: where to store the result
 * 
 * Iterate through the numbers and call @func on each one.
 * 
 * Return: -1 if there are NULL arguments, 0 otherwise.
 */
int reduce(int* numlist, func_reduce_t func, int* data);

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
int sort(void* list, size_t length, size_t size);


#endif
