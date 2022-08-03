#include <stdio.h>

int main(void){
	int i;
	scanf("%d",&i);
	printf("%d\n",pp(i));
}

int pp(int i){
	int j,r = 0;
	while (i > 9){
		j = i;
		j %= 10;
		r += j;
		i = i / 10;
	}
	return r += i;
}

//#define calculate(a, b, c)	((c) == '+' ? (a+b) :((c) == '-' ? (a-b) :(((c) == '*' ? (a*b) : (((c) == '/' ? (a/b) : (a)))))))
//
//struct val{
//	double a, b, result;
//	char c;
//	char str[100];
//};
//
//double scanner(){
//	struct val count[100];
//	
//	int i;
//
//	for (i = 0; i < 5; i++){
//		scanf("%lf %c %lf",&count[i].a, &count[i].c, &count[i].b);
//		count[i].result = calculate(count[i].a, count[i].b, count[i].c);
//		sprintf(count[i].str,"%g %c %g = %g",count[i].a, count[i].c, count[i].b, count[i].result);
//	}
//	for(i = 0; i < 5; i++){
//		printf("%s \n",count[i].str);
//	}
//	return 0;
//}
//
//int main(void){
//
//	while(1){
//		scanner();
//	}
//
//	return 0;
//}
