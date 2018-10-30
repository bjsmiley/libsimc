#include <stdio.h>
#include <stdlib.h>
#include <array.h>
#include <assert.h>

int main(int argc, char const *argv[])
{
    /* code */
    int* data = malloc(sizeof(int)*5);
    data[0] = 6;
    data[1] = 3;
    data[2] = 8;
    data[3] = 10;
    data[4] = 4;

    array_t array = array_create(data, 5, sizeof(int));
    assert(array != NULL);
    assert(array_delete(array) == -1);
    array_print(array);

    int data2[5] = {3,5,2,1,7};
    array_t array2 = array_create(data2, 5, sizeof(int));
    assert(array2 != NULL);
    assert(array_delete(array2) == -1);
    array_print(array2);

    // array_t list[2] = {array, array2};
    // array_t array3 = array_create(list, 2, sizeof(array_t));
    // assert(array3 != NULL);
    // assert(array_delete(array3) == -1);
    // array_print(array3);

    char data4[5] = {'a','b','b','z','s'};
    array_t array4 = array_create(data4, 5, sizeof(char));
    assert(array4 != NULL);
    assert(array_delete(array4) == -1);
    array_print(array4);

    return 0;
}
