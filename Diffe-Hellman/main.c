/* -------------------------------------------------------------------------------------------------- */
// Project Name: Diffe-Hellman Algorithm
// Developer: SUNWOO KIM
// date: March 29, 2022
/* -------------------------------------------------------------------------------------------------- */

#include <stdio.h>
#include "main.h"

typedef struct _Man{ 
    uint64_t first;
    uint64_t second;
    uint64_t symmetry;
}Man;

#define G 2
#define P 11

void privatekey(uint64_t *a, uint64_t *b){
    printf("Input Private Key A: ");
    scanf("%lld", a);
    getchar();
    printf("Input Private Key B: ");
    scanf("%lld", b);
    getchar();
}

uint64_t squared(uint64_t i){
    if(!i) return 1 % P;
    else return G << (i - 1) % P;
}

uint64_t hellman(uint64_t i, uint64_t j){
    uint64_t r;
    if(!i) return 1 % P;
    r = G << (i - 1);
    for(int a = 0; a < j; a++){
        r *= i;
    }
    return (r % P);
}

void replay_Request(boolean *loop){
    char a;
    printf("Would you like to do it again? (Y/N) ");
    scanf("%c", &a);
    getchar();
    if(a == 'N' || a == 'n') *loop = false;
    else *loop = true;
}

int main(void){
    boolean loop = true;
    Man a, b;

    while(loop){
        privatekey(&a.first, &b.first);
        b.second = squared(a.first);
        a.second = squared(b.first);
        a.symmetry = hellman(a.first, a.second);
        b.symmetry = hellman(b.first, b.second);
        printf("A:%lld B:%lld\n", a.symmetry, b.symmetry);
        replay_Request(&loop);
    }

    return 0;
}