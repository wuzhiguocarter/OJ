#ifndef _SORT_H
#define _SORT_H

#define true 1
#define false 0

typedef int bool;

typedef int elem_t;

typedef struct{
	elem_t *a;
	int len;
} List;

void printlist(elem_t *a, int n, int sps);
bool listCompare(List *a1, List *a2,int n);
// ==============常用内部排序=================
// 冒泡排序（简单交换排序的改进）
extern void bubbleSort_RE(elem_t *a, int len);
extern void bubbleSort_NRE(elem_t *a, int len);
// 选择排序
extern void selectionSort_RE(elem_t *a, int n);
extern void selectionSort_NRE(elem_t *a, int n);
// 插入排序
extern void insertionSort_RE(elem_t *a, int n);
extern void insertionSort_NRE(elem_t *a, int n);
// 希尔排序（插入排序的改进）
extern void shellSort_RE(elem_t *a, int n);
extern void shellSort_NRE(elem_t *a, int n);
// 堆排序（简单选择排序的改进）
extern void heapSort_RE(elem_t *a, int n);
extern void heapSort_NRE(elem_t *a, int n);
// 归并排序
extern void mergeSort_RE(elem_t *a, int n);
extern void mergeSort_NRE(elem_t *a, int n);
// 快速排序（冒泡排序的改进）
extern void quickSort_RE(elem_t *a, int n);
extern void quickSort_NRE(elem_t *a, int n);

#endif