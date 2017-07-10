#include "hashtable.h"
#include <stdio.h>  // printf
#include <stdlib.h> // malloc
#include <string.h> // memset strcmp

/** 
 * BKDR hash function in clang
 * @param key char* 字符串
 * @return int hashed value, we will get a int value
 */
// BKDRHash哈希算法 https://segmentfault.com/a/1190000007783628
int bkdrHash( char *key )
{
    uint seed = 131;//i can be 13, 131, 1313,131313 etc
    uint hash = 0;
    while( *key != '\n' && *key != 0 )
    {
            hash = hash * seed + ( *key++ );
    }
    return ( hash & 0x7FFFFFFF );
}

/** 取得Key在数组中的映射位置 */
static uint htIndex( char *key, htItem **ht ){
        uint hashedKey = bkdrHash( key );
        uint length = (ht[0]->fid-1);
        return (uint)hashedKey % length+1;
}

/** 有必要对数组元素进行一次0值 初始化 */
void htInit( htItem **ht, uint length ){
    int i;
    for( i=0; i<length; i++ ){
        ht[i] = (htItem*)malloc(sizeof(htItem));
        memset( ht[i], 0, sizeof(htItem) );
    }
    ht[0]->fid = length;
}

/** set hashTable element */
uint htSet( char *key, uint fid,  htItem **ht ){
    uint i = htIndex( key, ht );
    htItem *item = ht[i];
    while( item->next )
    {
        if( strcmp(key, item->next->key_string) == 0 ){
            item->next->fid = fid;
            return 0;
        }else{
            item = item->next;
        }
    }
    item->next = (htItem*)malloc(sizeof(htItem));
    item->next->fid = fid;
    item->next->key_string = key;
    return 0;
}

/** get hashTable elements */
htItem* htGet( char *key, htItem **ht ){
    uint i = htIndex( key, ht);
    htItem *item = ht[i]->next;
    htItem *tmp = (htItem*)malloc(sizeof(htItem));
    memset(tmp, 0, sizeof(htItem));
        while( item )
        {
                if( strcmp(key, item->key_string) == 0 ){
            printf("hiting %s\n", key);
            tmp->fid = item->fid;
            tmp->key_string = item->key_string;
                        return tmp;
                }
        item = item->next;
        }
        return item;
}

/** delete one element of hashtable */
int htDel(char *key, htItem **ht){
        uint i = htIndex(key, ht);
        htItem *item = ht[i];
        while(item->next){
                if(strcmp(key, item->next->key_string) == 0 ){
                        htItem *tmp = item->next;
                        item->next = tmp->next;
                        free(tmp);
                        return 0;
                }
                item = item->next;
        }
        return -1;
}

/** print all element of hashtable */
void print_hashTable( htItem **ht )
{
        uint length = ht[0]->fid;
        uint i;
        htItem *item;
        for( i = 1; i < length; i++ )
        {
                item = ht[i]->next;
                while(item)
                {
                        printf("%s => %d\n",item->key_string, item->fid);
                        item = item->next;
                }
        }
}