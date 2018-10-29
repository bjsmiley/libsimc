#include <stdio.h>
#include <stdlib.h>
#include <functions.h>

void inc( int* n){
    *n = *n + 1;
}

void print(int* n){
    printf("%d\n", *n);
}

int main(int argc, char const *argv[])
{
    int* list = malloc(4 * sizeof(int));
    for( int i = 0 ; i < 4 ; i++ ){
        list[i] = i+1;
    }
    map(list, inc);

    map(list, print);

    map(list, inc);

    map(list, print);

    return 0;
}
