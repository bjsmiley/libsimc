#include <stdio.h>
#include <stdlib.h>
#include <array.h>
#include <assert.h>

static int inc_item(void *data, void *arg)
{
    int *a = (int*)data;
    int inc = (int)(long)arg;

    *a += inc;

    return 0;
}

int main(int argc, char const *argv[])
{
    /* code */
  

    int array[] = {40, 6, 0, 88};
    array_t r = array_create(array, 4, sizeof(int), 0);

    array_print( r );
    array_iterate( r , inc_item , (void*)4 , NULL);
    array_print( r );

      return 0;
}
