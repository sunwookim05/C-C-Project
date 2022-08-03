#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "main.h"

typedef struct _Student{
    struct _Info{
        String adress, name, birth;
        uint8_t age;
        struct _Grade{
            uint8_t grade, class, number;
        }Grade;
    }Info;
    struct __Grade{
        struct _Test{
            uint8_t kor, math, social, science, eng;
        }Test;
        struct _DoTest{
            uint8_t kor, math, social, science, eng;
        }DoTest;
    }Grade;
}Student;
 
#define CHANGE_COLOR(X) (SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (X)))
void gotoxy(int x, int y){
    COORD Pos;
    Pos.X = x;
    Pos.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

void appLoop(Student *std){
    Student student;

}

void setUp(Student *std){
    for(uint16_t i = 0; i < 300; i++){
        std[i].Info.adress = malloc(sizeof(char) * 20);
        std[i].Info.name = malloc(sizeof(char) * 10);
        std[i].Info.birth = malloc(sizeof(char) * 8);
    } 
    CHANGE_COLOR(5);
    SetConsoleTitle("학생부 관리 프로그램");
    system("mode con cols=80 lines=60");
    gotoxy(28, 30);
    printf("학생수 최대 300명까지 가능");
    gotoxy(0, 0);
}

int main(void){
    Student std[300];
    boolean loop = true;
    
    setUp(std);
    scanf("%s %s %s", std[0].Info.name, std[0].Info.adress, std[0].Info.birth);
    while(loop){
        appLoop(std);
    }

    return 0;
}