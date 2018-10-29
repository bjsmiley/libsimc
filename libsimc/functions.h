#ifndef _FUNCTIONS_H
#define _FUNCTIONS_H

typedef void (*func_t)(int* elem_ptr);

int map(int* numlist, func_t func);

#endif
