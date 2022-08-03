#include <stdio.h>
#include <windows.h>
#include "font.h"

#define WHITE 15
#define CHANGE_COLOR(X) (SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (X)))

int main(void){
    for(int i = 0; i < 7; i++){
        for(int j = 0; j < 4; j++){
            for(int y = 0; y < 4; y++){
                for(int x = 0; x < 4; x++){
                    if(tetris[i][j][y][x] == 1){
                        if(i + 1 == 7) CHANGE_COLOR(8);
                        else CHANGE_COLOR(i + 1);
                        printf("бс");
                    }else {
                        CHANGE_COLOR(WHITE);
                        printf("бр");
                    }
                }
                printf("\n");
            }
            printf("\n");
        }
        printf("\n");
        printf("\n");
    }
    return 0;
}