# libsimc
Simple C Library - inspired by SGLIB and STL

# Goals
* To implement my own __limited__ version of the C++ STL, as well as, any other algorithms, data structures or functions for C.
* Make The library easy to use, robust, and safe.

# Files
## <functions.h>
### map()
Will iterate through an int array and execute a user defined function on each element.
### reduce()
Iterates through and reduces the array to a single integer using a user defined function.
### filter()
**_WILL BE IMPLEMENTED..._**

## <array.h>
### array_create()
Creates an array data structure for the user.
### array_delete()
Deallocates the array.
### array_length()
Gets the length of an array.
### array_print()
Will print an array in a clean fashion. (Mostly for debugging)
### array_get()
Given an index, will return a pointer to the data stored there.
### array_append()
Appends data to the end of an array, and realloc's memory before.

(quicksort, hashtable, ~~sorted~~?? array coming soon..)
