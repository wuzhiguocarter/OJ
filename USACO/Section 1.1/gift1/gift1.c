/*
ID: wuzhigu1
LANG: C
TASK: gift1
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

const int MAX_NAME_LEN = 14;

typedef struct{
	char *name;
	int giving;
	int dividing;
	char **recipient;
} strucFriend;

// int friCnt = -1;

char **getNameList(FILE *f,int numOfFri);
void getFriName(FILE *f,strucFriend *fri);
void getGivDiv(FILE *f,strucFriend *fri);
void getRecipient(FILE *f,strucFriend *fri);
void updateGain(strucFriend *fri,char **NameList,int *gain,int NP);

int main(int argc, char const *argv[])
{
    FILE *fin  = fopen ("gift1.in", "r");
	FILE *fout = fopen ("gift1.out", "w");

    int NP;
    fscanf(fin,"%d\n",&NP);

    printf("%d\n", NP);

    strucFriend fri[NP];

    int gain[NP];

    char **NameList;
	
	for (int i = 0; i < NP; ++i)
	{
		gain[i] = 0;
	}

    // while(!feof(fin)){
    	NameList = getNameList(fin,NP);
    	for (int i = 0; i < NP; ++i)
    	{
    		getFriName(fin,&fri[i]);
    		getGivDiv(fin,&fri[i]);
    		getRecipient(fin,&fri[i]);
    		// printf("%s", fri[i].name);
    		// printf("%s\n\n", fri[i].recipient[0]);
/*    		if(!strcmp(*(fri[i].recipient),NameList[2]))
    			printf("fri[%d].recipient == NameList[2]\n",i);
    		else
    			printf("fri[%d].recipient == NameList[2]\n",i);*/
 	  		updateGain(&fri[i],NameList,gain,NP);
 	  		// fprintf(fout,"%s %d NP = %d\n",NameList[i],gain[i],i);
    	}
    // } 

    for (int i = 0; i < NP; ++i)
    {
    	// NameList[i][strlen(NameList[i])-1] = '\0';
    	fprintf(fout,"%s %d\n",NameList[i],gain[i]);
    	printf("%s\n", NameList[i]);
    }

    fclose(fin);
    fclose(fout);

    exit(0);
}

char **getNameList(FILE *f,int numOfFri){
	char** NameList = (char **)malloc(sizeof(char *) * numOfFri);
	for (int i = 0; i < numOfFri; ++i)
	{
		NameList[i] = (char *)malloc(sizeof(char)*(MAX_NAME_LEN+1));
	}
	for (int i = 0; i < numOfFri; ++i)
	{
		fgets(NameList[i],MAX_NAME_LEN+1,f);
		printf("%s,%d bytes\n", NameList[i],(int)strlen(NameList[i]));
		NameList[i][(int)strlen(NameList[i])-1] = '\0';
		printf("%s,%d bytes\n", NameList[i],(int)strlen(NameList[i]));
	}
	return NameList;
}

void getFriName(FILE *f,strucFriend *fri){
	 fri->name = (char *)malloc(sizeof(char) * (MAX_NAME_LEN+1));
	 fgets(fri->name,MAX_NAME_LEN+1,f);
	 // friCnt++;
	 printf("%s,%d bytes\n", fri->name, (int)strlen(fri->name));
	 fri->name[(int)strlen(fri->name)-1] = '\0';
	 printf("%s,%d bytes\n", fri->name, (int)strlen(fri->name));
}

void getGivDiv(FILE *f,strucFriend *fri){
	fscanf(f,"%d %d\n",&fri->giving,&fri->dividing);
	printf("%d %d\n", fri->giving,fri->dividing);
}

void getRecipient(FILE *f,strucFriend *fri){

	fri->recipient = (char **)malloc(sizeof(char *) * fri->dividing);
	for(int i=0; i<fri->dividing; i++)
	{
		fri->recipient[i] = (char *)malloc(sizeof(char) * (MAX_NAME_LEN+1));
	//}

	//for (int i = 0; i < fri->dividing; ++i)
	//{
		fgets(fri->recipient[i],MAX_NAME_LEN+1,f);
		printf("%s,%d bytes\n", fri->recipient[i],(int)strlen(fri->recipient[i]));
		fri->recipient[i][(int)strlen(fri->recipient[i])-1] = '\0';
		printf("%s,%d bytes\n", fri->recipient[i],(int)strlen(fri->recipient[i]));
	//	fri->recipient++;// core dump
	//}
	}
}

void updateGain(strucFriend *fri,char **NameList,int *gain,int NP){
	
	int giftLeft = (fri->dividing==0 ? 0 : fri->giving%fri->dividing);
	// gain[friCnt] = gain[friCnt] - fri->giving + giftLeft;
	int giftGivingDiv = (fri->dividing==0 ? 0 : fri->giving/fri->dividing);

	char **rec = fri->recipient;
	char **nl = NameList;

	for (int j = 0; j < NP; ++j)
	{
		if(!strcmp(fri->name,nl[j]))
		{
			gain[j] = gain[j] - fri->giving + giftLeft;// giving 
			break;// giving 
		}
	}

	for (int i = 0; i < fri->dividing; ++i){
		for (int j = 0; j < NP; ++j)
		{
			if(!strcmp(rec[i],nl[j]))
			{
				gain[j] += giftGivingDiv;// recipient
				break;
			}
		}
	}

	for (int i = 0; i < NP; ++i)
	{
		printf("%d\t",gain[i]);
	}
	printf("\n");
}