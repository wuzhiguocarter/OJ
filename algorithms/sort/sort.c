#include "sort.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
// #include <time.h>

// used for heapSort
#define PARENT(i) (i >> 1)
#define LEFT(i)   (i << 1)
#define RIGHT(i)  (i << 1 + 1)

static const int MAX_INT = ((unsigned)(-1))>>1;
// static const int MIN_INT = ~MAX_INT;

static inline int Parent(int i) {return i >> 1;}
static inline int Left(int i) {return i << 1;}
static inline int Right(int i) {return ((i << 1) + 1);} 

// declaration of inner function
static int elemCompare(elem_t a, elem_t b);
static void swap(elem_t *a, int i, int j);
static bool makeMinToBeHead_BUB(elem_t *a, int n);
static void makeMinToBeHead_INS(elem_t *a, int n);
static void insertNewElem(elem_t *a, int n);
static void HeapAdjust(elem_t *a, int s, int m);
// 使根节点为i的子树维持最大堆的性质（前提：节点为i的左右子树都是最大堆）
static void MaxHeapify_RE(elem_t *a, int len, int i); 
static void MaxHeapify_NRE(elem_t *a, int len, int i);
static void BuildMaxHeap(elem_t *a, int len);
static void merge(elem_t *a,int p,int q,int r);
static void mergeSort(elem_t *a, int p, int r);
static void quickSort(elem_t *a, int p, int r);
static int patition(elem_t *a, int p, int r);

// ================================================================
// export function implementation
// ================================================================
extern void printlist(elem_t *a, int n, int sps){
	assert(a!=NULL);
	for (int i = 0; i < n; ++i)
	{
		printf("%d", a[i]);
		(i+1) % sps == 0 ? printf("\n") : printf("\t");
	}	
}
bool listCompare(List *a1, List *a2, int n){
	assert(a1!=NULL && a2!= NULL && n > 0);
	int index = 0;
	while(index++ < n && a1->a[index] == a2->a[index]){
		if (index == n-1)
		{
			return true;
		}
	}
	return false;
}
// 冒泡排序 最坏o(n^2)
extern void bubbleSort_RE(elem_t *a, int n){
	printf("\nUsing bubbleSort_RE Algorithm:\n");
	assert(a!=NULL);
	if (n < 2) return;
	else{
		if(true == makeMinToBeHead_BUB(a,n))
			bubbleSort_RE(a+1,n-1);
		else return;
	}
}

extern void bubbleSort_NRE(elem_t *a, int n){
	printf("\nUsing bubbleSort_NRE Algorithm:\n");
	assert(a!=NULL);
	bool flag = true; 
	// 检测是否已排序完成的标志，避免无意义的比较
	for (int i = 0; i < n && flag == true; ++i)
	{
		flag = false; 
		// 若内层循环无交换，则说明序列已排序
		for (int j = n-1; j > 0; --j)
		{
			if (elemCompare(a[j-1],a[j]))
			{
				swap(a,j-1,j);
				flag = true;
			}
		}
		// printf("%d\n", a[i]);
	}
}
// 选择排序 最坏o(n^2)
extern void selectionSort_RE(elem_t *a, int n){
	printf("\nUsing selectionSort_RE Algorithm:\n");
	assert(a!=NULL);
	if (n < 2) return;
	else{
		makeMinToBeHead_INS(a,n);
		selectionSort_RE(a+1,n-1);
	}
}
extern void selectionSort_NRE(elem_t *a, int n){
	printf("\nUsing selectionSort_NRE Algorithm:\n");
	assert(a!=NULL);
	for (int i = 0; i < n-1; ++i)
	{
		int min = i;
		for(int j = i+1; j < n; ++j)
		{
			if (elemCompare(a[min],a[j]))
			{
				min = j;
			}
		}
		if (min != i) //
		{
			swap(a,i,min);
		}
	}
}
// 插入排序 最坏o(n^2)
extern void insertionSort_RE(elem_t *a, int n){
	printf("\nUsing insertionSort_RE Algorithm:\n");
	assert(a!=NULL);
	if(n < 2) return;
	else{
		insertionSort_RE(a,n-1);// a[0]~a[n-2]为有序的
		insertNewElem(a,n); // 将a[n-1]插入到有序表
	}
}
extern void insertionSort_NRE(elem_t *a, int n){
	assert(a!=NULL);
	printf("\nUsing insertionSort_NRE Algorithm:\n");
	//=====================method 1====================
	for (int i = 1; i < n; ++i)
	{
		for(int j = i; j >= 1 && elemCompare(a[j-1],a[j]); --j)
			swap(a,j-1,j);
	}
	// =====================method 2====================
	// for (int i = 0; i < n; ++i)
	// {
	// 	bool flag = true;
	// 	for(int j = i+1; j > 0 && flag == true; --j)
	// 	{
	// 		flag = false;
	// 		if (elemCompare(a[j-1],a[j]))
	// 		{
	// 			swap(a,j-1,j);
	// 			flag = true;
	// 		}
	// 	}
	// }
}
// 希尔排序
extern void shellSort_RE(elem_t *a, int n){

}
extern void shellSort_NRE(elem_t *a, int n){
	printf("\nUsing shellSort_NRE Algorithm:\n");
	assert(a!=NULL);
	// int loopCnt = 0; // for debug
	for(int increment = n/2; increment >= 1; increment = increment/2){
		// printf("\nLoop %d, increment = %d:\n", loopCnt++, increment);
		for(int i = increment; i < n; ++i){
			// printf("\ni = %d\n", i);
			for(int j = i; j >= increment && elemCompare(a[j-increment],a[j]); j -= increment)
			{
				// printf("%d and %d will be swaped\n", a[j-increment],a[j]);
				swap(a,j-increment,j);
			}
			// printlist(a,n,10);
		}
	}
}
// 堆排序（简单选择排序的改进）
extern void heapSort_RE(elem_t *a, int n){
	
}
extern void heapSort_NRE(elem_t *a, int n){
	assert(a!=NULL && n > 0);
	printf("\nUsing heapSort_NRE Algorithm:\n");
	//===================method 2 算法导论==================
	BuildMaxHeap(a,n);	// 构建最大堆
	for(int i = n-1; i >=1; i--){
		swap(a,0,i);
		MaxHeapify_NRE(a,i,0); 
		// 维护最大堆, 每循环一次，需要维护的堆的大小减一
		// 维护以偏移量为0的元素为根的大小为i的堆为最大堆
	}

	//===================method 1 大话数据结构==================
	// for (int i = n/2; i > 0; i--)
	// {
	// 	HeapAdjust(a,i,n);
	// } // 构建最大堆// 维护最大堆
	// for(int i = n; i > 1; i--)
	// {
	// 	swap(a,0,i-1);
	// 	HeapAdjust(a,1,i-1);
	// }// 维护最大堆

}
// 归并排序
extern void mergeSort_RE(elem_t *a, int n){
	printf("\nUsing mergeSort_RE Algorithm:\n");
	assert(a!=NULL && n >= 0);
	int p = 0, r = n-1;
	mergeSort(a,p,r);
}
extern void mergeSort_NRE(elem_t *a, int n){
	
}
// 快速排序（冒泡排序的改进）
extern void quickSort_RE(elem_t *a, int n){
	printf("\nUsing quickSort_RE Algorithm:\n");
	assert(a!=NULL && n >= 0);
	int p = 0, r = n-1;
	quickSort(a,p,r);
}
extern void quickSort_NRE(elem_t *a, int n){

}
// ================================================================
// inner function implementation
// ================================================================
static int elemCompare(elem_t a, elem_t b){
	return (a > b);
}

static void swap(elem_t *a, int i, int j){
	assert(a!=NULL);
	int temp = a[j];
	a[j] = a[i];
	a[i] = temp;
}

bool makeMinToBeHead_BUB(int *a, int n){
	assert(a!=NULL);
	bool flag = false;
	for (int i = n-1; i > 0; i--)
	{
		if (elemCompare(a[i-1],a[i]))
		{
			swap(a,i-1,i);
			flag = true;
		}
	}
	return flag;
}

static void makeMinToBeHead_INS(elem_t *a, int n){
	assert(a!=NULL);
	int min = 0;
	for (int i = 1; i < n; ++i)
	{
		if (elemCompare(a[min],a[i]))
		{
			min = i;
		}
	}
	if (min != 0)
	{
		swap(a,min,0);
		// printf("%d\n", a[0]);
	}
}

static void insertNewElem(elem_t *a, int n){
	assert(a!=NULL);
	// printf("\n%d will be inserted.\n", a[n-1]); // for debug
	bool flag = true; // 插入成功标志
	for (int i = n-1; i > 0 && (flag == true); --i) // 再也不要用代码自动生成功能 --i
	{
		flag = false;
		if (elemCompare(a[i-1],a[i]))
		{
			// printf("to swap %d and %d\n",a[i-1],a[i]); // for debug
			swap(a,i-1,i);
			flag = true;
		}
	}
	// printlist(a,n,10); // for debug
	// printf("\n"); 
}

static void HeapAdjust(elem_t *a, int s, int m){
	assert(a!=NULL && s > 0 && m > 0);
	int temp = a[s-1];
	for(int j = 2*s; j <= m; j *=2)
	{
		if(j < m && elemCompare(a[j],a[j-1]))
			++j;
		if(elemCompare(temp,a[j-1]))
			break;
		a[s-1] = a[j-1];
		s = j;
	}
	a[s-1] = temp;
}
// 维持一个最大堆，最坏时间复杂度O(log(n))
static void MaxHeapify_RE(elem_t *a, int len, int i){
	assert(a!=NULL && len >= 0 && i >=0 && i < len);
	// i是当前节点的偏移量，i+1是当前节点的层序编号
	// lchild是孩子节点的偏移量，lchild + 1是孩子节点的层序编号
	// 对于完全二叉树，有关系lchild + 1 = Left(i+1)
	int lchild = Left(i+1) - 1; 
	int rchild = Right(i+1) - 1;
	// 临时设置最大值节点的偏移量为当前节点值
	int largest = i;

	// 在有左孩子的前提下（lchild < len），将当前节点值与左孩子节点值比较
	if(lchild < len && elemCompare(a[lchild],a[largest]))
		largest = lchild;
	// 在有左孩子的前提下（lchild < len），将当前节点值与左孩子节点值中的较大值与右孩子节点值比较
	if(rchild < len && elemCompare(a[rchild], a[largest]))
		largest = rchild;

	if (largest != i){
		swap(a,i,largest);
		MaxHeapify_RE(a,len,largest);
	}
}

static void MaxHeapify_NRE(elem_t *a, int len, int i){
	assert(a!=NULL && len >= 0 && i >=0 && i < len);
	int root = i;
	while(root < len){
		int lchild = Left(root+1) - 1; 
		int rchild = Right(root+1) - 1;
		int largest = root;
		
		if(lchild < len && elemCompare(a[lchild],a[largest]))
			largest = lchild;
		if(rchild < len && elemCompare(a[rchild], a[largest]))
			largest = rchild;

		if (largest == root)
			break;
		else {
			swap(a,root,largest);
			root = largest; // 沿着未调整前较大孩子节点的子树往下调整
		}
	}
}
// 讲一个无序数组构建成一个最大堆，最坏时间复杂度为O(n)
static void BuildMaxHeap(elem_t *a, int len){
	assert(a!=NULL && len >= 0);
	for(int i = Parent(len)-1; i >= 0; i--){
		MaxHeapify_NRE(a,len,i);
	}
}
static void mergeSort(elem_t *a, int p, int r){
	assert(a!=NULL && p >= 0 && r >=0 && r >= p);
	if(p < r){
		int q = ((p+r) >> 1);
		mergeSort(a,p,q);
		mergeSort(a,q+1,r);
		merge(a,p,q,r);
	}
}
// 合并两个有序的子序列为一个有序序列
static void merge(elem_t *a,int p,int q,int r){
	assert(a!=NULL && p >= 0 && q >= 0 && r >=0 && q >=p && r >= q);
	int nl = q - p + 1; // len1
	int nr = r - q;     // len2
	int L[nl+1],R[nr+1];
	for(int i = 0; i < nl; i++){
		L[i] = a[p+i];
	}
	for (int j = 0; j < nr; ++j){
		R[j] = a[q+j+1];
	}
	L[nl] = MAX_INT;
	R[nr] = MAX_INT;
	int i = 0, j = 0;
	// O(n), n = r - p + 1
	for(int k = p;k <= r;k++){
		if(elemCompare(L[i],R[j])){
			a[k] = R[j];
			j++;
		}
		else{
			a[k] = L[i];
			i++;
		}
	}
}
// static int cnt = 0;
static void quickSort(elem_t *a, int p, int r){
	assert(a!=NULL);
	// printf("\nNo.%05d p = %d, r = %d\n", ++cnt,p,r);
	if(p < r){
		int q = patition(a,p,r);
		// printf("\nNo.%05d p = %d, q = %d, r = %d\n", ++cnt,p,q,r);
		quickSort(a,p,q-1);
		quickSort(a,q+1,r);
	}
}
static int patition(elem_t *a, int p, int r){
	assert(a!=NULL && p >= 0 && r >=0 && r >= p);
	//x取子数组最后一个元素，把比x小的放在左边， 把比x大放到右边
	elem_t x  = a[r]; 
	int i = p - 1;
	for(int j = p; j <= r-1; j++){
		if (elemCompare(x,a[j])) // a[j] <= x
		{
			swap(a,++i,j);
		}
	}
	swap(a,i+1,r);
	return (i+1);
}