/*
ID: wuzhigu1
LANG: C
TASK: barn1
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXSTALL 201

int hascow[MAXSTALL];

int intcmp(const void *va, const void *vb)
{
	return *(int*)vb - *(int*)va;
}

int main()
{
    FILE *fin, *fout;
    int n, m, nstall, ncow, i, j, c, lo, hi, nrun;
    int run[MAXSTALL];
 
    fin = fopen("barn1.in", "r");
    fout = fopen("barn1.out", "w");

    fscanf(fin, "%d %d %d", &m, &nstall, &ncow);

    for(i=0; i<ncow; i++) {
		fscanf(fin, "%d", &c);
	hascow[c-1] = 1;
    }
 
    n = 0;	
    for(i=0; i<nstall && !hascow[i]; i++)
	n++;
    lo = i;
    for(i=nstall-1; i>=0 && !hascow[i]; i--)
	n++;
    hi = i+1;
    nrun = 0;
    i = lo;
    while(i < hi) {
	while(hascow[i] && i<hi)
	    i++;
 
	for(j=i; j<hi && !hascow[j]; j++)
	    ;
	run[nrun++] = j-i;
	i = j;
    }
    qsort(run, nrun, sizeof(run[0]), intcmp);
    for(i=0; i<nrun && i<m-1; i++)
	n += run[i];
    fprintf(fout, "%d\n", nstall-n);
    exit(0);
}