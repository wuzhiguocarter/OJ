// LeetCode: 83. Remove Duplicates from Sorted List
// Given a sorted linked list, delete all duplicates such that each element appear only once.

// For example,
// Given 1->1->2, return 1->2.
// Given 1->1->2->3->3, return 1->2->3.
#include <map>
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
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
                    while(cnt++ < node_map[pNode->val]-1){
                        pNodeTemp = pNodeTemp->next;
                    }
                    pNode_pre->next = pNodeTemp;
                    pNode = pNodeTemp;
                }
                // 链表头部有重复
                else{
                    int cnt = 0;
                    ListNode *pNodeTemp = pNode;
                    while(cnt++ < node_map[pNode->val]-1){
                        pNodeTemp = pNodeTemp->next;
                    }
                    head = pNodeTemp;
                    pNode_pre = NULL;
                    pNode = pNodeTemp;
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
    ListNode* deleteDuplicates(ListNode* head) {
         if( !head || !head->next) return head;
        int val = head->val;
        ListNode* p = head->next;
        // 当前节点值与下个节点值不相等
        if (p->val != val) {
            head->next = deleteDuplicates(p);
            return head;
        } 
        // 当前节点值与下个节点值相等
        else {
            while (p != NULL && p->val == val){
                head = p;
                p = p->next;
            } 
            head->next = deleteDuplicates(p);
            return head;
        }
    }
};