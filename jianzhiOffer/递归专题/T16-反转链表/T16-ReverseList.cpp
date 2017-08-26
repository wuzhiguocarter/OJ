/*
struct ListNode {
	int val;
	struct ListNode *next;
	ListNode(int x) :
			val(x), next(NULL) {
	}
};*/
class Solution {
public:
	// 非递归解法 从前到后反转
    ListNode* ReverseList(ListNode* pHead) {
    	if(pHead == nullptr || pHead->next == nullptr) return pHead;
        ListNode *pPre = NULL;
        ListNode *pCurrent = pHead;
        while(pCurrent != NULL){
        	ListNode *pNext = pCurrent->next;
            pCurrent->next = pPre;
            pPre = pCurrent;
            pCurrent = pNext;
        }
        return pPre;
    }
    // 递归解法 从后到前反转
    ListNode* ReverseList(ListNode* pHead) {
    	if(pHead == nullptr || pHead->next == nullptr) return pHead;
    	ListNode *p = ReverseList(pHead->next);
    	pHead->next->next = pHead;
    	pHead->next = nullptr;
    	return p;// p从调用的最里层到最最外层值始终没变，为最后一个节点的地址
    }
};