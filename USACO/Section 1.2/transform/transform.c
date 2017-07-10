/*
ID: wuzhigu1
LANG: C
TASK: transform
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


#define MaxN 20
#define TRANS 7

int N = 1;
int transIndex = 1;
char *s=NULL,*sc=NULL,*sct = NULL;

char* transform(const char *s,int N,int transIndex, ...);
char* rot90(const char *s, int N);
char* reflect(const char *s, int N);
char* combine(const char *s, int N, int CombIndex);
void printGraph(char *s,int N);

void main(void)
{
    FILE *fin, *fout;
    fin = fopen("transform.in", "r");
    fout = fopen("transform.out", "w");
    assert(fin != NULL && fout != NULL);
    

    /* read input, sort */
    fscanf(fin, "%d\n", &N);
    assert(N > 0);
    printf("%d\n", N);


    // char *s=NULL,*sc=NULL,*sct = NULL;

    s = (char *)malloc((N*N+1)*sizeof(char));
    assert(s!=NULL);
    memset(s,'\0',(N*N+1));
    char *st = s;
    for (int i = 0; i < N; ++i)
    {
        fscanf(fin, "%s\n", st);
        st += N;
    }   
    printf("s:\n");
    printGraph(s,N);

    sc = (char *)malloc((N*N+1)*sizeof(char));
    assert(sc!=NULL);
    memset(sc,'\0',(N*N+1));
    st = sc;
    for (int i = 0; i < N; ++i)
    {
        fscanf(fin, "%s\n", st);
        st += N;
    }   
    printf("sc:\n");
    printGraph(sc,N);



    for (int i = 1; i <= TRANS; ++i)
    {
        if(i != 5)
        {
            sct = transform(s,N,i);

            printf("strcmp(sct,sc) = %d\n", strcmp(sct,sc));
            if (0 == strcmp(sct,sc))
            {
                transIndex = i;
                printf("transIndex = %d\n", i);
                break;
            }
        }
        else
        {
            for (int j = 1; j <= 3; ++j)
            {
                sct = transform(s,N,i,j);

                if (0 == strcmp(sct,sc))
                {
                    transIndex = i;
                    printf("transIndex = %d\n", i);
                    goto label;// braek can't jump out nested loops
                }
            }
        }

    }

    label:;
    fprintf(fout, "%d\n", transIndex);

    free(s);free(sc);free(sct);
    fclose(fin);fclose(fout);
    exit(0);
}

char* transform(const char *s,int N,int transIndex, ...)
{ 
    assert(N > 0 && s != NULL && ( 1 <= transIndex && transIndex <= 7));

    char *ret = NULL;// do not use uninitialized pointer

    switch(transIndex)
    {
        // // #1: 90 Degree Rotation: The pattern was rotated clockwise 90 degrees.
        case 1:
        {
            ret = rot90(s, N);
            printf("#1:rot90:\n");
            printGraph(ret,N);
            break;
        }
        // #2: 180 Degree Rotation: The pattern was rotated clockwise 180 degrees.
        case 2:
        {
            ret = rot90(s,N);
            ret = rot90(ret,N);
            printf("#2:rot180:\n");
            printGraph(ret,N);
            break;
        }
        // #3: 270 Degree Rotation: The pattern was rotated clockwise 270 degrees.
        case 3:
        {
            ret = rot90(s,N);
            ret = rot90(ret,N);
            ret = rot90(ret,N);
            printf("#3:rot270:\n");
            printGraph(ret,N);
            break;
        }
        // #4: reflect
        case 4:
        {
            ret = reflect(s,N);
            printf("#4:reflect:\n");
            printGraph(ret,N);
            break;
        }
        // #5: combine
        case 5:
        {
            va_list args;
            va_start(args, transIndex);
            int CombIndex = va_arg(args, int);
            assert(1 <= CombIndex && CombIndex <= 3);
            ret = combine(s,N,CombIndex);
            va_end(args);
            break;
        }
        // #6: No Change
        case 6:
        {
            ret = (char *)malloc((N*N+1)*sizeof(char));
            assert(ret!=NULL);
            memset(ret,'\0',(N*N+1));
            memcpy(ret,s,N*N);
            printf("#6:No Change:\n");
            printGraph(ret,N);
            break;
        }
        case 7:
        {
            ret = (char *)malloc((N*N+1)*sizeof(char));
            assert(ret!=NULL);
            memset(ret,'\0',(N*N+1));// for strcmp
            memcpy(ret,sc,N*N);
            printf("#7:Invalid Transformation!\n");
            printGraph(ret,N);
            break;
        }
    }

    return ret;
}

char* rot90(const char *s, int N)
{
    assert(s!=NULL && N>0);

    char *ret = (char *)malloc((N*N+1)*sizeof(char));
    assert(ret!=NULL);
    memset(ret,'\0',(N*N+1));

    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            ret[j*N + (N-1) - i] = s[i*N+j];
        }
    }
    return ret;
}

char* reflect(const char *s, int N)
{
    assert(s!=NULL && N>0);

    char *ret = (char *)malloc((N*N+1)*sizeof(char));
    assert(ret!=NULL);
    memset(ret,'\0',(N*N+1));

    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            ret[i*N + (N-1) - j] = s[i*N + j];
        }
    }
    return ret;
}

char* combine(const char *s, int N, int CombIndex)
{
    assert(s!=NULL && N>0 && (1 <= CombIndex && CombIndex <= 3));

    char *ret = NULL;

    switch(CombIndex)
    {
        case 1: 
        {
            ret = reflect(s,N);
            ret = rot90(ret,N);
            printf("#5.1:Combine reflection and rot90:\n");
            printGraph(ret,N);
            break;
        }
        case 2:
        {
            ret = reflect(s,N);
            ret = rot90(ret,N);
            ret = rot90(ret,N);
            printf("#5.2:Combine reflection and rot180:\n");
            printGraph(ret,N);
            break;
        }
        default:
        {
            ret = reflect(s,N);
            ret = rot90(ret,N);
            ret = rot90(ret,N);
            ret = rot90(ret,N);
            printf("#5.3:Combine reflection and rot270:\n");
            printGraph(ret,N);
            break;
        }
    }

    return ret;
}

void printGraph(char *s,int N)
{
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            printf("%c", s[i*N+j]);
        }
        printf("\n");
    }
}

