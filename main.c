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

// Summen av lista burde være lik summen av samme sortert liste
void assertSum(int list1[], int list2[], int length1, int length2){
	int sumList1 = sum(list1, length1);
	int sumList2 = sum(list2, length2);
	assert(sumList1 == sumList2);
	printf("Both lists have same sums\n");
}

// A sortert liste er en stigende list. F.eks. {2, 6, 9, 11, 21, 67}
void assertSorted(int list[], int length){
	if (length < 2){
		printf("List too short\n");
		return;
	}

	for (int i=1; i<length;i++){
		assert(list[i]>= list[i-1]);
	}

	printf("List is sorted\n");
	
}
int main(){
	int testlist[] = {1,2,3,4};
	int testlist2[] = {1,2,4,3};
	assertSum(testlist, testlist2, ARRAY_LEN(testlist), ARRAY_LEN(testlist2));
	assertSorted(testlist, ARRAY_LEN(testlist));
}
