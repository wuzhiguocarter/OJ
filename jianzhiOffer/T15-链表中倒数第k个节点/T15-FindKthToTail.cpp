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
    ListNode* FindKthToTail(ListNode* head, unsigned int k) {
    	if(head == nullptr || k <= 0) return nullptr;
    	ListNode *p1 = head, *p2 = head;
    	int cnt = 1;
    	while(cnt++ < k){
    		if(p2->next == nullptr) // 节点数少于k
    			return nullptr;
    		p2 = p2->next;
    	}
    	while(p2->next != nullptr){
    		p1 = p1->next;
    		p2 = p2->next;
    	}
    	return p1;
    }
};