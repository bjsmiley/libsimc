#include <stdio.h>
#include <stdlib.h>
#include <array.h>
#include <assert.h>

void test_inc(array_t ar1 , array_t ar2){
    for(int i = 0 ; i < 5 ; i++){
        printf("%d,", *(int*)array_get(ar1, i));
    }
}

int main(int argc, char const *argv[])
{
    /* code */
    int* data = malloc(sizeof(int)*5);
    data[0] = 6;
    data[1] = 3;
    data[2] = 8;
    data[3] = 10;
    data[4] = 4;

    array_t array = array_create(data, 5, sizeof(int), 1);
    assert(array != NULL);
    assert(array_delete(array) == -1);
    array_print(array);

    int data2[5] = {3,5,2,1,7};
    array_t array2 = array_create(data2, 5, sizeof(int), 0);
    assert(array2 != NULL);
    assert(array_delete(array2) == -1);
    array_print(array2);



    char data4[] = "hello";//{'a','b','b','z','s'};
    array_t array4 = array_create(data4, 5, sizeof(char), 0);
    assert(array4 != NULL);
    assert(array_delete(array4) == -1);
    array_print(array4);

    //test_inc(array, array2);
 

    int num = 55;
    int num2 = 44;
    int insNum = 99;
    char char1 = 'z';
    array_append(array, &num);
    array_print(array);

    array_append(array4, &char1);
    array_print(array4);

    array_append(array2, &num2);
    array_print(array2);
    puts("=============================");
    array_insert(array, 2, &insNum, 0);
    array_print(array);

    array_insert(array4, 4, &char1, 0);
    array_print(array4);

    assert( array_insert(array2, 6, &insNum, 0) == 0 );
    array_print(array2);
    //array_delete()
    puts("============ REMOVE: =================");
    array_remove(array, 1, NULL);
    array_print(array);
    int* got;
    array_remove(array, 4, (void**)&got);
    array_print(array);
    printf("got: %d\n", *got);
    free(got);

    puts("============ REMOVE: =================");
    char* whatChar;
    array_print(array4);
    array_pop(array4, (void**)&whatChar);
    printf("\n%c\n", *whatChar);
    array_remove(array4,0,(void**)&whatChar);
    printf("\n%c\n", *whatChar);
    array_print(array4);
    whatChar = NULL;
    whatChar = array_get_head(array4);
    printf("\nhead: %c\n", *whatChar);
    whatChar = NULL;
    whatChar = array_get_new(array4,0); // cant do the test without and insert that wont move the values over


    return 0;
}
