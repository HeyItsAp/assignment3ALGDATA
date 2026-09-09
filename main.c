# include <stdio.h>

#define ARRAY_LEN(arr)(sizeof(arr)/sizeof((arr)[0]))

int sum(int list[], int length){
	int sum = 0;
	for (int i = 0; i < length; i++){
		sum += list[i];
	}
	return sum;
}
int main(){
	int testlist[] = {1,2,3,4};
	printf("%d\n", sum(testlist, ARRAY_LEN(testlist)));
	
}
