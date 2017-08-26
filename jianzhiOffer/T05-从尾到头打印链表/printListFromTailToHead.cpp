/**
*  struct ListNode {
*        int val;
*        struct ListNode *next;
*        ListNode(int x) :
*              val(x), next(NULL) {
*        }
*  };
*/
class Solution {
public:
    // 非递归解法
    vector<int> printListFromTailToHead(ListNode* head) {
        ListNode *headTemp = head;
        vector<int> ret;
        // 输入检查
        if(headTemp == NULL) return ret;

        // 遍历链表，将所有链表元素存到栈里
        stack<int> stk;
        while(headTemp != NULL){
            stk.push(headTemp->val);
            headTemp = headTemp->next;
        }
        // 依次取栈顶元素，并弹出直到栈空
        while(!stk.empty()){
            ret.push_back(stk.top());
            stk.pop();
        }
        return ret;
    }
};

class Solution {
private:
    vector<int> ret;
public:
    // 递归解法
    vector<int> printListFromTailToHead(ListNode* head) {
        // vector<int> ret; 
        //思考为什么ret不能放这里？
        // 因为如果ret放到函数内层, 每次递归调用该函数，ret只能收集一个节点的值
        if(head != NULL){
            if(head->next != NULL ){
                printListFromTailToHead(head->next);
            }
            ret.push_back(head->val);
        }
        return ret;
    }
};