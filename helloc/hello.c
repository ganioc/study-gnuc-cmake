#include <stdio.h>

#define SIZE 5

// local function to print out elements of an array
void print_array(int arr[], int size){
    for(int i = 0; i < size; i++){
        printf("%d\n", arr[i]);
    }
}


int main(void){
    // local int array
    int arr[SIZE] = {1, 2, 3, 4, 5};

    // print array elements one by one
    print_array(arr, SIZE);

    // change element of arr[], arr[i]*2
    for(int i = 0; i < SIZE; i++){
        arr[i] *= 2;
    }

    print_array(arr, SIZE);

    printf("Hello C\n");

    return 0;
}