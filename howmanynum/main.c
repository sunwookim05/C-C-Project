#include <stdio.h>

int pow(int a, int b) {
    if (b == 0) {
        return 1;
    }
 
    int n = pow(a, b / 2);
    int temp = n * n;
 
    if (b % 2 == 0) {
        return temp;
    } else {
        return a * temp;
    }
}

int main(){
	int a, n;
	scanf("%d%d", &a, &n);
	printf("%d",pow(a,n));
	return 0;
}