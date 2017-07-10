#ifndef _DCLIST_H
#define _DCLIST_H

typedef struct{
	int color;// 1 for 'r', 2 for 'b', 3 for 'w'
	int num;
} Tdata;

/*node*/
typedef struct DCListElmt_
{
	Tdata *data;
	struct DCListElmt_ *pre;
	struct DCListElmt_ *next;
} DCListElmt;

/*list*/
typedef struct DCList_
{
	int size;
	int (*match)(const void *key1, const void *key2);
	void (*destroy)(Tdata *data);
	DCListElmt *head;
	DCListElmt *tail;
} DCList;

#define dclist_size(list)			 ((list)->size)
#define dclist_head(list)			 ((list)->head)
#define dclist_tail(list)			 ((list)->tail)

#define dclist_is_head(element)		 ((element)->pre  == (list->tail) ? 1 : 0)
#define dclist_is_tail(element)      ((element)->next == (list->head) ? 1 : 0)
#define dclist_data(element)		 ((element)->data)
#define dclist_pre(element)			 ((element)->pre)
#define dclist_next(element)		 ((element)->next)

void dclist_init(DCList *list, void (*destroy)(Tdata *data));
void dclist_destory(DCList *list);
int dclist_ins_next(DCList *list, DCListElmt *element, const Tdata *data);
int dclist_rem(DCList *list, DCListElmt *element, Tdata **data);

// application dependent
int printdclist(DCList *list);

#endif