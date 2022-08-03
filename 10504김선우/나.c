#include <stdio.h>
#include <math.h>

int main(void){
	
	float a,b,c,s,r,ir;
	
	printf("세 변의 길이를 입력하시오 (cm) : ");
	scanf("%f %f %f", &a, &b, &c);
	
	if(a+b<=c || a+c<=b || b+c<=a){
		
		printf("ERROR");
		return 0;
		
	}else if(a==b && b==c || a==c && c==b || b==c && c==a){
		
		printf("정삼각형\n");
		
	}else if(((a*a)+(b*b) == c*c || (a*a)+(c*c) == b*b || (c*c)+(b*b) == a*a) && a==b || b==c || c==a){
		
		printf("직각 이등변 삼각형\n");
		
	}else if((a*a)+(b*b) == c*c || (a*a)+(c*c) == b*b || (c*c)+(b*b) == a*a){
		
		printf("직각 삼각형\n");
		
	}else if(a==b || b==c || a==c){
		
		printf("이등변 삼각형\n");
		
	}else{
		
		printf("삼각형\n");
		
	}
	
	s = (a+b+c) / 2;
	
	r = s*(s-a)*(s-b)*(s-c);
		
	printf("%4.3lf",sqrt(r));
	
	
	return 0;
}
