/*
ID: wuzhigu1
LANG: C
TASK: ride
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <math.h>

int main () {
    FILE *fin  = fopen ("ride.in", "r");
    FILE *fout = fopen ("ride.out", "w");
    char s1[8];
	char s2[8];
/*
    char s1[6];
	char s2[6];
*/
	char *ps = s1;
	char temp;
	while(temp != '\n'){
		temp = fgetc (fin);
		*(ps++) = temp;
	}
	*(ps-1) = '\0';

	ps = s2;
	temp = ' ';
	while(temp != '\n'){
		temp = fgetc (fin);
		*(ps++) = temp;
	}
	*(ps-1) = '\0';

	printf("s1 has %d bytes,while s2 has %d bytes\n",(int)strlen(s1),(int)strlen(s2));
	printf("%s%s",s1,s2);

	long l1,l2;
	l1 = l2 = 1;
	long n1[6],n2[6];
	
	int i;
	for(i=0;i<strlen(s1);i++){
		n1[i] = s1[i] - 64;
		l1 = l1*n1[i];
		printf("n1 = %ld\tl1 = %ld\n",n1[i],l1);
	}
	for(i=0;i<strlen(s2);i++){
		n2[i] = s2[i] - 64;
		l2 = l2*n2[i];
		printf("n2 = %ld\tl2 = %ld\n",n2[i],l2);
	}

/*
	int i;
	for(i = 0;i < 6; i++){
		n1[i] = ((0 == s1[i] - 32 || s1[i] - '\n') ? 1 : s1[i] - 64);
		n2[i] = ((0 == s2[i] - 32 || s2[i] - '\n') ? 1 : s2[i] - 64);
		l1 = l1*n1[i];
		l2 = l2*n2[i];
		printf("n1 = %ld n2 = %ld l1 = %ld l2 = %ld\n",n1[i],n2[i],l1,l2);
	}
*/	
	l1 = l1%47;
	l2 = l2%47;
//	printf("%ld %ld\n",l1,l2);

	if(l1 == l2)
		fputs ("GO\n",fout);
	else    
		fputs ("STAY\n",fout);

    exit (0);
}
