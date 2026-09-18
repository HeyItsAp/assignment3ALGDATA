#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define ARRAY_LEN(arr) (sizeof(arr) / sizeof((arr)[0]))

int sum(int list[], int length)
{
	int sum = 0;
	for (int i = 0; i < length; i++)
	{
		sum += list[i];
	}
	return sum;
}

// A sortert liste er en stigende list. F.eks. {2, 6, 9, 11, 21, 67}
void assertSorted(int list[], int length)
{
	if (length < 2)
	{
		printf("List too short\n");
		return;
	}

	for (int i = 1; i < length; i++)
	{
		if (list[i] < list[i - 1])
		{
			fprintf(stderr, "Assertion failed: list[%d] (%d) < list[%d] (%d)\n", i, list[i], i - 1, list[i - 1]);
			return;
		}
	}

	printf("List is sorted\n");
}

// Hjelpe funksjon; Bytt.
void bytt(int *a, int *b)
{
	int t = *a;
	*a = *b;
	*b = t;
}
// Funksjon som returnerer tilfeldig array:
int *createRandomArray(int count, int min, int max)
{
	int range = max - min + 1;
	if (count > range)
		return NULL;

	int *unsortedlist = malloc(count * sizeof(int));
	int *used = calloc(range, sizeof(int));
	if (!used)
	{
		free(unsortedlist);
		return NULL;
	}

	for (int i = 0; i < count; i++)
	{
		int num;
		do
		{
			num = rand() % range;
		} while (used[num]);
		unsortedlist[i] = min + num;
		used[num] = 1;
	}
	free(used);
	return unsortedlist;
}
// Funksjon som returner en array der hverannen er 1:
int *createPatternArray(int count, int min, int max)
{
	if (count <= 0 || min > max)
		return NULL;

	int *unsorted = malloc(count * sizeof(int));
	if (!unsorted)
		return NULL;

	int range = max - min + 1;
	int duplicateValue = min; // Verdien som gjentas ofte

	for (int i = 0; i < count; i++)
	{
		if (i % 2 == 0)
		{
			// Annenhvert element får samme faste verdi
			unsorted[i] = duplicateValue;
		}
		else
		{
			// De andre elementene blir tilfeldige
			unsorted[i] = min + (rand() % range);
		}
	}

	return unsorted;
}

/*
***********************
QuickSort fra boka
	t: tabell
	h: høyre
	v: venste
	m: midten
************************
*/
// Hjelpe funksjon; Median. Assisterende sort?
int median3sort(int *t, int v, int h)
{
	int m = (v + h) / 2;
	if (t[v] > t[m])
		bytt(&t[v], &t[m]);
	if (t[m] > t[h])
	{
		bytt(&t[m], &t[h]);
		if (t[v] > t[m])
			bytt(&t[v], &t[m]);
	}
	return m;
}

// Hjelpe funksjon; Splitt. BAsert på boken finner en delingsverdi
int splitt(int *t, int v, int h)
{
	int iv, ih;
	int m = median3sort(t, v, h);
	int dv = t[m];
	bytt(&t[m], &t[h - 1]);

	for (iv = v, ih = h - 1;;)
	{
		while (t[++iv] < dv)
			;
		while (t[--ih] > dv)
			;
		if (iv >= ih)
			break;
		bytt(&t[iv], &t[ih]);
	}
	bytt(&t[iv], &t[h - 1]);
	return iv;
}

// Selve quick sort:
void quicksort(int *t, int v, int h)
{
	if (h - v > 2)
	{
		int delepos = splitt(t, v, h);
		quicksort(t, v, delepos - 1);
		quicksort(t, delepos + 1, h);
	}
	else
		median3sort(t, v, h);
}

/*
* **********************
Quicksort fra geekforgeeks
* **********************
*/
int partition(int *arr, int low, int high, int *lp);

void DualPivotQuickSort(int *arr, int low, int high)
{
	if (low < high)
	{
		// lp means left pivot, and rp means right pivot.
		int lp, rp;
		rp = partition(arr, low, high, &lp);
		DualPivotQuickSort(arr, low, lp - 1);
		if (arr[lp] != arr[rp])
		{
			DualPivotQuickSort(arr, lp + 1, rp - 1); // If pivots are equal just skip it
		}
		DualPivotQuickSort(arr, rp + 1, high);
	}
}

int partition(int *arr, int low, int high, int *lp)
{
	// New Pivot point to avoid worst case on identical
	int mid1 = low + (high - low) / 3;
	int mid2 = high - (high  low) / 3;

	if (arr[mid1] > arr[mid2]) bytt(&arr[mid1], &arr[mid2]);
	    bytt(&arr[low], &arr[mid1]);   // move left pivot candidate into place
	    bytt(&arr[high], &arr[mid2]);  // move right pivot candidate into place
	    
	if (arr[low] > arr[high])
		bytt(&arr[low], &arr[high]);
	// p is the left pivot, and q is the right pivot.
	int j = low + 1;
	int g = high - 1, k = low + 1, p = arr[low], q = arr[high]; // Better pivot candiate fix
	while (k <= g)
	{

		// if elements are less than the left pivot
		if (arr[k] < p)
		{
			bytt(&arr[k], &arr[j]);
			j++;
		}

		// if elements are greater than or equal
		// to the right pivot
		else if (arr[k] >= q)
		{
			while (arr[g] > q && k < g)
				g--;
			bytt(&arr[k], &arr[g]);
			g--;
			if (arr[k] < p)
			{
				bytt(&arr[k], &arr[j]);
				j++;
			}
		}
		k++;
	}
	j--;
	g++;

	// bring pivots to their appropriate positions.
	bytt(&arr[low + (high - low) / 3], &arr[j]);
	bytt(&arr[high - (high - low) / 3], &arr[g]);

	// returning the indices of the pivots.
	*lp = j; // because we cannot return two elements
	// from a function.

	return g;
}
// qsort compare function
int comp(const void *a, const void *b)
{
	int x = *(const int *)a;
	int y = *(const int *)b;

	if (x < y)
		return -1;
	if (x > y)
		return 1;
	return 0;
}
// qsort reverse
int reverse(const void *a, const void *b)
{
	return *(const int *)b - *(const int *)a;
}
// ********************
// Main
// ********************
int main()
{
	srand(time(NULL));
	int count = 500000;
	int trials = 5;
	int *unsorted1 = createRandomArray(count, 1, count);
	int *unsorted2 = createPatternArray(count, 1, count);
	int *unsorted3 = createRandomArray(count, 1, count);
	qsort(unsorted3, count, sizeof(int), comp);
	int *unsorted4 = createRandomArray(count, 1, count);
	qsort(unsorted4, count, sizeof(int), comp);
	qsort(unsorted4, count, sizeof(int), reverse);

	/*
	printf("\nGenerating 1:\n");
	for (int i = 0; i < count; i++){
		printf("%d ", unsorted1[i]);
	}
	printf("\n");

	printf("\nGenerating 2:\n");
	for (int i = 0; i < count; i++){
		printf("%d ", unsorted2[i]);
	}
	printf("\n");

	printf("\nGenerating 3:\n");
	for (int i = 0; i < count; i++){
		printf("%d ", unsorted3[i]);
	}
	printf("\n");

	printf("\nGenerating 4:\n");
	for (int i = 0; i < count; i++){
		printf("%d ", unsorted4[i]);
	}
	printf("\n");
	*/

	// RandomArray
	printf("=== Round 1: Random List ===\n");
	int *backup = malloc(count * sizeof(int));
	memcpy(backup, unsorted1, count * sizeof(int));
	assertSorted(unsorted1, count);

	printf("----- Quicksort -----\n");
	printf("- Pre-sorted stats -\n");
	printf("Sum: %d,\n", sum(unsorted1, count));

	double total_time = 0;
	for (int i = 0; i < trials; i++)
	{
		memcpy(unsorted1, backup, count * sizeof(int)); // Reset
		clock_t start = clock();
		quicksort(unsorted1, 0, count - 1);
		clock_t end = clock();
		total_time += (double)(end - start) / CLOCKS_PER_SEC;
	}
	double avg_time = total_time / trials;
	printf("- Completed -\n");
	printf("Sum: %d,\n", sum(unsorted1, count));
	assertSorted(unsorted1, count);
	printf("[[ Tid: %.12f ]]\n", avg_time);

	printf("----- Dual Pivot -----\n");
	printf("- Pre-sorted stats -\n");
	printf("Sum: %d,\n", sum(unsorted1, count));

	total_time = 0;
	for (int i = 0; i < trials; i++)
	{
		memcpy(unsorted1, backup, count * sizeof(int)); // Reset
		clock_t start = clock();
		DualPivotQuickSort(unsorted1, 0, count - 1);
		clock_t end = clock();
		total_time += (double)(end - start) / CLOCKS_PER_SEC;
	}
	avg_time = total_time / trials;
	printf("- Completed -\n");
	printf("Sum: %d,\n", sum(unsorted1, count));
	assertSorted(unsorted1, count);
	printf("[[ Tid: %.12f ]]\n", avg_time);
	free(unsorted1);
	printf("\n");

	// Duplicate
	printf("=== Round 2: Duplicate ===\n");
	memcpy(backup, unsorted2, count * sizeof(int));
	assertSorted(unsorted2, count);
	printf("----- Quicksort -----\n");
	printf("- Pre-sorted stats -\n");
	printf("Sum: %d,\n", sum(unsorted2, count));

	total_time = 0;
	for (int i = 0; i < trials; i++)
	{
		memcpy(unsorted2, backup, count * sizeof(int)); // Reset
		clock_t start = clock();
		quicksort(unsorted2, 0, count - 1);
		clock_t end = clock();
		total_time += (double)(end - start) / CLOCKS_PER_SEC;
	}
	avg_time = total_time / trials;
	printf("- Completed -\n");
	printf("Sum: %d,\n", sum(unsorted2, count));
	assertSorted(unsorted2, count);
	printf("[[ Tid: %.12f ]]\n", avg_time);

	printf("----- Dual Pivot -----\n");
	printf("- Pre-sorted stats -\n");
	printf("Sum: %d,\n", sum(unsorted2, count));

	total_time = 0;
	for (int i = 0; i < trials; i++)
	{
		memcpy(unsorted2, backup, count * sizeof(int)); // Reset
		clock_t start = clock();
		DualPivotQuickSort(unsorted2, 0, count - 1);
		clock_t end = clock();
		total_time += (double)(end - start) / CLOCKS_PER_SEC;
	}
	avg_time = total_time / trials;
	printf("- Completed -\n");
	printf("Sum: %d,\n", sum(unsorted2, count));
	assertSorted(unsorted2, count);
	printf("[[ Tid: %.12f ]]\n", avg_time);
	free(unsorted2);
	printf("\n");


	// Already sorted
	printf("=== Round 3: Already Sorted  ===\n");
	memcpy(backup, unsorted3, count * sizeof(int));
	assertSorted(unsorted3, count);
	printf("----- Quicksort -----\n");
	printf("- Pre-sorted stats -\n");
	printf("Sum: %d,\n", sum(unsorted3, count));

	total_time = 0;
	for (int i = 0; i < trials; i++)
	{
		memcpy(unsorted3, backup, count * sizeof(int)); // Reset
		clock_t start = clock();
		quicksort(unsorted3, 0, count - 1);
		clock_t end = clock();
		total_time += (double)(end - start) / CLOCKS_PER_SEC;
	}
	avg_time = total_time / trials;
	printf("- Completed -\n");
	printf("Sum: %d,\n", sum(unsorted3, count));
	assertSorted(unsorted3, count);
	printf("[[ Tid: %.12f ]]\n", avg_time);

	printf("----- Dual Pivot -----\n");
	printf("- Pre-sorted stats -\n");
	printf("Sum: %d,\n", sum(unsorted3, count));

	total_time = 0;
	for (int i = 0; i < trials; i++)
	{
		memcpy(unsorted3, backup, count * sizeof(int)); // Reset
		clock_t start = clock();
		DualPivotQuickSort(unsorted3, 0, count - 1);
		clock_t end = clock();
		total_time += (double)(end - start) / CLOCKS_PER_SEC;
	}
	avg_time = total_time / trials;
	printf("- Completed -\n");
	printf("Sum: %d,\n", sum(unsorted3, count));
	assertSorted(unsorted3, count);
	printf("[[ Tid: %.12f ]]\n", avg_time);
	free(unsorted3);
	printf("\n");

	// Reverse Sorted
	printf("=== Round 4: Reverse Sorted (already sorted but reverse order) ===\n");
	memcpy(backup, unsorted4, count * sizeof(int));
	assertSorted(unsorted4, count);
	printf("----- Quicksort -----\n");
	printf("- Pre-sorted stats -\n");
	printf("Sum: %d,\n", sum(unsorted4, count));

	total_time = 0;
	for (int i = 0; i < trials; i++)
	{
		memcpy(unsorted4, backup, count * sizeof(int)); // Reset
		clock_t start = clock();
		quicksort(unsorted4, 0, count - 1);
		clock_t end = clock();
		total_time += (double)(end - start) / CLOCKS_PER_SEC;
	}
	avg_time = total_time / trials;
	printf("- Completed -\n");
	printf("Sum: %d,\n", sum(unsorted4, count));
	assertSorted(unsorted4, count);
	printf("[[ Tid: %.12f ]]\n", avg_time);

	printf("----- Dual Pivot -----\n");
	printf("- Pre-sorted stats -\n");
	printf("Sum: %d,\n", sum(unsorted4, count));

	total_time = 0;
	for (int i = 0; i < trials; i++)
	{
		memcpy(unsorted4, backup, count * sizeof(int)); // Reset
		clock_t start = clock();
		DualPivotQuickSort(unsorted4, 0, count - 1);
		clock_t end = clock();
		total_time += (double)(end - start) / CLOCKS_PER_SEC;
	}
	avg_time = total_time / trials;
	printf("- Completed -\n");
	printf("Sum: %d,\n", sum(unsorted4, count));
	assertSorted(unsorted4, count);
	printf("[[ Tid: %.12f ]]\n", avg_time);
	free(unsorted4);
	free(backup);

	return 0;
}
