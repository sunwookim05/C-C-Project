#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
	
	int a,b,c,i,j,r;
	char aa;
	
	while(1) {
	
		printf("단을 입력해 주세요 : ");
		scanf("%d",&a);
	
		for(i=1; i<=9; i++){
			r=a*i;
			printf("%d * %d = %d \n",a,i,r);
		}
	
		printf("다시하시겠습니까? (y/n) ");
		getchar();
		scanf("%c",&aa);
		
		if(aa=='n'){
			printf("종료합니다.");
			break;
		}
	}
	return 0;
}
