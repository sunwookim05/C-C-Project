#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

struct save_ca{ double a, b, result; char str[2]; char save_result[50];};

void calculate(double val1, double val2, char str[], double *save_val){
	*save_val = (str[0] == '+') ? val1 + val2 : (str[0] == '-') ? val1 - val2 : (str[0] == '*') ? val1 * val2 : (str[0] == '/') ? val1 / val2 :
				(str[0] == '%') ? (long)val1 % (long)val2 : (str[0] == '|') ? (long)val1 | (long)val2 : (str[0] == '&') ? (long)val1 & (long)val2 :
				(str[0] == '<' && str[1] == '<') ? (long)val1 << (long)val2 : (str[0] == '>' && str[1] == '>') ? (long)val1 >> (long)val2 : 
				(str[0] == '^') ? pow(val1, val2) : (long)NULL;
}

int main(void){
	int i, j;
	struct save_ca save[100];

	for(i = 0; i < 100; i++) for(j = 0; j < 50; j++) save[i].save_result[j] = 0;
	for(i = 0; i < 100; i++){
		int blank[2] = {0, }, r = 0;
		char ca[50] = "00000";
		char m[2][46] = {0, };
		scanf("%[^\n]",ca);
		getchar();
		system("cls");
		if(strcmp(ca, "00000") == 0) break;
		for(j = 0; j < 50; j++) if(ca[j] == 32){ blank[r] = j; r++; if(r > 1) break;}
		save[i].str[0] = ca[blank[0] + 1]; save[i].str[1] = ca[blank[0] + 2];
		for(j = 0; j < blank[0]; j++) m[0][j] = ca[j];
		for(j = 0; j < 50; j++) m[1][j] = ca[j + blank[1]];
		save[i].a = atof(m[0]); save[i].b = atof(m[1]);
		calculate(save[i].a, save[i].b, save[i].str, &save[i].result);
		if(save[i].str[1] != 32) sprintf(save[i].save_result,"%g %c%c %g = %g\n", save[i].a, save[i].str[0], save[i].str[1], save[i].b, save[i].result);
		else sprintf(save[i].save_result,"%g %c %g = %g\n", save[i].a, save[i].str[0], save[i].b, save[i].result);
		printf("%s",save[i].save_result);
	}
	for(i = 0; i < 100; i++) printf("%s",save[i].save_result);

	return 0; 
}