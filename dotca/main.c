#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "font.h"

#define calculate(a,b,c) ((c) == '+' ? (a + b) : (c) == '-' ? (a - b) : (c) == '*' ? (a * b) : (c) == '/' ? (a / b) : 0)

void putString(char *str, int max){
	int maxc = strlen(str);
	char c;
	for(int i = 0; i < 8; i++){
		for(int r = 0; r < max; r++){
			c = str[r] - ' ';
			for(int j = 0; j < 6; j++){
				(font[c][i][j] != 1 ? printf("□") : printf("■"));
			}
		}
		printf("\n");
	}
}

void appLoop(int *exit){
	int max1;
	double a, b, r;
	char chr, c;
	char *s1;
	char *s2;

	printf("계산하고 싶은 식을 입력하세요\n");
	scanf("%lf %c %lf",&a, &c, &b);
	getchar();
	printf("입력한 식이 %g %c %g가 맞습니까? (Y/N) ", a, c, b);
	scanf("%c", &chr);
	getchar();
	if(chr == 'N' || chr == 'N') return;
	r = calculate(a, b, c);
	sprintf(s1,"%g%c%g",a ,c, b);
	sprintf(s2,"=%g",r);
	max1 = (strlen(s1) > strlen(s2) ? strlen(s1) : strlen(s2));
	putString(s1, max1);
	putString(s2, max1);
	printf("다시 계산하시겠습니까? (Y/N) ");
	scanf("%c", &chr);
	getchar();
	if(chr == 'N' || chr == 'N') *exit = 1;
}

int main(void){
	int exit = 0;

	printf("환영합니다\n");
	while(!exit){
		appLoop(&exit);
	}
	printf("\n종료합니다.");

	return 0;
}