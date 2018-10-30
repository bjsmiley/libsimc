#include <stdio.h>
#include <stdlib.h>
#include <functions.h>

void inc( int* n){
    *n = *n + 1;
}

void print(int* n){
    printf("%d\n", *n);
}

void sum(int* result, int n){
    *result += n;
}

void getlastt(int* result, int elem ){
*result = elem;
}

int main(int argc, char const *argv[])
{
    int* list = malloc(12 * sizeof(int));
    for( int i = 0 ; i < 12 ; i++ ){
        list[i] = i+5;
    }
    map(list, inc);

    map(list, print);
    puts("");

    // map(list, inc);

    // map(list, print);
    int data;
    reduce(list, sum, &data);
    printf("data: %d\n", data);
    // map(list, print);

    // printf("length: %d\n", length(list));

    // for( int i = 0 ; i < 4 ; i++ ){
    //     list[i] = 10-i;
    // }    
    // map(list, print);
    // sort(list);
    // puts("sorted:");
    // map(list, print);

    // puts("sorted2:");
    // int arr[10] = {4,8,2,-1,10,8,3,9,7,1};
    // int* list2 = malloc(10*sizeof(int));
    // for( int i = 0; i < 10; i++){
    //     list2[i] = arr[i];
    // }
    // sort(list2);
    // map(list2, print);
    
    // puts("convert:");
    // int arr[10] = {4,8,2,-1,10,8,3,9,7,1};
    // int* ptr;
    // create_pointer(&ptr, arr, 10);
    // map(ptr, print);
    // // printf("length: %d\n", length(arr));
    // // sort(arr);
    // // map(arr, print);




    return 0;
}
