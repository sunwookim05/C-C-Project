#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
	int a,b,c,d,i,j,h;
	char aa,ba,ca,da;
	
	while(1){	
		while(1){	
	
			printf("ù ��° ���ڸ� �Է��� �ּ��� : ");
			scanf("%c",&aa);
			printf("�� ��° ���ڸ� �Է��� �ּ��� : ");
			getchar();
			scanf("%c",&ba);
		
			a=aa;
			b=ba;
			i=a+5;
			j=0;
		 
			if(i>=b){
				printf("�ٽ� �Է��� �ּ���. \n");
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
		
		printf("\n �ٽ��Ͻðڽ��ϱ�? (y/n) ");
		getchar();
		scanf("%c",&aa);
		getchar();
		
		if(aa=='n'){
			printf("�����մϴ�.");
			break;
		}
		
	}
	
	return 0;
}
