#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>


#include "dclist.h"
// compile: gcc -fPIC -shared dclist.c -o libdclist.so


void dclist_init(DCList *list, void (*destroy)(Tdata *data))
{
    list->size = 0;
    list->destroy = destroy;
    list->head = NULL;
    list->tail = NULL;
}

void dclist_destory(DCList *list)
{
    Tdata *data;
    while(dclist_size(list) > 0)
    {
        if(!dclist_rem(list, dclist_tail(list), (Tdata **)&data)
            && list->destroy != NULL)
        {
            list->destroy(data);
        }
    }
}

int dclist_ins_next(DCList *list, DCListElmt *element, const Tdata *data)
{
    DCListElmt *new_element=NULL;

    /* Do not allow a NULL element unless the list is empty*/
    if(element == NULL && dclist_size(list) != 0)
        return -1;

    
    /* Allocate storage for the element*/
    /* Here can't be debug by step because there's not src of malloc()*/
    new_element = (DCListElmt *)malloc(sizeof (DCListElmt));
/*    int *p = (int *)malloc(sizeof(int));
    *p = 777;
    printf("p = %d\n", *p);
    free(p);*/
    // printf("malloc new_element success!\n");

    // exit(0);
    
    if(new_element == NULL)
        return -1;

    /* coredump here: new_element->data need memory allocation*/
    /* Insert the new element into the list*/
    new_element->data = (Tdata *)malloc(sizeof (Tdata));
    *(new_element->data) = *data;

    if (dclist_size(list) == 0)
    {
        /* Handle insertion when the list is empty,
        the new_element will be head of list*/
        list->head = new_element;
        list->tail = new_element;
        list->head->pre  = new_element;
        list->head->next = new_element;
    }
    else
    {
        new_element->pre = element;
        new_element->next = element->next;

        /* when element is tail of list*/
        if (dclist_is_tail(element))
        {
            list->head->pre = new_element;
            list->tail = new_element;
        }
        else
        {
            element->next->pre = new_element;
        }

        element->next = new_element;
    }

    /* Adjust the size of list*/
    list->size++;
    return 0;
}

int dclist_rem(DCList *list, DCListElmt *element, Tdata **data)
{
    /* Do not allow a NULL element or removal from an empty list.*/
    if(element == NULL || dclist_size(list) == 0)
        return -1;

    /* Remove the element from the list*/
    *data = element->data;

    if (element == list->head)
    {
        if (dclist_size(list) == 1)
        {
            list->head = list->tail = NULL;
        }
        else
        {
            element->pre->next = element->next;
            element->next->pre = element->pre;
            list->head = element->next;
        }
    }
    else if (element == list->tail)
    {
        /* Here dclist_size must be larger than 1 */
        element->pre->next = element->next;
        element->next->pre = element->pre;
        list->tail = element->pre;
    }
    else
    {
        /* Here dclist_size must be larger than 1 */
        element->pre->next = element->next;
        element->next->pre = element->pre;
    }

    /* Free the storage allocated by the abstract type*/
    free(element);

    /* Adjust list size*/
    list->size--;

    return 0;
}

int printdclist(DCList *list){
    
    DCListElmt *ele = list->head;

    assert(dclist_size(list) != 0);

    while(!dclist_is_tail(ele))
    {
        int color = ele->data->color;
        int num = ele->data->num;
        printf("color is %d, num is %d\n", color, num);
        ele = ele->next;
    }

    int color = ele->data->color;
    int num = ele->data->num;
    printf("color is %d, num is %d\n", color, num);

    return 0;
}




// void dclist_init(DCList *list, void (*destroy)(Tdata *data))
// {
// 	list->size = 0;
// 	list->destroy = destroy;
// 	list->head = NULL;
// 	list->tail = NULL;
// }

// void dclist_destory(DCList *list)
// {
// 	Tdata *data;
// 	while(dclist_size(list) > 0)
// 	{
// 		if(!dclist_rem(list, dclist_tail(list), (Tdata **)&data)
// 			&& list->destroy != NULL)
// 		{
// 			list->destroy(data);
// 		}
// 	}
// }

// int dclist_ins_next(DCList *list, DCListElmt *element, const Tdata *data)
// {
// 	DCListElmt *new_element=NULL;

// 	/* Do not allow a NULL element unless the list is empty*/
// 	if(element == NULL && dclist_size(list) != 0)
// 		return -1;

	
// 	/* Allocate storage for the element*/
// 	/* Here can't be debug by step because there's not src of malloc()*/
// 	new_element = (DCListElmt *)malloc(sizeof (DCListElmt));
// /*    int *p = (int *)malloc(sizeof(int));
//     *p = 777;
//     printf("p = %d\n", *p);
//     free(p);*/
//     // printf("malloc new_element success!\n");

// 	// exit(0);
	
// 	if(new_element == NULL)
// 		return -1;

// 	/* coredump here: new_element->data need memory allocation*/
// 	/* Insert the new element into the list*/
// 	new_element->data = (Tdata *)malloc(sizeof (Tdata));
// 	*(new_element->data) = *data;

// 	if (dclist_size(list) == 0)
// 	{
// 		/* Handle insertion when the list is empty,
// 		the new_element will be head of list*/
// 		list->head = new_element;
// 		list->tail = new_element;
// 		list->head->pre  = new_element;
// 		list->head->next = new_element;
// 	}
// 	else
// 	{
// 		new_element->pre = element;
// 		new_element->next = element->next;

// 		/* when element is tail of list*/
// 		if (dclist_is_tail(element))
// 		{
// 			list->head->pre = new_element;
// 			list->tail = new_element;
// 		}
// 		else
// 		{
// 			element->next->pre = new_element;
// 		}

// 		element->next = new_element;
// 	}

// 	/* Adjust the size of list*/
// 	list->size++;
// 	return 0;
// }

// int dclist_rem(DCList *list, DCListElmt *element, Tdata **data)
// {
// 	/* Do not allow a NULL element or removal from an empty list.*/
// 	if(element == NULL || dclist_size(list) == 0)
// 		return -1;

// 	/* Remove the element from the list*/
// 	*data = element->data;

// 	if (element == list->head)
// 	{
// 		if (dclist_size(list) == 1)
// 		{
// 			list->head = list->tail = NULL;
// 		}
// 		else
// 		{
// 			element->pre->next = element->next;
// 			element->next->pre = element->pre;
// 			list->head = element->next;
// 		}
// 	}
// 	else if (element == list->tail)
// 	{
// 		/* Here dclist_size must be larger than 1 */
// 		element->pre->next = element->next;
// 		element->next->pre = element->pre;
// 		list->tail = element->pre;
// 	}
// 	else
// 	{
// 		/* Here dclist_size must be larger than 1 */
// 		element->pre->next = element->next;
// 		element->next->pre = element->pre;
// 	}

// 	/* Free the storage allocated by the abstract type*/
// 	free(element);

// 	/* Adjust list size*/
// 	list->size--;

// 	return 0;
// }

// int printdclist(DCList *list){
	
// 	DCListElmt *ele = list->head;

// 	assert(dclist_size(list) != 0);

// 	while(!dclist_is_tail(ele))
// 	{
// 		int color = ele->data->color;
// 		int num = ele->data->num;
// 		printf("color is %d, num is %d\n", color, num);
// 		ele = ele->next;
// 	}

// 	int color = ele->data->color;
// 	int num = ele->data->num;
// 	printf("color is %d, num is %d\n", color, num);

// 	return 0;
// }