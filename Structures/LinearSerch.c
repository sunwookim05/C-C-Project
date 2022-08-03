#include <stdio.h>

int LSerch(int ar[], int len, int target){
    for(int i = 0; i < len; i++){
        if(ar[i] == target)
            return i;
    }
}

int main(void){
    int arr[] = {3, 5, 2, 4, 9};
    int idx;

    idx = LSerch(arr, sizeof(arr)/sizeof(int), 4);

    if(idx == sizeof(arr)/sizeof(int))
        printf("serch fail\n");
    else
        printf("target index: %d \n", idx);

    idx = LSerch(arr, sizeof(arr)/sizeof(int), 7);

    if(idx == sizeof(arr)/sizeof(int))
        printf("serch fail\n");
    else
        printf("target index: %d \n", idx);

    return 0;
}