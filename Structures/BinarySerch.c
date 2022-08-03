#include <stdio.h>

int BSerch(int ar[], int len, int target){ // binary search function
    int first = 0;
    int last = len - 1;
    int mid;

    while(first <= last){
        mid = (first + last) / 2;
        if(target == ar[mid]){
            return mid;
        }else {
            if(target < ar[mid])
                last = mid - 1;
            else
                first = mid + 1;
        }
    }
    return -1;
}

int main(void){
    int arr[] = {1, 3, 5, 7, 9}; // search target
    int idx;

    idx = BSerch(arr, sizeof(arr)/sizeof(int), 7); // search index

    if(idx == -1)
        printf("serch fail\n"); // fail
    else
        printf("target index: %d \n", idx); // success

    idx = BSerch(arr, sizeof(arr)/sizeof(int), 4); // search index

    if(idx == -1)
        printf("serch fail\n"); // fail
    else
        printf("target index: %d \n", idx); // success

    return 0;
}  