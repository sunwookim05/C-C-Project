#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
	
	int a,b,c,i,j,r;
	char aa;
	
	while(1) {
	
		printf("���� �Է��� �ּ��� : ");
		scanf("%d",&a);
	
		for(i=1; i<=9; i++){
			r=a*i;
			printf("%d * %d = %d \n",a,i,r);
		}
	
		printf("�ٽ��Ͻðڽ��ϱ�? (y/n) ");
		getchar();
		scanf("%c",&aa);
		
		if(aa=='n'){
			printf("�����մϴ�.");
			break;
		}
	}
	return 0;
}
