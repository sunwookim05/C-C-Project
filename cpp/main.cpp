#include <iostream>
#include <stdio.h>
int main(void){
    int num = 1;
    int *pnum;

    pnum = &num;

    printf("%d %d\n",num, pnum);
    
    *pnum = 2;

    printf("%d %d\n",num, pnum);

    printf("%d %d\n",num, *pnum);

    printf("%d %d\n",num, &pnum);

    return 0;
}