#include <stdio.h>

typedef unsigned char* String;

int main(void){
    String str[2];

    str[0] = "1324567";
    str[1] = "ASDFGSD";

    printf("%s %s",str[1], str[0]);

    str[0] = "ASDFGSD";
    str[1] = "ASDFGSD";

    printf("\n%s %s",str[1], str[0]);

    return 0;
} 