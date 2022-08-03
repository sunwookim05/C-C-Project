#include <stdio.h>

void hex(int i){
	char arr[26]="ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	if(i > 0){
		i--;
		hex(i/26);
		printf("%c",arr[i%26]);
	}
}

int main(void){
    int i;

    scanf("%d",&i);
	hex(i);

	return 0;
}