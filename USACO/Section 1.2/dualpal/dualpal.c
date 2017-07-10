/*
ID: wuzhigu1
LANG: C
TASK: dualpal
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
#define MaxS 10000
#define MinS 0

#define MaxN 15
#define MinN 1

#define MaxB 10
#define MinB 2

int b = 2;
int n = 0;
int ns = 0;

/* Get Representation of Decimal Number n In Base b*/
void dec2nrb(long int n,int b,char *s);
/* Reverse string s to t*/
void rvs(const char *s,char *t); 
// const means that we don't change value of *s within function block

void main(void)
{
    FILE *fin, *fout;
    fin = fopen("dualpal.in", "r");
    fout = fopen("dualpal.out", "w");
    assert(fin != NULL && fout != NULL);
    /* Read Input. */
    fscanf(fin, "%d %d\n", &n, &ns);
    printf("N = %d, S = %d\n", n,ns);
    assert(MinN <= n && n <= MaxN && 0 < ns && ns < 10000);

    char s[20] = {'\0'};
    char t[20] = {'\0'};

    int lcnt = 0;
    int bcnt = 0;
    long int tns = ns + 1;
    while(lcnt != n)
    {
        printf("\ntns = %ld\n", tns);
        bcnt = 0; // reset to 0 very for loop
        for (int b = 2; b <= 10; ++b)
        {
            memset(s,'\0',20);
            memset(t,'\0',20);
            dec2nrb(tns,b,s);
            rvs(s,t);
            printf("base = %d,s = %s, t = %s\n", b,s,t);
            if(!strcmp(s,t))
            {
                bcnt++;
                if (bcnt >= 2)
                {
                    lcnt++;
                    fprintf(fout, "%ld\n", tns);
                    break;
                }
                
            }
            
        }
        tns++;
    }

    /* Free Dynamic Memory and Close All Opened Files. */
    fclose(fin);fclose(fout);
    exit(0);
}

/* Get Representation of Decimal Number n In Base b*/
void dec2nrb(long int n,int b,char *s)
{
    assert((n > 0) && (MinB <= b && b <= MaxB) && s != NULL);
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