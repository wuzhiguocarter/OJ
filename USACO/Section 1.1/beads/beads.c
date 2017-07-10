/*
ID: wuzhigu1
LANG: C
TASK: beads
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

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

#define dclist_size(list)            ((list)->size)
#define dclist_head(list)            ((list)->head)
#define dclist_tail(list)            ((list)->tail)

#define dclist_is_head(element)      ((element)->pre  == (list->tail) ? 1 : 0)
#define dclist_is_tail(element)      ((element)->next == (list->head) ? 1 : 0)
#define dclist_data(element)         ((element)->data)
#define dclist_pre(element)          ((element)->pre)
#define dclist_next(element)         ((element)->next)

void dclist_init(DCList *list, void (*destroy)(Tdata *data));
void dclist_destory(DCList *list);
int dclist_ins_next(DCList *list, DCListElmt *element, const Tdata *data);
int dclist_rem(DCList *list, DCListElmt *element, Tdata **data);

// application dependent
int printdclist(DCList *list);
// #include "dclist.h"

const int MinN = 3;
const int MaxN = 400;

// typedef struct{
//  int color;// 1 for 'r', 2 for 'b', 3 for 'w'
//  int num;
// } Tdata;

/* If you do not have have to free data manually, set destroy = NULL*/
void destroy(Tdata *data);
void str2list(char *s, DCList *list, int N);
int mergelist1(DCList *list);//count for 'r' 'b' 'w'
int mergelist2(DCList *list);//handle 'w' when color of its neighbors are diffrent
int* getSumSeries(DCList *list);
int getMax(int *s, int size);

int main()
{
    FILE *fin  = fopen ("beads.in", "r");
    FILE *fout = fopen ("beads.out", "w");
    assert(fin != NULL && fout != NULL);

    int N;
    fscanf(fin,"%d\n",&N);
    // printf("%d\n", N);

    assert(MinN <= N && N <= MaxN);

    char beads[MaxN];

    fgets(beads,sizeof beads,fin);

    // the last byte in beads is '\n'
/*    printf("%s, has %lu bytes,the last byte is %c",
        beads,strlen(beads),beads[strlen(beads)-1]);*/

    DCList list;
    dclist_init(&list,destroy);

    str2list(beads,&list,N);

    printf("Before merge:\n");

    // printdclist(&list);


    mergelist1(&list);

    printf("After merge1:\n");
    printdclist(&list);


    mergelist2(&list);

    printf("After merge2:\n");

    printdclist(&list);

    int *s = getSumSeries(&list);
    printf("Sum Series:\n");
    for (int i = 0; i < list.size; ++i)
    {
        printf("%d, ", s[i]);
    }

    printf("\n");

    int m = getMax(s, list.size);

    printf("max: %d\n", m);
    fprintf(fout, "%d\n", m);

    free(s);
    dclist_destory(&list);

    fclose(fin);
    fclose(fout);
    exit(0);
}

void destroy(Tdata *data)
{
    free(data);
    // printf("destroying data\n");
}

void str2list(char *s, DCList *list, int N)
{
    int i = 0;// index of beads string
    int sum = 0;// cnt of beads
    Tdata data = {0,0};// temp obj for list node
    while(isalpha(s[i]) && sum <= N)
    {
        switch(s[i]){
            case 'r':{
                data.color = 1;
                data.num = 1;
                i++;
                break;
            }
            case 'b':{
                data.color = 2;
                data.num = 1;
                i++;
                break;
            }
            case 'w':{data.color = 3;
                data.num = 1;
                i++;
                break;
            }
            default: printf("error in str2Tdata func\n");break;
        }

        if (dclist_size(list) == 0)
        {
            dclist_ins_next(list,NULL,&data);
        }
        else if (list->tail->data->color == data.color)
        {
            list->tail->data->num ++;
        }
        else{
            dclist_ins_next(list,list->tail,&data);
        }

        sum ++;
    }
    printf("sum of beads is %d\n", sum);
}

int mergelist1(DCList *list){
    // assert(list->size > 2);// if list->size <=2 , you can't merge
    if (list->size == 1 || list->size == 2)
    {
        return 0;
    }
    // printf("dclist_size is %d\n", list->size);
    DCListElmt *ele = list->head;
    Tdata *data;// temp for dclist_rem
    // printf("pre: color %d, num %d\n", ele->pre->data->color, ele->pre->data->num);
    // printf("head: color %d, num %d\n", ele->data->color, ele->data->num);
    // printf("next: color %d, num %d\n", ele->next->data->color, ele->next->data->num);
    while(!dclist_is_tail(ele) || list->tail->data->color == 3)
    {
        if (ele->data->color != 3)
        {
            ele = ele->next;
        }
        else if (ele->pre->data->color == ele->next->data->color)
        {
            ele->data->color = ele->pre->data->color;
            ele->data->num += ele->pre->data->num + ele->next->data->num;
            dclist_rem(list,ele->pre,&data);free(data);
            dclist_rem(list,ele->next,&data);free(data);// delete two neighbors of ele

            ele = ele->next;
        }
        else
        {
            ele = ele->next;
        }
    }

    if (list->tail->data->color == list->head->data->color)
    {
        list->head->data->num += list->tail->data->num;
        dclist_rem(list,list->tail,&data);free(data);
        
    }

    return 0;
}

int numSum(DCList *list, DCListElmt *ele, char dir, int num)
{
    assert(list->size >= num);
    int ret = 0;
    DCListElmt *tempElmt = ele;
    for (int i = 0; i < num; ++i)
    {
        ret += tempElmt->data->num;
        tempElmt = (dir == 'p') ? tempElmt->pre : tempElmt->next;
    }

    return ret;
}
int deleteElmt(DCList *list, DCListElmt *ele, char dir, int num)
{
    assert(list->size >= num);
    DCListElmt *tempElmt = (dir == 'p') ? ele->pre : ele->next;
    Tdata *data;
    for (int i = 0; i < num; ++i)
    {
        dclist_rem(list,tempElmt,&data);free(data);
        tempElmt = (dir == 'p') ? ele->pre : ele->next;
    }

    return 0;
}

int mergelist2(DCList *list){
    // assert(list->size > 2);// if list->size <=2 , you can't merge
    if (list->size == 1 || list->size == 2)
    {
        return 0;
    }
    // printf("dclist_size is %d\n", list->size);
    DCListElmt *ele = list->head;
    Tdata *data;// temp for dclist_rem

    while(!dclist_is_tail(ele) || list->tail->data->color == 3)// here #element must be equal or larger than 3
    {
        if (ele->data->color != 3)
        {
            ele = ele->next;
        }
        else // neighbors of 'w' are diffrent
        {
            if (list->size == 3)
            {
                ele->data->color = ele->pre->data->color;
                ele->data->num  += ele->pre->data->num;
                dclist_rem(list,ele->pre,&data);
                free(data);
                break;
            }
            else
            {
                int sum1,sum2 = 0;
                int colorPre  = ele->pre->data->color;
                int colorNext = ele->next->data->color;
                int cnt = 2;
                DCListElmt *pe = ele->pre;
                DCListElmt *ne = ele->next;
                while(pe->pre->data->color != colorPre)
                {
                    pe = pe->pre;
                    cnt += 1;
                }
                sum1 = numSum(list,ele,'p',cnt);

                cnt = 2;
                while(ne->next->data->color != colorNext)
                {
                    ne = ne->next;
                    cnt += 1;
                }
                sum2 = numSum(list,ele,'n',cnt);

                if (sum1 > sum2)
                {
                    ele->data->color = ele->pre->data->color;
                    ele->data->num = numSum(list,ele,'p',2);
                    dclist_rem(list,ele->pre,&data);
                    free(data);
                }
                else
                {
                    ele->data->color = ele->next->data->color;

                    ele->data->num = numSum(list,ele,'n',2);
                    deleteElmt(list,ele,'n',1);
                }

                ele = ele->next;
            }
        }

    }

    return 0;   
}

// int mergelist2(DCList *list){
//     // assert(list->size > 2);// if list->size <=2 , you can't merge
//     if (list->size == 1 || list->size == 2)
//     {
//         return 0;
//     }
//     // printf("dclist_size is %d\n", list->size);
//     DCListElmt *ele = list->head;
//     Tdata *data = (Tdata *)malloc(sizeof(Tdata));// temp for dclist_rem

//     while(!dclist_is_tail(ele))// here #element must be equal or larger than 3
//     {
//         if (ele->data->color != 3)
//         {
//             ele = ele->next;
//         }
//         else // neighbors of 'w' are diffrent
//         {

//             if (ele->next->next->data->color == 3)//here #element at least is 4
//             {

//                 int sum1 = ele->data->num + ele->pre->data->num
//                         + ele->pre->pre->data->num;
//                 int sum2 = ele->data->num 
//                         + ele->next->data->num
//                         + ele->next->next->data->num 
//                         + ele->next->next->next->data->num;
//                 if (sum1 > sum2)
//                 {
//                     ele->data->color = ele->pre->data->color;
//                     ele->data->num += ele->pre->data->num;
//                     dclist_rem(list,ele->pre,&data);
//                 }
//                 else
//                 {
//                     ele->data->color = ele->next->data->color;
//                     ele->data->num += ele->next->data->num 
//                                     + ele->next->next->data->num;

//                     dclist_rem(list,ele->next,&data);
//                     dclist_rem(list,ele->next,&data); // delete the next two element of ele                  
//                 }
//             }
//             else
//             {
//                 int sum1 = ele->data->num + ele->pre->data->num
//                             + ele->pre->pre->data->num;
//                 int sum2 = ele->data->num + ele->next->data->num
//                             + ele->next->next->data->num;

//                 if (sum1 > sum2)
//                 {
//                     ele->data->color = ele->pre->data->color;
//                     ele->data->num += ele->pre->data->num;
//                     dclist_rem(list,ele->pre,&data);
//                 }
//                 else
//                 {
//                     ele->data->color = ele->next->data->color;
//                     ele->data->num += ele->next->data->num;
//                     dclist_rem(list,ele->next,&data);               
//                 }                
//             }

//             ele = ele->next;
//         }
//     }

//     free(data);

//     return 0;   
// }

int* getSumSeries(DCList *list)
{
    assert(list->size > 0);
    int *ret = (int *)malloc(list->size*sizeof(int));
    DCListElmt *ele = list->head;

    if (list->size == 1)
    {
        ret[0] = list->head->data->num;
    }
    else
    {
        for (int i = 0; i < list->size; ++i)
        {
            ret[i] = ele->data->num + ele->pre->data->num;
            ele = ele->next;
        }
    }

    return ret;
}
int getMax(int *s, int size)
{
    int ret = s[0];

    if (size == 1)
    {
        return ret;
    }

    for (int i = 0; i < size - 1; ++i)
    {
        ret = (ret > s[i+1]) ? ret : s[i+1];
    }

    return ret;
}

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