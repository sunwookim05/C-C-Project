#include <stdio.h>

int len[100000000] = {0, };
int bindex = 0;

int colatz(long long int n, int m){
	if(n < 99999999){ 
		if(len[n] != 0){
			return m + len[n];
		}
	}
	m++;
	if(n % 2 == 0) return colatz(n / 2, m);
	else return colatz(n * 3 + 1, m);
}

int main(void){
 	int min, max;
	
	len[1] = 1;
    scanf("%d %d", &min, &max);
	for(int i = min; i <= max; i++){
		len[i] = colatz(i, 0);
		if(len[bindex] < len[i]) bindex = i;
	}
	printf("%d %d\n", bindex, len[bindex]);
	return 0;
}