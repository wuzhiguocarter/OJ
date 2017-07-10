/*
ID: wuzhigu1
LANG: C
TASK: palsquare
*/
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

/*
Note:
(1)variable argument function
(2)malloc-assert-memset-strcmp
(3)matrix and one-dim/two-dim array
*/
/*
Input:
A single line with B, the b (specified in b 10).
Output:
Print both the number and its square in b B.
*/
#define MaxB 20
#define MinB 2

#define MaxN 300
#define MinN 1

int b = 0;

/* Get Representation of Decimal Number n In Base b*/
void dec2nrb(long int n,int b,char *s);
/* Reverse string s to t*/
void rvs(const char *s,char *t); 
// const means that we don't change value of *s within function block

void main(void)
{
    FILE *fin, *fout;
    fin = fopen("palsquare.in", "r");
    fout = fopen("palsquare.out", "w");
    assert(fin != NULL && fout != NULL);
    /* Read Input. */
    fscanf(fin, "%d\n", &b);
    assert(MinB <= b && b <= MaxB);

    char cN[20] = {'\0'};
    char s[20] = {'\0'};
    char t[20] = {'\0'};

    for (int i = MinN; i <= MaxN; ++i)
    {
        memset(cN,'\0',20);
        memset(s,'\0',20);
        memset(t,'\0',20);
        dec2nrb(i,b,cN);
        dec2nrb(i*i,b,s);
        rvs(s,t);
        if(!strcmp(s,t))
        {
            fprintf(fout, "%s %s\n", cN,s);
        }
    }

    /* Free Dynamic Memory and Close All Opened Files. */
    fclose(fin);fclose(fout);
    exit(0);
}

/* Get Representation of Decimal Number n In Base b*/
void dec2nrb(long int n,int b,char *s)
{
    assert((MinN*MinN <= n && n <= MaxN*MaxN) && (MinB <= b && b <= MaxB) && s != NULL);
    long int rem;

    char temp[20] = {'\0'};

    int i = 0;
    while(0 != n)
    {
        rem = n % b;
        temp[i] = (rem < 10) ? rem + '0' : (rem - 10) + 'A';
        n   = n / b;
        i++;
    }

    rvs(temp,s);
}
/* Reverse string s to t*/
void rvs(const char *s,char *t)
{
    assert(s!=NULL && t!=NULL);
    char len = strlen(s);
    for (int i = 0; i < len; ++i)
    {
        t[i] = s[(len-1) - i];
    }
} 