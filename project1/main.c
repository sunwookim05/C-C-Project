#include <stdio.h>

int main(void) {
	
	int i=0,j=0,r=0,x=1,y;
	float rr;
	char a,b;
	
	while(1){
		
		printf("���� 2�� �Է�: ");
		scanf("%d %d", &i, &j); 
		getchar();
	
		while(1){
			printf("������ �Է� :");
			scanf("%c",&a);
			getchar();
		
			if(a=='+'){
				r=i+j;
				printf("%d %c %d = %d\n",i,a,j,r);
				break;
				
			}else if(a=='-'){
				r=i-j;
				printf("%d %c %d = %d\n",i,a,j,r);
				break;
			
			}else if(a=='*'){
				r=i*j;
				printf("%d %c %d = %d\n",i,a,j,r);
				break;
				
			}else if(a=='/'){
				rr=(float)i/j;
				printf("%d %c %d = %lf\n",i,a,j,rr); 
				break;
				
			}else {
				printf("\n");
				
			}
			
		}
	}
//		while(1){
//			printf("�ٽ��Ͻðڽ��ϱ�? Y/N");
//			scanf();
//		}
		
//	}
	
	return 0;
}
