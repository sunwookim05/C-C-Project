#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <conio.h>

#define MAX 6

void gotoxy(int x, int y){
    COORD Pos;
    Pos.X = x;
    Pos.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

void loop(){
    int sec = 0, data = 0;
    clock_t sclock1, nclock1;
    sclock1 = clock();

    while(1){
        if(kbhit()){
            data = getch();
        }
        nclock1 = clock();
        if (nclock1 - sclock1 >= CLOCKS_PER_SEC){
            sec += 1;
            sclock1 = clock();
        }
    }

}

int main(void){

    loop();

    return 0;
}