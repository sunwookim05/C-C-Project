#include <stdio.h>

int main(void){
	
	int x,y,r,blank1=5,blank2=8;
	
	for(x=0;x<5;x++){
		
		for(y=0;y<14;y++){
			
			if(blank1==y){
				
				printf("  ");
				
			}else if(blank2==y){
				
				printf("  ");
				
			}else{
				
				printf("бр");
				
			}
			
		}
		blank1--;
		blank2++;
		printf("\n");
	}
	
	blank1=1;
	blank2=12;
	
	for(x=0;x<5;x++){
		
		for(y=0;y<14;y++){
			
			if(blank1==y){
				
				printf("  ");
				
			}else if(blank2==y){
				
				printf("  ");
				
			}else{
				
				printf("бр");
				
			}
			
		}
		blank1++;
		blank2--;
		printf("\n");
	}
	
	return 0;
}
