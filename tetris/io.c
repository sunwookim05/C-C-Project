#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include "font.h"

void gotoxy(int x, int y){
    COORD Pos;
    Pos.X = x;
    Pos.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

int getKeys() {
	if (_kbhit()) {
		return _getch();
	}
	return -1;
}

void output(int x, int y, int shape, int count){

}

void clearline(int i){
    for(int x = 0; x < 10; x++){
        printf("бр");
    }
}

void clearAll(){
    for(int i = 0; i < 20; i++){
        clearline(i);
        printf("\n");
    }
}

