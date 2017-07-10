// test_sort.c
#include "sort.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>


static const int n = 50;
static const int sps = 10;

int main(){
	List list;
	list.a = (elem_t *)malloc(sizeof(int)*n);
	list.len = n;
	printf("Random Number From 0 ~ %d\n", list.len);
	srand(time(0));
	for (int i = 0; i < list.len; ++i)
	{
		list.a[i] = rand() % list.len;
		printf("%d", list.a[i]);
		(i+1) % sps == 0 ? printf("\n") : printf("\t");
	}
	
	// bubbleSort_RE(list.a,list.len); // test pass
	// bubbleSort_NRE(list.a,list.len); // test pass

	// selectionSort_RE(list.a,list.len); // test pass
	// selectionSort_NRE(list.a,list.len); // test pass

	// insertionSort_RE(list.a,list.len); // test pass
	// insertionSort_NRE(list.a,list.len); // test pass

	// shellSort_NRE(list.a,list.len); // test pass
	
	// heapSort_NRE(list.a,list.len); // test pass

	// mergeSort_RE(list.a,list.len); // test pass

	quickSort_RE(list.a,list.len); // test pass

	printf("\nOrdered Sequence:\n");
	printlist(list.a, list.len, sps);

	free(list.a);

	exit(0);
}