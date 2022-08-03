#include <stdio.h>

int main(void){
	
	int x=0,y=0,z=0,r=0,xi,yi,zi,ix,iy,iz,izz,ir,rr=0;
	
	for(x=0; x<=9; x++){
		
		for(y=0;y<=9;y++){
			
			for(z=0;z<=9;z++){
				
				xi=(x*10)+9;
				yi=(y*10)+5;
				zi=(z*10)+4;
				
				if(zi==xi-yi){
					r++;
				}
				
				ix=(x*10)+z;
				iz=(z*10)+0;
				ir=(y*10)+100+z;
				
				if(ir==ix+iz){
					rr++;
					
				}
				
			}
			
		}
		
	}
	
	printf("■9 - ▲5 = ●4이 성립하는 모든 경우의 개수 : %d 개\n",r);
	printf("■● + ●0 = 1▲●이 성립하는 모든 경우의 개수 : %d 개\n",rr);
		
	return 0;
	
}

