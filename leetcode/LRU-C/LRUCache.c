#include <stdio.h> // fprintf
#include <stdlib.h> // malloc, free
#include <string.h> // memset

#include "LRUCacheADT.h"
#include "LRUCache.h"

/********************************************************
* LRU缓存相关接口及实现
********************************************************/

/*创建一个LRU缓存*/
int LRUCacheCreate(int capacity, void **lruCache)
{
    LRUCacheS* cache = NULL;
    if (NULL == (cache=malloc(sizeof(*cache)))) {
        perror("malloc");
        return -1;
    }
    memset(cache, 0, sizeof(*cache));
    cache->cacheCapacity = capacity;
    cache->hashMap = malloc(sizeof(cacheEntryS)*capacity);
    if (NULL == cache->hashMap) {
        free(cache);
        perror("malloc");
        return -1;
    }
    memset(cache->hashMap, 0, sizeof(cacheEntryS)*capacity);
    *lruCache = cache;
    return 0;
}

/*释放一个LRU缓存*/
int LRUCacheDestory(void *lruCache)
{
    LRUCacheS* cache = (LRUCacheS*)lruCache;
    if (NULL == cache) return 0;
    //free hashmap
    if (cache->hashMap)
        free(cache->hashMap);
    //free linklist
    freeList(cache);
    free(cache);
    return 0;
}

/********************************************************
* 缓存存取接口
********************************************************/
/*将数据放入LRU缓存中*/
int LRUCacheSet(void *lruCache, char key, char data)
{
    LRUCacheS *cache = (LRUCacheS *)lruCache;
    /*从哈希表查找数据是否已经在缓存中*/
    cacheEntryS *entry = getValueFromHashMap(cache, key);
    if (entry!=NULL) {/*数据已经在缓存中*/
    /*更新数据，将该数据项更新至链表表头*/
        entry->data = data;
        updateLRUList(cache, entry);
    } else {
    /*数据没在缓存中*/
       /*新建缓存单元*/
       entry = newCacheEntry(key, data);

       /*将新建缓存单元插入链表表头*/
       cacheEntryS *removedEntry = insertToListHead(cache, entry);
       if (NULL != removedEntry) {
       /*将新建缓存单元插入链表表头过程中，发生缓存满了的情况，需要淘汰最久没有被访问到的缓存数据单元*/
           removeEntryFromHashMap(cache, removedEntry);     
           freeCacheEntry(removedEntry);
       }
       /*将新建缓存单元插入哈希表*/
       insertentryToHashMap(cache, entry);
    }    
    return 0;
}

/*从缓存中获取数据*/
char LRUCacheGet(void *lruCache, char key)
{
    LRUCacheS *cache = (LRUCacheS *)lruCache;
    /*从哈希表查找数据是否已经在缓存中*/
    cacheEntryS *entry = getValueFromHashMap(cache,key);
    if (NULL != entry) {
        /*缓存中存在该数据，更新至链表表头*/
        updateLRUList(cache, entry);
        /*返回数据*/
        return entry->data;
    } else {
        /*缓存中不存在相关数据*/
        return '\0';
    }
}

/********************************************************
* 调试接口
********************************************************/
/*遍历缓存链表，打印缓存中的数据，按访问时间从新到旧的顺序输出*/
void LRUCachePrint(void *lruCache)
{
    LRUCacheS *cache = (LRUCacheS *)lruCache;
    if (NULL==cache||0 == cache->lruListSize) return ;
    fprintf(stdout, "\n>>>>>>>>>>\n");
    fprintf(stdout, "cache  (key  data):\n");
    cacheEntryS *entry = cache->lruListHead;
    while(entry) {
        fprintf(stdout, "(%c, %c) ", entry->key, entry->data);
        entry = entry->lruListNext;
    }
    fprintf(stdout, "\n<<<<<<<<<<\n\n");
}