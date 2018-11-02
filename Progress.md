# Libsimc Progress Journal

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