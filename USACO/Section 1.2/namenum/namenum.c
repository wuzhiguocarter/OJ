/*
ID: wuzhigu1
LANG: C
TASK: namenum
*/
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

/*
Note:
(1) read file containg numbers, isdigit()
(2) char * varible as function argument should be memset to '\0' before being passed
(3) difference between fscanf,fgets when reading string from file stream
(4) strcpy(a,b): note that strings can't be assigned to each other
(5) feof(fid): stdio.h
*/


#define MaxN 15

char givenSeri[MaxN] = {'\0'};
int n = 0;
// char validSeri[5000][MaxN] = {'\0'};

typedef struct maptable maptable;
struct maptable
{
	char num;
	char alpha[4];
};

maptable key[8] = {
					{'2',"ABC"},
					{'3',"DEF"},
					{'4',"GHI"},
					{'5',"JKL"},
					{'6',"MNO"},
					{'7',"PQRS"},
					{'8',"TUV"},
					{'9',"WXYZ"},
				};

void getSerialNum(char *s,maptable *key,char *seri);

void main(void)
{
    // FILE *fin,*fdin, *fout,*fdout;
    FILE *fin,*fdin, *fout;
    fin = fopen("namenum.in", "r");
    fdin = fopen("dict.txt","r");
    // fdout = fopen("dictseri.txt","w");
    fout = fopen("namenum.out", "w");
    // assert(fin != NULL && fout != NULL && fdin != NULL && fdout != NULL);
    assert(fin != NULL && fout != NULL && fdin != NULL);
    // fgets(givenSeri,MaxN,fin);
    fscanf(fin,"%s",givenSeri);
    printf("Serial Number is:\n");
    printf("%s\n", givenSeri);
    n = strlen(givenSeri);
    printf("n = %d\n", n);

    char s[MaxN] = {'\0'};
    char seri[MaxN] = {'\0'};
    int numofvn = 0;int i = 0;

    int validtime = 0;
    while(!feof(fdin))
    {
    	memset(s,'\0',MaxN);
    	fscanf(fdin,"%s",s);

    	memset(seri,'\0',MaxN);
    	getSerialNum(s,key,seri);
    	// printf("\nNo.%d\n", i);
    	// printf("Name = %s, Serial = %s\n", s,seri);
    	// printf("strlen(seri) = %d\n", strlen(seri));
    	if (!strcmp(givenSeri,seri))
    	{
    		fprintf(fout,"%s\n", s);
    		validtime++;
    	}
    	// fprintf(fdout, "%s\n", seri);
    	// strcpy(&validSeri[i],seri);
    	numofvn = i++;
    }
    if (0 == validtime)
    {
    	fprintf(fout, "NONE\n");
    }

    // fprintf(stderr, "%s\n", );
    fclose(fin);fclose(fdin);fclose(fout);//fclose(fdout);
    exit(0);
}

void getSerialNum(char *s,maptable *key,char *seri)
{
	assert(s!=NULL && seri!=NULL);
	char len = strlen(s); // '\0' must be appended at the end of s


	// printf("\nstrlen(Name) = %d charaters\n", len);
	for (int i = 0; i < len; ++i)
	{
		assert('A' <= s[i] && s[i] <= 'Z');
		if (s[i] < 'P')
		{
			seri[i] = key[(s[i] - 'A')/3].num;
			continue;
		}
		if ('P' <= s[i] && s[i] <= 'S')
		{
			seri[i] = key[5].num; // '7'
			continue;
		}
		if ('T' <= s[i] && s[i] <= 'V')
		{
			seri[i] = key[6].num; // '8'
			continue;
		}
		if ('W' <= s[i] && s[i] <= 'Z')
		{
			seri[i] = key[7].num; // '9'
			continue;
		}
	}
}