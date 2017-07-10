// #include <stdio.h>
// #include <stdlib.h>

// struct stru{
// 	char *name;
// 	int age;
// } st;

// int main(){
// 	printf("sizeof char* is %lu bytes\n", sizeof(char*));// 8
// 	printf("sizeof int is %lu bytes\n", sizeof(int));// 4
// 	printf("sizeof struct stru st is %lu bytes\n", sizeof st);// 16
// 	printf("NULL equals %d here\n", (int)NULL);// 0

// 	exit(0);
// }

#include <stdio.h>
 
int main(void)
{
    // type argument:
    printf("sizeof(float)         = %zu\n", sizeof(float));
    printf("sizeof(void(*)(void)) = %zu\n", sizeof(void(*)(void)));
    printf("sizeof(char[10])      = %zu\n", sizeof(char[10]));
//  printf("sizeof(void(void)) = %zu\n", sizeof(void(void))); // Error: function type
//  printf("sizeof(char[]) = %zu\n", sizeof(char[])); // Error: incomplete type
 
    // expression argument:
    printf("sizeof 'a'   = %zu\n", sizeof 'a'); // type of 'a' is int
//  printf("sizeof main = %zu\n", sizeof main); // Error: Function type
    printf("sizeof &main = %zu\n", sizeof &main);
    printf("sizeof \"hello\" = %zu\n", sizeof "hello"); // type is char[6]
}