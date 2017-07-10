/*
ID: wuzhigu1
LANG: C
TASK: milk
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

/*
0 <= N <= 2,000,000
0 <= M <= 5,000
0 <= Pi <= 1,000
0 <= Ai <= 2,000,000
*/

long int N = -1; // the amount of milk that Merry Milk Makers wants per day
int M = -1; // the number of farmers that they may buy from


void arraySort(int *a,long int *b, int size);

int main () {
    FILE *fin  = fopen ("milk.in", "r");
    FILE *fout = fopen ("milk.out", "w");

    assert(fin != NULL && fout != NULL);

    fscanf(fin, "%ld %d\n", &N, &M);
    assert(N >= 0 && M >=0);
    printf("MMM wants %ld units of milk from %d farmers\n", N, M);
    // printf("sizeof(long int) = %lu Bytes\n",sizeof(long int));

    int P[M]; // Pi (0 <= Pi <= 1,000) is price in cents that farmer i charges.
    long int A[M]; // Ai (0 <= Ai <= 2,000,000) is the amount of milk that farmer i can sell to Merry Milk Makers per day.

    for (int i = 0; i < M; ++i)
    {
        fscanf(fin, "%d %ld\n", &P[i], &A[i]);
        // printf("Farmer %d: %ld units at %d cents per unit\n", i, A[i], P[i]);
    }

    arraySort(P,A,M);
    // printf("---Price---\t---Units---\n");
    // for (int i = 0; i < M; ++i)
    // {
    //     printf("%d\t%ld\n", P[i], A[i]);
    // }

    long totalUnits = 0;
    long int totalCost = 0;
    int i = 0;
    while(totalUnits != N)
    {
        
        totalCost += ((totalUnits + A[i]) >= N) ? 
            (N - totalUnits)*P[i] : A[i]*P[i];
        totalUnits = ((totalUnits + A[i]) >= N) ? 
            N : (totalUnits + A[i]);
        i++;
    }

    fprintf (fout, "%ld\n", totalCost);
    exit (0);
}

void arraySort(int *a,long int *b, int N)  
{     
    int temp1 = 0;
    long int temp2 = 0;
  
    //冒泡法排序实现从小到大排序  
    for(int i=0;i<N;i++) //进行N次循环  
    {  
        for(int j=i+1;j<N;j++) //循环比较剩余的变量  
        {  
            if(a[i] > a[j]) //如果前面一个数比后面数大，交换两个数的值  
            {  
                temp1 = a[i];
                a[i] = a[j];  
                a[j] = temp1;
                temp2 = b[i];
                b[i]  = b[j];
                b[j]  = temp2;
            }
        }  
    }
}