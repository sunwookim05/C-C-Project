#include <stdio.h>
#include <stdlib.h>

int main(void){

    int a, r = 0;

    printf("a를 입력하세요 : ");
    scanf_s("%d", &a);
    while (a) {
        r = (r * 10) + (a % 10);
        a = a / 10;
    }

    printf("a를 뒤집으면 %d 입니다.", r);
    return 0;
}
