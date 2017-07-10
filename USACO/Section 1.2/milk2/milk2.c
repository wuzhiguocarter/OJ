/*
ID: wuzhigu1
LANG: C
TASK: milk2
*/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define MaxN 6000

int N;
long int t[MaxN][2];
long int t1[MaxN];
long int t2[MaxN];
long int idle_time[MaxN];// can be negative
long int ct[MaxN];
long int lct;//the longest continuous time
long int lit;//the longest idle time

long int temp_begin;
long int temp_end;

long int max(long int a[],int N)
{
	long int ret;
	ret = a[0];
	for (int i = 1; i < N; ++i)
	{
		ret = a[i] > ret ? a[i] : ret;
	}

	return ret;
}

void arraySort(long int *a,long int *b, int N)  
{     
    long int temp1 = 0;
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


int main () {
    FILE *fin  = fopen ("milk2.in", "r");
    FILE *fout = fopen ("milk2.out", "w");

    assert(fin != NULL && fout != NULL);

    fscanf (fin, "%d\n", &N);
    assert(N >= 1);

    // printf("N = %d\n", N);

    for (int i = 0; i < N; ++i)
    {
    	fscanf(fin,"%ld %ld\n", &t1[i],&t2[i]);
    }

    arraySort(t1,t2,N);

    temp_begin = t1[0];
    temp_end   = t2[0];

    int ct_index = 0;

    for (int i = 1; i < N; ++i)
    {
    	if (t1[i] - temp_end <= 0)
    	{
    		temp_end = (temp_end > t2[i]) ? temp_end : t2[i];
    	}
    	else
    	{
			printf("temp_begin = %ld, temp_end = %ld\n", temp_begin,temp_end);
    		   			
    		ct[ct_index] = temp_end - temp_begin;

    		idle_time[ct_index] = t1[i] - temp_end;
    		printf("t1 = %ld, temp_end = %ld, idle_time = %ld\n", t1[i], temp_end, idle_time[ct_index]);

    		temp_begin = t1[i];
    		temp_end   = t2[i];

    		ct_index ++;
    		printf("temp_begin = %ld, temp_end = %ld\n", temp_begin,temp_end);
    	}
    }
    ct[ct_index] = temp_end - temp_begin;// for the last ct

    lct = max(ct, ct_index);
    lit = max(idle_time, ct_index);
    lit = (lit < 0) ? 0 : lit;



    fprintf (fout, "%ld %ld\n", lct,lit);
    exit (0);
}