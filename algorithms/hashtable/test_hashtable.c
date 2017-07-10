#include "hashtable.h"
#include <stdio.h>

int main()
{
	htItem *item[101];
	htInit(item, 101);

	htSet("longmon",100,item);
	htSet("natalie", 1000,item);
	htSet("xiaoqiong",99, item);

	print_hashTable(item);	

	printf("Geting ...\n");

	htItem *tmp = htGet("longmon",item);
	
	printf("Key %s => %d\n", tmp->key_string, tmp->fid);

    htItem *tmp1 = htGet("natalie",item);

    printf("Key %s => %d\n", tmp1->key_string, tmp1->fid);

    htItem *tmp2 = htGet("xiaoqiong",item);

    printf("Key %s => %d\n", tmp2->key_string, tmp2->fid);

	printf("\nDelete natalie ...\n");
	
	htDel("natalie", item);

	printf("deleted \n");

	print_hashTable(item);
	
	htItem *tmp3 = htGet("natalie",item);
	
	printf("tmp3 pointer:%u\n", tmp3);
	if( tmp3->key_string ) {
	        printf("Key %s => %d\n", tmp3->key_string, tmp3->fid);
	}

	return 0;
}

// int main(){
// 	/** 定义与初始化 */
// 	htItem *item[101];
// 	htInit(item, 101);

// 	/** 添加元素 */
//     htSet("longmon",100,item); 
//     htSet("natalie", 1000,item);
//     htSet("xiaoqiong",99, item);

// 	/** 打印⑴ */
//     print_hashTable(item);
    
//     /** 删除一个元素 */
//     htDel("natalie", item);
    
//     /** 打印⑵ */
//     print_hashTable(item);
    
//     /** 获取key为longmon的值 */
//     htItem *tmpitem = htGet("longmon", item); 
    
//     /** 打印⑶ */
//     printf("key: %s => val:%d\n", tmpitem->key_string, tmpitem->fid);


// 	return 0;
// }