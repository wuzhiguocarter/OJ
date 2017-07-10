#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int
hash(char *s)
{
	int i, h;

	h = 1;
	for(i=0; s[i] && isalpha(s[i]); i++)
		h = ((s[i]-'A'+1)*h) % 47;
	return h;
}

void
main(void)
{
	FILE *in, *out;
	char comet[100], group[100];  /* bigger than necessary, room for newline */

	in = fopen("ride.in", "r");
	out = fopen("ride.out", "w");

	fgets(comet, sizeof comet, in);
	fgets(group, sizeof group, in);

	if(hash(comet) == hash(group))
		fprintf(out, "GO\n");
	else
		fprintf(out, "STAY\n");
	exit (0);
}

/*
1. ctype.h
	int isalpha ( int c );
	
2. logic value of s[i]
	if s[i] is '\0' or NUL, the value of s[i] is 0, the logic value of s[i] is false;
	ascii of '\0' is 0, while ascii of '\n' is 10;

3. condition of for loop: use of logic expression
	for(i=0; s[i] && isalpha(s[i]); i++){
		statement
	}

4. file operation: 
	FILE * fopen ( const char * filename, const char * mode );
	char * fgets ( char * str, int num, FILE * stream );
	int fprintf ( FILE * stream, const char * format, ... );
	
5. sizeof is an operator
	Syntax
	sizeof( type )	(1)	
	sizeof expression	(2)	
	Both versions return a value of type size_t
*/