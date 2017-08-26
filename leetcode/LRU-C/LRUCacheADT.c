#include <stdio.h> // fprintf
#include <stdlib.h> // malloc, free
#include <string.h> // memset

#include "LRUCacheADT.h"


/********************************************************
* LRU缓存及缓存单元相关接口及实现
********************************************************/
/*创建一个缓存单元*/
cacheEntryS* newCacheEntry(char key, char data)
{
    cacheEntryS* entry = NULL;
    if (NULL == (entry=malloc(sizeof(*entry)))) {
        perror("malloc");
        return NULL;
    }
    memset(entry, 0, sizeof(*entry));
    entry->key          = key;
    entry->data         = data;
    return entry;
}
/*释放一个缓存单元*/
void freeCacheEntry(cacheEntryS* entry)
{
    if (NULL == entry) return;
    free(entry);
}


/********************************************************
* 双向链表相关接口及实现
********************************************************/
/*从双向链表中删除指定节点*/
void removeFromList(LRUCacheS *cache, cacheEntryS *entry)
{
    /*链表为空*/
    if (cache->lruListSize==0)
        return ;

    if (entry==cache->lruListHead && entry==cache->lruListTail) {
    /*链表中仅剩当前一个节点*/
        cache->lruListHead = cache->lruListTail = NULL;
    } else if (entry == cache->lruListHead) {
    /*欲删除节点位于表头*/
        cache->lruListHead = entry->lruListNext;
        cache->lruListHead->lruListPrev = NULL;
    } else if (entry == cache->lruListTail) {
    /*欲删除节点位于表尾*/
        cache->lruListTail = entry->lruListPrev;
        cache->lruListTail->lruListNext = NULL;
    } else {
    /*其他非表头表尾情况，直接摘抄节点*/
        entry->lruListPrev->lruListNext = entry->lruListNext;
        entry->lruListNext->lruListPrev = entry->lruListPrev;
    }
    /*删除成功，链表节点数减1*/
    cache->lruListSize--;
}

/* 将节点插入到链表表头*/ 
cacheEntryS * insertToListHead(LRUCacheS *cache, cacheEntryS *entry) 
{
    cacheEntryS *removedEntry = NULL;

    if (++cache->lruListSize > cache->cacheCapacity) {
    /* 如果缓存满了，即链表当前节点数已等于缓存容量，那么需要先删除链表表尾节点，即淘汰最久没有被访问到的缓存数据单元*/
        removedEntry = cache->lruListTail;
        removeFromList(cache, cache->lruListTail);   
    }

    if (cache->lruListHead==NULL&&cache->lruListTail==NULL) {
    /*如果当前链表为空链表*/
            cache->lruListHead = cache->lruListTail = entry;
    } else {
    /*当前链表非空，插入表头*/
            entry->lruListNext = cache->lruListHead;
            entry->lruListPrev = NULL;
            cache->lruListHead->lruListPrev = entry;
            cache->lruListHead = entry;
    }

    return removedEntry;
}

/*释放整个链表*/
void freeList(LRUCacheS *cache)
{
    /*链表为空*/
    if (0 == cache->lruListSize) return;

    cacheEntryS *entry = cache->lruListHead;
    /*遍历删除链表上的所有节点*/
    while(entry) {
        cacheEntryS *temp = entry->lruListNext;
        freeCacheEntry(entry);     
        entry = temp;
    }
    cache->lruListSize = 0;
}

/*辅助性接口，用于保证最近访问的节点总是位于链表表头*/
void updateLRUList(LRUCacheS *cache, cacheEntryS *entry) 
{
    /*将节点从链表中摘抄*/
    removeFromList(cache, entry);
    /*将节点插入链表表头*/
    insertToListHead(cache, entry);
}

/********************************************************
* 哈希表相关接口及实现
********************************************************/
/*哈希函数*/
int hashKey(LRUCacheS *cache, char key)
{
    return (int)key%cache->cacheCapacity;
}

/*从哈希表获取缓存单元*/
cacheEntryS *getValueFromHashMap(LRUCacheS *cache, int key) {
    /*1.使用函数函数定位数据存放在哪个槽*/
    cacheEntryS *entry = cache->hashMap[hashKey(cache,key)];

    /*2.遍历查询槽内链表，找到准确的数据项*/
    while (entry) {
        if (entry->key == key)
            break;
        entry = entry->hashListNext;
    }

    return entry;
}

/*向哈希表插入缓存单元*/
void insertentryToHashMap(LRUCacheS *cache, cacheEntryS *entry) 
{
     /*1.使用函数函数定位数据存放在哪个槽*/
    cacheEntryS *n = cache->hashMap[hashKey(cache, entry->key)];
    if (n!=NULL) {
    /*2.如果槽内已有其他数据项，将槽内数据项与当前欲加入数据项链成链表，当前欲加入数据项为表头*/
       entry->hashListNext = n;
       n->hashListPrev = entry;
    }
    /*3.将数据项放入加入哈希槽内*/
    cache->hashMap[hashKey(cache,entry->key)] = entry;
}

/*从哈希表删除缓存单元*/
void removeEntryFromHashMap(LRUCacheS *cache, cacheEntryS *entry) 
{
    /*无需做任何删除操作的情况*/
    if (NULL==entry || NULL==cache || NULL==cache->hashMap) return ;

    /*1.使用函数函数定位数据存放在哪个槽*/
    cacheEntryS *n = cache->hashMap[hashKey(cache,entry->key)];
    /*2.遍历槽内链表，找到欲删除节点，将节点从哈希表摘除*/
    while (n) {
        if (n->key==entry->key) {/*找到欲删除节点，将节点从哈希表摘抄*/
            if (n->hashListPrev) {
                n->hashListPrev->hashListNext = n->hashListNext;
            } else {
                cache->hashMap[hashKey(cache, entry->key)] = n->hashListNext;
            }
            if (n->hashListNext)
                n->hashListNext->hashListPrev = n->hashListPrev;
            return ;
        }
        n = n->hashListNext;
    }

}

