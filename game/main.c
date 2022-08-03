#include <stdio.h>
#include <windows.h>
#include <conio.h>

#define TRUE 1
#define FALSE 0

char workUI[20][6][20] = {
    {
        "                    "
        "                    "
        "                    "
        "                    "
        "                    "
        "                    "
    },
    {
        "                    "
        "                    "
        "                    "
        "                    "
        "                    "
        "                    "
    },
    {
        "                    "
        "                    "
        "                    "
        "                    "
        "                    "
        "                    "
    },
    {
        "                    "
        "                    "
        "                    "
        "                    "
        "                    "
        "                    "
    },
    {
        "                    "
        "                    "
        "                    "
        "                    "
        "                    "
        "                    "
    },
    {
        "                    "
        "                    "
        "                    "
        "                    "
        "                    "
        "                    "
    },
    {
        "                    "
        "                    "
        "                    "
        "                    "
        "                    "
        "                    "
    },
    {
        "                    "
        "                    "
        "                    "
        "                    "
        "                    "
        "                    "
    },
    {
        "                    "
        "                    "
        "                    "
        "                    "
        "                    "
        "                    "
    },
}

void CursorView(){
    CONSOLE_CURSOR_INFO cursorInfo = { 0, };
    cursorInfo.dwSize = 1;
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

void gotoxy(int x, int y){
    COORD Pos;
    Pos.X = x;
    Pos.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

void menu(int data){
    gotoxy(0, 0);
    printf("1. 자판기 작동\n2. 재고 추가\n3. 품목 추가\n4. 품목 제거\n5. 나가기");
}

void

int main(void){
    int data = '0';

    CursorView();
    while(data != '5'){
        if(kbhit()){
            data = getch();
        }
        switch (data){
        case '0': menu(data);
            break;
        case '1':
            break;
        case '2':
            break;
        case '3':
            break;
        case '4':
            break;
        }
    }

    return 0;
}