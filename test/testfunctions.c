#include <stdio.h>
#include <functions.h>

int func( void* data){
    if( *(int*)data > 50 ){
        return 1;
    }
    else{
        return 0;
    }
}
int func2( void* data){
    if( *(int*)data > 0 ){
        return 1;
    }
    else{
        return 0;
    }
}

int main(int argc, char const *argv[])
{
    /* code */
    int array[] = {4,3,7,10,99,1};
    all_of(array, 5, sizeof(int), func) ? printf("TRUTH\n") : printf("FALSE\n");
    all_of(array, 5, sizeof(int), func2) ? printf("TRUTH AGAIN\n") : printf("FALSE AGAIN\n");
    any_of(array, 5, sizeof(int), func) ? printf("TRUTH2\n") : printf("FALSE2\n");
    any_of(array, 5, sizeof(int), func2) ? printf("TRUTH AGAIN2\n") : printf("FALSE AGAIN2\n");

    int seq[5];
    int start = 30;
    iota( seq , &start , 5 ,sizeof( int ));
    for( int i = 0 ; i < 5 ; i++ ){
        printf("[%d]", seq[i]);
    }
    printf("\n");

    double seq2[5];
    double start2 = 4.079;
    iota( seq2 , &start2 , 5 ,sizeof( double ));
    for( int i = 0 ; i < 5 ; i++ ){
        printf("[%f]", seq2[i]);
    }
    printf("\n");

    return 0;
}
