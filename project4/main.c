#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
	int a,b,c,d,i,j,h;
	char aa,ba,ca,da;
	
	while(1){	
		while(1){	
	
			printf("첫 번째 문자를 입력해 주세요 : ");
			scanf("%c",&aa);
			printf("두 번째 문자를 입력해 주세요 : ");
			getchar();
			scanf("%c",&ba);
		
			a=aa;
			b=ba;
			i=a+5;
			j=0;
		 
			if(i>=b){
				printf("다시 입력해 주세요. \n");
				getchar();
			}else{
			break;
			}
		}
	
		for(c=a+1; c<=b-1; c++){
			ca=c;
			printf("%c ",ca);
			j++;
			if(j==3){
				printf("\n");
				j=0;
			}
		}
		
		printf("\n 다시하시겠습니까? (y/n) ");
		getchar();
		scanf("%c",&aa);
		getchar();
		
		if(aa=='n'){
			printf("종료합니다.");
			break;
		}
		
	}
	
	return 0;
}
