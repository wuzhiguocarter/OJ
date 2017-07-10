/*
ID: wuzhigu1
LANG: C
TASK: friday
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <stdbool.h>

const int MAX_N = 400;

typedef struct{
	int CurrentYear;
	int CurrentMonth;
	int DaysInCYM;
	int CurrentThir;
	int ThirtCnt[7];
} Thirteenth;

Thirteenth th = {1899,0,31,6,{1,0, 0,0,0,0,0}};
/*
0 January
1 Febuary
2 March
...
11 December
*/
/*
6 Sat
0 Sun
1 Mon
2 Tur
3 Wed
4 Thu
5 Fri
*/

static bool isLeapYear(int year);
int calcuDays(int year, int month);
void updateThirtCnt(Thirteenth *th);

int main(int argc, char const *argv[])
{
    FILE *fin  = fopen ("friday.in", "r");
	FILE *fout = fopen ("friday.out", "w");

    int N,year;
    fscanf(fin,"%d\n",&N);
    year = N;

    for (int i = 0; i < year; ++i)
    {
    	th.CurrentYear += 1;
    	bool isLy = isLeapYear(th.CurrentYear);

    	for (int j = 1; j <= 12; ++j)
    	{
    		th.CurrentMonth = (j == 12) ? (th.CurrentMonth + 1) : (th.CurrentMonth + 1) % 12;
    		
    		th.DaysInCYM = calcuDays(th.CurrentYear,th.CurrentMonth);


    		printf("%d,%d isLeapYear,%dth Month has %d days\n",th.CurrentYear,isLy,th.CurrentMonth,th.DaysInCYM);

    		th.CurrentThir = (th.CurrentThir + th.DaysInCYM % 7) % 7;

    		if (i == year - 1 && j==12)
    		{
    			printf("Here not updateThirtCnt\n");
    		}
    		else{
    			updateThirtCnt(&th);
    		}
    	}
    }

	fprintf(fout,"%d %d %d %d %d %d %d\n",
		th.ThirtCnt[0], 
		th.ThirtCnt[1],
		th.ThirtCnt[2],
		th.ThirtCnt[3],
		th.ThirtCnt[4],
		th.ThirtCnt[5],
		th.ThirtCnt[6]);

    fclose(fin);
    fclose(fout);

    exit(0);
}

static bool isLeapYear(int year){
	return (year % 400) ? ((year % 100) ? ((year % 4) ? false:true): false) : true;
}

int calcuDays(int year, int month){
	int ret = -1;
	switch(month){
		case 1:
		case 3:
		case 5:
		case 7:
		case 8:
		case 10:
		case 12: ret = 31;break;
		case 4:
		case 6:
		case 9:
		case 11: ret = 30;break;
		case 2:  ret = isLeapYear(year) ? 29 : 28;break;
		default: ret = -1;printf("Error in Calulate Days\n");break;
	}
	return ret;
}

void updateThirtCnt(Thirteenth *th){
	int index = (th->CurrentThir + 1) % 7;
	th->ThirtCnt[index] += 1;
}