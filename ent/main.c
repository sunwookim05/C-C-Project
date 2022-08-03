#include <stdio.h>

int fild[10][10] = {0,};

void fildRun(){
    int i, j, temp = 1;
    for(j = 1; j < 9; j++){
        for(i = temp; i < 9; i++){
            if(fild[j][i] == 0){
                fild[j][i] = 9;
            }
            if(fild[j][i + 1] == 1){
                temp = i;
                break;
            }else if(fild[j][i] == 2){
                fild[j][i] = 9;
                return;
            }
        }
        if(fild[j][i] == 2){
            fild[j][i] = 9;
            return;
        }
    }
}

int main(void){
    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++){
            scanf("%d", &fild[i][j]);
        }
    }
    fildRun();
    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++){
            printf("%d ", fild[i][j]);
        }
        printf("\n");
    }

    return 0;
}