#include <stdio.h>

char n[10] = " ";
char u[10] = " ";

void unit(int i, int *r){
	*r = 0;
	while(i > 9){
		*r += 1;
		i /= 10;
	}
}

void number(int i, int r){
	for(int r = 0; r < 10; r++) n[r] = 0;
	switch (i){
		case 0: if(r == 0){sprintf(n,"¿µ");}break;
		case 1:sprintf(n,"ÀÏ");break;
		case 2:sprintf(n,"ÀÌ");break;
		case 3:sprintf(n,"»ï");break;
		case 4:sprintf(n,"»ç");break;
		case 5:sprintf(n,"¿À");break;
		case 6:sprintf(n,"À°");break;
		case 7:sprintf(n,"Ä¥");break;
		case 8:sprintf(n,"ÆÈ");break;
		case 9:sprintf(n,"±¸");break;
		default:sprintf(n,"");
	}
}

void units(int i, int x, int j, int y1, int y2, int y3){
	for(int r = 0; r < 10; r++) u[r] = 0;
	switch (i){
		case 1:if(j > 0 || x == i){sprintf(u,"½Ê");}break;
		case 2:if(j > 0 || x == i){sprintf(u,"¹é");}break;
		case 3:if(j > 0 || x == i){sprintf(u,"Ãµ");}break;
		case 4:if(j > 0 || x == i || y1 > 0 || y2 > 0 || y3 > 0){sprintf(u,"¸¸");}break;
		case 5:if(j > 0 || x == i){sprintf(u,"½Ê");}break;
		case 6:if(j > 0 || x == i){sprintf(u,"¹é");}break;
		case 7:if(j > 0 || x == i){sprintf(u,"Ãµ");}break;
		case 8:if(j > 0 || x == i || y1 > 0){sprintf(u,"¾ï");}break;
		case 9:if(x == i){sprintf(u,"½Ê");}break;
		default:sprintf(u,"");
	}
}

int main(void){
	int i, r, x, y = 0;
    char str[10] = {0, };

    scanf("%s",str);
	i = atoi(str);
	unit(i, &r);
	x = r;
	for(x; x >= 0; x--){
		number(str[y] - '0', r);
		units(x, r, str[y] - '0', str[y - 1] - '0', str[y - 2] - '0', str[y - 3] - '0');
		y++;
		printf("%s%s", n, u);
	}
	return 0;
}