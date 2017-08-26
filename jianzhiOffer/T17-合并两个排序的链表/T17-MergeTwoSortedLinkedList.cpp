#include <stdio.h>

struct ListNode {
	int val;
	struct ListNode *next;
	ListNode(int x) :
			val(x), next(NULL) {
	}
};

ListNode *ListNodePush(ListNode *list, int x){
	if(list != NULL){
		ListNode *newNode = new ListNode(x);
		list->next = newNode;
		return newNode;
	}
}

class Solution {
public:
  // 非递归方法
    ListNode* Merge(ListNode* pHead1, ListNode* pHead2){
      if (NULL == pHead1) return pHead2;
      if (NULL == pHead2) return pHead1;
      ListNode *pMergeHead = pHead1->val < pHead2->val ? pHead1 : pHead2;
      // 对两个链表进行遍历的指针
      ListNode *p1 = pHead1, *p2 = pHead2;
      while(!(p1 == NULL || p2 == NULL)){
          if(p1->val <  p2->val){
            // 用临时变量保存将来更新的指针
              ListNode *temp = p1;
              p1 = p1->next;
              temp->next = p2;
          }
          else{
              ListNode *temp = p2;
              p2 = p2->next;
              temp->next = p1;
          }
      }
      return pMergeHead;
    }
};

class Solution {
public:
	// 递归方法
    ListNode* Merge(ListNode* pHead1, ListNode* pHead2){
    	// base case
    	if (NULL == pHead1) return pHead2;
    	if (NULL == pHead2) return pHead1;


      // recursive case
    	// 递归变量
    	ListNode *pMergeHead = NULL;

    	// 递归分支
    	if (pHead1->val < pHead2->val)
    	{
    		// 递归内容
    		pMergeHead = pHead1;
    		pMergeHead->next = Merge(pHead1->next, pHead2);
    	}
    	else{
    		pMergeHead = pHead2;
    		pMergeHead->next = Merge(pHead1, pHead2->next);
    	}
      return pMergeHead;
    }
};

int main(int argc, char const *argv[])
{
	ListNode *list1 = new ListNode(1);
	ListNodePush(ListNodePush(list1,3),5);
	ListNode *list2 = new ListNode(2);
	ListNodePush(ListNodePush(list2,4),6);

	Solution s;
	s.Merge(list1,list2);

	return 0;
}