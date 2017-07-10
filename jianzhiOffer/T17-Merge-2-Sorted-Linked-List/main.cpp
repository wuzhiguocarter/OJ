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
	// 递归方法
    ListNode* Merge(ListNode* pHead1, ListNode* pHead2){
    	// 终止条件
    	if (NULL == pHead1) return pHead2;
    	if (NULL == pHead2) return pHead1;

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

    }
    // 非递归方法
   //  ListNode* Merge(ListNode* pHead1, ListNode* pHead2)
   //  {
   //      // 边界条件
   //      if(pHead1 == NULL) return pHead2;
   //      if(pHead2 == NULL) return pHead1;
        
   //      ListNode *p1 = pHead1;
   //      ListNode *p2 = pHead2;
   //      ListNode *pdummyNode = new ListNode(0);
   //      ListNode *mergeCurrent = pdummyNode;
   //      while(p1 != NULL && p2 != NULL){
   //          printf("p1->val = %d, p2->val = %d\n", p1->val, p2->val);
   //          if(p1->val < p2->val){
   //              ListNode *temp = p1->next;
   //              mergeCurrent->next = p1;
   //              mergeCurrent = p1;
			// 	p1 = temp; // p1 point to the next node of list 1
			// 	if (p1 == NULL)
			// 	{
			// 		mergeCurrent->next = p2;
			// 		return pHead1->val < pHead2->val ? pHead1 : pHead2;
			// 	}			
   //          }
   //          else{
   //              ListNode *temp = p2->next;
   //              mergeCurrent->next = p2;
   //              mergeCurrent = p2;
			// 	p2 = temp;
			// 	if (p2 == NULL)
			// 	{
			// 		mergeCurrent->next = p1;
			// 		return pHead1->val < pHead2->val ? pHead1 : pHead2;
			// 	}	
   //          }
   //      }
   //      //printf("p1->val = %d, p2->val = %d", p1->val, p2->val);
   //      delete pdummyNode;
   //      return pHead1->val < pHead2->val ? pHead1 : pHead2;
  	// }
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