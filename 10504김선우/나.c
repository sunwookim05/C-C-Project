#include <stdio.h>
#include <math.h>

int main(void){
	
	float a,b,c,s,r,ir;
	
	printf("�� ���� ���̸� �Է��Ͻÿ� (cm) : ");
	scanf("%f %f %f", &a, &b, &c);
	
	if(a+b<=c || a+c<=b || b+c<=a){
		
		printf("ERROR");
		return 0;
		
	}else if(a==b && b==c || a==c && c==b || b==c && c==a){
		
		printf("���ﰢ��\n");
		
	}else if(((a*a)+(b*b) == c*c || (a*a)+(c*c) == b*b || (c*c)+(b*b) == a*a) && a==b || b==c || c==a){
		
		printf("���� �̵ �ﰢ��\n");
		
	}else if((a*a)+(b*b) == c*c || (a*a)+(c*c) == b*b || (c*c)+(b*b) == a*a){
		
		printf("���� �ﰢ��\n");
		
	}else if(a==b || b==c || a==c){
		
		printf("�̵ �ﰢ��\n");
		
	}else{
		
		printf("�ﰢ��\n");
		
	}
	
	s = (a+b+c) / 2;
	
	r = s*(s-a)*(s-b)*(s-c);
		
	printf("%4.3lf",sqrt(r));
	
	
	return 0;
}
