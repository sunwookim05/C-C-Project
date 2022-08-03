#include <stdio.h>

#define STRC(A, B, C) A = (B+C)

typedef char* String;

int main(void){
    int i = 1;
    String str[2];

    i += 1;

    STRC(str[0], "0", i);

    printf(str[0]);

    return 0;
}