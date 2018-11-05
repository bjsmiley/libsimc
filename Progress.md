# Libsimc Progress Journal
## 11/4/18
Haven't been able to work on it in awhile.  
I developed a general quicksort function that takes a void pointer.  
However, it only works on ints, chars, and doubles.  
Perhaps I'll find a way soon to expand it.  
More STL general functions have been added, like, iota() and all_of().

## 11/1/18
Array now implements better memory space copying with memcpy().  
I have also done more tests for the functions I wrote yesterday.  
Perhaps I will make map/filter/reduce functions like in swift, then start moving on to expand libsimc. 
Do I need to start displaying errors and exiting instead of just returning NULL or -1? 

## 10/31/18
Just started this informal journal to record thoughts, opinions, and reflect. Hope it goes well.  
I added more functions to array.h  
More testing needs to be done for them  
including:  
* array_pop(), array_get_head(), and array_overwrite_data() and array_get_new()

Clean up code & comments   
See what can be written better then I would like to finalizing array.h for now  
idea: implement in functions.h time() passing in a func and args and it records execution time...