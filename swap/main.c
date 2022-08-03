#include <stdio.h>

void swap(int *a, int *b){
    int i = *a;
    *a = *b;
    *b = i;
}

int main(void){
    int a, b;

    scanf("%d %d",&a, &b);
    swap(&a, &b);
    printf("%d %d", a, b);

    return 0;
}