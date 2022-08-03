#include <stdio.h>
#include <string.h>

int main(void){
	
	int i = 0,j,r = 0;
	unsigned char str[][100 + 1] = "";

	while(1){
		scanf("%[^\n]",str[i]);
		getchar();
		if(strcmp(str[i], "ESC") == 0)
			break;
		i++;
		for(j = 0; j < 100; j++){
			if(str[i][j] != "\0" && str[i][j] != '\n'){
				r++;
			}else{
				break;
			}
		}
	}
	printf("문자열은 %d 개, 문자는 %d 개", i, r);
	
	return 0;
}
