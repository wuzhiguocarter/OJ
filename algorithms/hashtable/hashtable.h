#ifndef _HASHTABLE_H
#define _HASHTABLE_H

typedef unsigned int uint;
typedef char key_t;

/** 单向链表的节点的结构体 */
typedef struct _htItem{
        struct _htItem  *next;
        char *key_string;
        uint fid;

} htItem;

int bkdrHash( char *key );

void htInit( htItem **ht, uint length );

uint htSet( char *key, uint fid,  htItem **ht ); // 增，改
int htDel(char *key, htItem **ht); // 删
htItem* htGet( char *key, htItem **ht ); // 查

void print_hashTable( htItem **ht );


#endif