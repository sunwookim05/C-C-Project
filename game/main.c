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
    printf("1. ���Ǳ� �۵�\n2. ��� �߰�\n3. ǰ�� �߰�\n4. ǰ�� ����\n5. ������");
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