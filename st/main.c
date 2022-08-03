#include <stdio.h>

typedef struct _a
{
    int a;
    int b;
} a;

a aa[2];

int main(void){
    aa[0].a = 1;
    aa[0].b = 2;

    aa[1] = aa[0];

    printf("%d %d \n%d %d", aa[0].a, aa[0].b, aa[1].a, aa[1].b);
}