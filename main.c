# include <stdio.h>
# include <assert.h>

#define ARRAY_LEN(arr)(sizeof(arr)/sizeof((arr)[0]))

int sum(int list[], int length){
	int sum = 0;
	for (int i = 0; i < length; i++){
		sum += list[i];
	}
	return sum;
}

int assertSum(int list1[], int list2[], int length1, int length2){
	int sumList1 = sum(list1, length1);
	int sumList2 = sum(list2, length2);
	assert(sumList1 == sumList2);
	printf("List1 | %d = %d | List2", sumList1, sumList2);
}
int main(){
	int testlist[] = {1,2,3,4};
	int testlist2[] = {1,2,3,4};
	assertSum(testlist, testlist2, ARRAY_LEN(testlist), ARRAY_LEN(testlist2));
}
