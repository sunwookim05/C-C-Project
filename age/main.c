#include <stdio.h>

int main(void){
    int value = 1, sum;

    while(value){
        scanf("%d", &value);
        sum += value;
    }

    printf("%d", sum);

    return 0;
}