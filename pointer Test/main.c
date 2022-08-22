#include "main.h"

void swap(short a, int *b){
    int* c = b;
    *(short*)&c = a;
}

int main(void){

}