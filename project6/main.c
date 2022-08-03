#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

//연산
#define calculate(a, b, c)	((c) == '+' ? (a+b) :((c) == '-' ? (a-b) :(((c) == '*' ? (a*b) : (((c) == '/' ? (a/b) : (a)))))))

void keyent(){
	char c;

	c = getch();
	if(c == 13){
		keyent();
	}
}

//키 값에 따라 출력, 출력된 문자 지우기
void keyval(double a, char c){

	printf("\r");
	for(int i = 0; i <= 50; i++){
		
		printf("  ");
		
	}

	if(c == 'c' || c == 'C' || c == 27){
		printf("\r");

	}else if(c == 13){
		printf("\r%g ", a);
		keyent();

	}else {
		printf("\r%g %c ", a, c);

	}

}

int main(void){

	double a, b, r;
	char cal;

	while(1){
	
		scanf("%lf %c %lf", &a, &cal, &b);
		getchar();
		
		r = calculate(a, b, cal);
		
		printf("= %g ", r);

		while(1){
			a=r;
			r=0;
			
			cal = getch();
			keyval(a, cal);

			if(cal == 'c' || cal == 'C'){
				a = 0, b = 0, r = 0;
				break;
				
			}else if(cal == 27){
				return 0;

			}

			if(cal == 13){
				scanf("%c %lf", &cal, &b);

			}else {
				scanf("%lf", &b);

			}
			getchar();
			
			r = calculate(a, b, cal);
			
			printf("= %g",r);

		}
		
	}
	
	return 0;
	
}
