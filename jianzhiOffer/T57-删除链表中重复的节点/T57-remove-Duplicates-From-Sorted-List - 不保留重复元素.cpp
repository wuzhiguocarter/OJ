// LeetCode: 82. Remove Duplicates from Sorted List II
// 
// 在一个排序的链表中，存在重复的结点，请删除该链表中重复的结点，
// 重复的结点不保留，返回链表头指针。 
// 例如，链表1->2->3->3->4->4->5 处理后为 1->2->5
#include <map>

struct ListNode {
    int val;
    struct ListNode *next;
    ListNode(int x) :
        val(x), next(NULL) {
    }
};
// 非递归解法
class Solution {
public:
    ListNode* deleteDuplication(ListNode* head) {
        if(head == nullptr) return nullptr;
        ListNode *ret = head;
        ListNode *pNode = head;
        map<int, int> node_map;
        while(pNode != nullptr){
        	if(node_map.find(pNode->val) != node_map.end()){
        		node_map[pNode->val]++;
        	}
        	else{
        		node_map[pNode->val] = 1;
        	}
        	pNode = pNode->next;
        }
        pNode = head;
        ListNode *pNode_pre = NULL;
        while(pNode != nullptr){
        	// 遇到重复节点
        	if(node_map[pNode->val] > 1){
        		// 链表中部有重复
        		if(pNode != head){
        			int cnt = 0;
                    ListNode *pNodeTemp = pNode;
        			while(cnt++ < node_map[pNode->val]){
        				pNodeTemp = pNode->next;
        			}
        			pNode_pre->next = pNodeTemp;
                    pNode = pNode_pre;
        		}
        		// 链表头部有重复
        		else{
        			int cnt = 0;
                    ListNode *pNodeTemp = pNode;
        			while(cnt++ < node_map[pNode->val]){
        				pNodeTemp = pNodeTemp->next;
        			}
        			pNode_pre = NULL;
        			head = pNodeTemp;
        		}
        	}
    		pNode_pre = pNode;
    		pNode = pNode->next;
        }
        return head;
    }
};

// 递归解法
class Solution {
public:
    ListNode* deleteDuplication(ListNode* head)
    {
        if( !head || !head->next) return head;
        int val = head->val;
        ListNode* p = head->next;
        // 当前节点值与下个节点值不相等
        if (p->val != val) {
            head->next = deleteDuplication(p);
            return head;
        } 
        // 当前节点值与下个节点值相等
        else {
            while (p != NULL && p->val == val) 
            	p = p->next;
            return deleteDuplication(p);
        }
    }
};