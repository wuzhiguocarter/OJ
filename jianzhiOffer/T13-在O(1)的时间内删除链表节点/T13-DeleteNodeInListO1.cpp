struct ListNode
{
	int var;
	ListNode *next;	
};

ListNode* DeleteNode(ListNode *head, ListNode *pTobeDeleted){
	// 如果表为空或者仅有一个节点或者删除的是空节点，则返回nullptr
	if(head == nullptr || head->next = nullptr || pTobeDeleted == nullptr) return nullptr;
	
	// 至少有两个节点,且pTobeDeleted不为nullptr
	ListNode *pTobeDeleted_next = pTobeDeleted->next;
	// 如果删除的是首节点
	if(pTobeDeleted == head){
		ListNode *ret = head->next;
		delete head;
		head = nullptr;
		return ret;
	}
	// 如果删除的是尾节点
	if(pTobeDeleted_next = NULL){
		ListNode *pNode = head;
		while(pNode->next != pTobeDeleted){
			pNode = pNode->next;
		}
		pNode->next = pTobeDeleted->next;
		delete pTobeDeleted;
		pTobeDeleted = NULL;
	}
	// 如果删除的是中间节点
	pTobeDeleted->var = pTobeDeleted_next->var;
	pTobeDeleted->next = pTobeDeleted_next->next;
	delete pTobeDeleted_next;
	pTobeDeleted_next = nullptr;

	return head;
}