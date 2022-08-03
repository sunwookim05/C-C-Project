#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>

#include "font.h"

#define pm(c) ((c) == '+' ? 10 : (c) == '-' ? 11 : (c) == '*' ? 12 : (c) == '/' ? 13 : (c) == ' ' ? 14 : 14)
#define calculate(a,b,c) ((c) == '+' ? (a + b) : (c) == '-' ? (a - b) : (c) == '*' ? (a * b) : (c) == '/' ? (a / b) : 0)

int x = 0, y = 0;

void gotoxy(int x, int y){
	COORD pos={x,y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos); 
}

void putString(char *str, int max){
	int X = x;
	int Y = y;
	for(int a = 0; a < 8; a++){
			gotoxy(x, Y);
			printf("■");
			Y += 1;
	}
	X += 2;
	Y = y;
	for(int r = 0; r < max; r++){
		char c = str[r] - ' ';
		for(int i = 0; i < 8; i++){
			gotoxy(X, Y);
			for(int j = 0; j < 6; j++){
				(font[c][i][j] == 1 ? printf("■") : printf("□"));
			}
			Y += 1;
		}
		X += 12;
		Y = y;
	}
	for(int a = 0; a < 8; a++){
		gotoxy(X, Y);
		printf("□■");
		Y += 1;
	}
}

void appLoop(int *exit){
	int max1, max2;
	double a, b, r;
	char chr, c;
	char *s1;
	char *s2;

	printf("계산하고 싶은 식을 입력하세요");
	y += 1;
	gotoxy(x, y);
	scanf("%lf %c %lf",&a, &c, &b);
	getchar();
	y += 1;
	printf("입력한 식이 %g %c %g가 맞습니까? (Y/N) ", a, c, b);
	scanf("%c", &chr);
	getchar();
	y += 1;
	if(chr == 'N' || chr == 'N') return;
	r = calculate(a, b, c);
	sprintf(s1,"%g%c%g",a ,c, b);
	sprintf(s2,"=%g",r);
	max1 = strlen(s1);
	max2 = strlen(s2);
	putString(s1, max1);
	y += 8;
	gotoxy(x, y);
	putString(s2, max2);
	y += 8;
	gotoxy(x, y);
	printf("다시 계산하시겠습니까? (Y/N) ");
	scanf("%c", &chr);
	getchar();
	if(chr == 'N' || chr == 'N') *exit = 1;
	y += 1;
}

int main(void){
	int exit = 0;

	printf("환영합니다\n");
	y += 1;
	gotoxy(x, y);
	while(!exit){
		appLoop(&exit);
	}
	printf("\n종료합니다.");

	return 0;
}