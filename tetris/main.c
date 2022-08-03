#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <conio.h>
#include "font.h"

#define START_POSx 3
#define START_POSy 5
#define RED 4
#define YELLOW 6
#define BLACK 0
#define BLUE 1
#define GREEN 2
#define WHITE 15
#define GRAY 8
#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77
#define CHANGE_COLOR(X) (SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (X)))

typedef struct _random {
    int posX;
    int posY;
} random;

typedef struct _line_data {
    int floor;
    int right;
    int left;
    char pos[10];
} line_data;

random rnd[6];

unsigned char ui[20][10] = {0, };
int change_stat = 0;
int last;
int tim;
int pos;
int down_Force;

void gotoxy(int x, int y){
    COORD Pos;
    Pos.X = x;
    Pos.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

void CursorView()
{
    CONSOLE_CURSOR_INFO cursorInfo = { 0, };
    cursorInfo.dwSize = 1;
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
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
        gotoxy(START_POSx, START_POSy + i);
        clearline(i);
    }
    gotoxy(0, 0);
}

void name(){
    int color[5] = {BLUE, YELLOW, RED, GREEN, GRAY};
    static int i = 0;
    gotoxy(27, 0);
    CHANGE_COLOR(color[i % 5]);
    printf("T");
    CHANGE_COLOR(color[(i + 1) % 5]);
    printf("E");
    CHANGE_COLOR(color[i % 5]);
    printf("T");
    CHANGE_COLOR(color[(i + 2) % 5]);
    printf("R");
    CHANGE_COLOR(color[(i + 3) % 5]);
    printf("I");
    CHANGE_COLOR(color[(i + 4) % 5]);
    printf("S");
    CHANGE_COLOR(WHITE);
    gotoxy(0, 0);

    i += 1;
}

void menu(){
    system(" mode  con lines=30  cols=60 ");
    CHANGE_COLOR(YELLOW);
    gotoxy(1, 3);
    printf("1. Play game");
    gotoxy(1, 4);
    printf("2. EXIT");
    gotoxy(0, 0);
    CHANGE_COLOR(WHITE);
}

void update(){
    
}

void downupdate(){
    
}

void block(){
    
}

void change(){
    if(change_stat > 3) change_stat = 0;

    gotoxy(0, 1);
    printf("%d %10d %10d",change_stat, pos, down_Force);
}

void loop(){
    int data = 0;
    clock_t sclock1, nclock1, sc, nc;
    system("cls");
    name();
    sclock1 = clock();
    sc = clock();
    gotoxy(START_POSx, START_POSy);
    clearAll();

    while(1){
        if(kbhit()){
            data = getch();
        }
        nclock1 = clock();
        nc = clock();
        if (nclock1 - sclock1 >= CLOCKS_PER_SEC){
            down_Force += 1;
            sclock1 = clock();
            change();
        }
        if(nc - sc >= (CLOCKS_PER_SEC / 10)){
            name();
            sc = clock();
        }
        if(down_Force > 0){
            down_Force--;
            downupdate();
            change();
        }
        switch (data){
        case UP: change_stat += 1; change(); break;
        case DOWN: down_Force += 1; change(); break;
        case RIGHT: pos += 1; change(); break;
        case LEFT: pos -= 1; change(); break;
        }
        gotoxy(0, 30);
        data = 0;
    }
}

int main(void){
    int data = 0;
    clock_t sc, nc;
    sc = clock();

    CursorView();
    menu();
    while(!data){
        nc = clock();
        if(nc - sc >= (CLOCKS_PER_SEC / 10)){
            name();
            sc = clock();
        }
        if(kbhit()){
            data = getch();
        }
    }

    if(data == '1') loop();
    gotoxy(0, 25);
    
    return 0;
}
