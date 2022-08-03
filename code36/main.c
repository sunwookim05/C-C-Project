#include <stdio.h>

char code[36] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F','G','H','I','J','K','L','N','M','O','P','Q','R','S','T','U','V','W','X','Y','Z'};

int main(void){
	int n, i = 0;
	char str[] = {0};
	scanf("%d", &n);
	while(n != 0){
		str[i] = code[n % 36];
		n /= 36;
		i++;
	}
	printf("%s",str);
	return 0;
}