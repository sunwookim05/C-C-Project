#include <stdio.h>

int main(void){
	
	int arr[10],i = 11,r,ir,result=0;
	char j;
	
	printf("정수 10개 입력 : ");
	scanf("%d %d %d %d %d %d %d %d %d %d",&arr[0] ,&arr[1] ,&arr[2] ,&arr[3] ,&arr[4] ,&arr[5] ,&arr[6] ,&arr[7] ,&arr[8] ,&arr[9]);
	getchar();
	
	printf("알파벳 입력U/D : ");
	scanf("%c", &j);
	getchar();
	
	printf("자연수 입력 : ");
	scanf("%d",&i);
	getchar();
	
	if(i > 10){
		
		printf("ERROR\n");
		return 0;
		
	}
	
	switch(j){
		
		case 'U':
			
			for(r = 0; r < 9; r++){
				
				for(ir = 0; ir < 9 - r; ir++){
					
					if(arr[ir] > arr[ir + 1]){
						
						result = arr[ir];
						arr[ir] = arr[ir + 1];
						arr[ir + 1] = result;
						
					}
					
				}
				
			}
			
			for(r = 0; r < i; r++){
				printf("%d ",arr[r]);
				
			}
			
			break;
			
		case 'D':
			
			for(r = 0; r < 9; r++){
				
				for(ir = 0; ir < 9 - r; ir++){
					
					if(arr[ir] < arr[ir + 1]){
						
						result = arr[ir];
						arr[ir] = arr[ir + 1];
						arr[ir + 1] = result;
						
					}
					
				}
				
			}
			
			for(r = 0; r < i; r++){
				printf("%d ",arr[r]);
				
			}
		
			break;
		
		default:
			printf("ERROR\n");
			
	}
	
	return 0;
	
}
