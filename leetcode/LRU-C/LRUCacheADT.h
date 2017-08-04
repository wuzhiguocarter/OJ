/*
* file name: LRUCacheImpl.h
* desp: LRU缓存内部数据结构
*/
#ifndef __LRUCACHEIMPL_H__
#define __LRUCACHEIMPL_H__

/*定义LRU缓存的缓存单元*/
typedef struct cacheEntryS{
    char key;     /* 数据的key */
    char data;    /* 数据的data */

    struct cacheEntryS *hashListPrev;  /* 缓存哈希表指针，指向哈希链表的前一个元素 */
    struct cacheEntryS *hashListNext;  /* 缓存哈希表指针，指向哈希链表的后一个元素 */

    struct cacheEntryS *lruListPrev;   /* 缓存双向链表指针，指向链表的前一个元素 */
    struct cacheEntryS *lruListNext;   /* 缓存双向链表指针，指向链表的后一个元素 */
}cacheEntryS;

/* 定义LRU缓存*/ 
typedef struct LRUCacheS{
    int cacheCapacity;        /*缓存的容量*/
    cacheEntryS **hashMap;    /*缓存的哈希表*/

    cacheEntryS *lruListHead; /*缓存双向链表表头*/
    cacheEntryS *lruListTail; /*缓存双向链表表尾*/
    int lruListSize;          /*缓存双向链表节点个数*/
}LRUCacheS;

/********************************************************
* LRU缓存单元相关接口及实现
********************************************************/
/*创建一个缓存单元*/
cacheEntryS* newCacheEntry(char key, char data);
/*释放一个缓存单元*/
void freeCacheEntry(cacheEntryS* entry);

/********************************************************
* 双向链表相关接口及实现
********************************************************/
/*从双向链表中删除指定节点*/
void removeFromList(LRUCacheS *cache, cacheEntryS *entry);
/* 将节点插入到链表表头*/ 
cacheEntryS * insertToListHead(LRUCacheS *cache, cacheEntryS *entry);

/*释放整个链表*/
void freeList(LRUCacheS *cache);
/*辅助性接口，用于保证最近访问的节点总是位于链表表头*/
void updateLRUList(LRUCacheS *cache, cacheEntryS *entry);


/********************************************************
* 哈希表相关接口及实现
********************************************************/
/*哈希函数*/
int hashKey(LRUCacheS *cache, char key);
/*从哈希表获取缓存单元*/
cacheEntryS *getValueFromHashMap(LRUCacheS *cache, int key);
/*向哈希表插入缓存单元*/
void insertentryToHashMap(LRUCacheS *cache, cacheEntryS *entry);
/*从哈希表删除缓存单元*/
void removeEntryFromHashMap(LRUCacheS *cache, cacheEntryS *entry);



#endif //__LRUCACHEIMPL_H__