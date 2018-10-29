#ifndef _FUNCTIONS_H
#define _FUNCTIONS_H

/*
 * func_t - 
 */
typedef void (*func_map_t)(int* elem_ptr);
typedef void (*func_reduce_t)(int* result, int elem);

int map(int* numlist, func_map_t func);

int reduce(int* numlist, func_reduce_t func, int* data);

int length(int* numlist);

#endif
