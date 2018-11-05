#include <stdio.h>
#include <functions.h>

int main(int argc, char const *argv[])
{
    /* code */
    int array[] = {8,4,1,9,3};
    char charArray[] = "bzqpa";

    sort(array, 5, sizeof(int));
    for( int i = 0 ; i < 5 ; i++ ){
        printf("[%d]", array[i]);
    }
    printf("\n");

    sort(charArray, 5, sizeof(char));
    for( int i = 0 ; i < 5 ; i++ ){
        printf("[%c]", charArray[i]);
    }
    printf("\n");



    return 0;
}
