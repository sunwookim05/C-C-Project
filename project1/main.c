#include <stdio.h>

int main(void) {
	
	int i=0,j=0,r=0,x=1,y;
	float rr;
	char a,b;
	
	while(1){
		
		printf("정수 2개 입력: ");
		scanf("%d %d", &i, &j); 
		getchar();
	
		while(1){
			printf("연산자 입력 :");
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
//			printf("다시하시겠습니까? Y/N");
//			scanf();
//		}
		
//	}
	
	return 0;
}
