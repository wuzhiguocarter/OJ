#include <iostream>
#include <vector>
#include <stack>
#include <queue>

using namespace std;

struct TreeNode{
	int val;
	struct TreeNode* left;
	struct TreeNode* right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
private:
	vector<int> ret;
public:
	// ============================================================================= //
	// 二叉树的构建
	// ============================================================================= //
	// 扩展二叉树的先序序列构建二叉树
	TreeNode* buildTreeExtPreorder(const vector<string> &epre){

	}
	// 由 中序遍历序列  和 前序遍历序列 构建二叉树
	// 辅助函数
	template<typename BidiIt>
	TreeNode* buildTree_IN_PRE(BidiIt in_first, BidiIt in_last,
						BidiIt pre_first, BidiIt pre_last)
	{
		if(in_first == in_last || pre_first == pre_last) return nullptr;
		// 从前序遍历序列取根节点
		const auto val = *pre_first;
		TreeNode* root = new TreeNode(*pre_first);
		// 在中序遍历序列中查找根节点所在位置
		auto in_root_pos = find(in_first, in_last, val);
		// 计算左子树的遍历序列的长度
		auto left_size = distance(in_first, in_root_pos);
		// 找到前序遍历序列中左右子树的分隔点
		auto pre_left_last = next(pre_first+1, left_size);
		// 递归创建左右子树
		root->left = buildTree_IN_PRE(in_first, in_root_pos, 
							next(pre_first), pre_left_last);
		root->right = buildTree_IN_PRE(next(in_root_pos),in_last, 
							pre_left_last, pre_last);
		return root;
	}
    TreeNode* buildTree_in_pre(vector<int> &inorder,vector<int> preorder) {
		return buildTree_IN_PRE(begin(inorder), end(inorder),
						 begin(preorder), end(preorder));
    }

	// 由 中序遍历序列  和 后序遍历序列 构建二叉树
	// 辅助函数
	template<typename BidiIt>
	TreeNode* buildTree_IN_POST(BidiIt in_first, BidiIt in_last,
						BidiIt post_first, BidiIt post_last)
	{
		if(in_first == in_last || post_first == post_last) return nullptr;
		// 从后序遍历序列取根节点
		const auto val = *prev(post_last);
		TreeNode* root = new TreeNode(val);
		// 在中序遍历序列中查找根节点所在位置
		auto in_root_pos = find(in_first, in_last, val);
		// 计算左子树的遍历序列的长度
		auto left_size = distance(in_first, in_root_pos);
		// 找到后序遍历序列中左右子树的分隔点
		auto post_left_last = next(post_first, left_size);
		// 递归创建左右子树
		root->left = buildTree_IN_POST(in_first, in_root_pos, 
							post_first, post_left_last);
		root->right = buildTree_IN_POST(next(in_root_pos),in_last, 
							post_left_last, pre(post_last));
		return root;
	}
    TreeNode* buildTree_in_post(vector<int> &inorder,vector<int> postorder) {
		return buildTree_IN_POST(begin(inorder), end(inorder),
						 begin(postorder), end(postorder));
    }

    // get方法: 求树或节点的高度
    int Height(TreeNode *root){

    }
	// ============================================================================= //
	// 二叉树的遍历
	// ============================================================================= //
    // 获取二叉树的 前序遍历序列
    vector<int> preOrder_recursive(TreeNode *root){
    	
    	if(root == NULL){ 
    		ret.clear();
    		return ret;
    	}
    	ret.push_back(root->val);
    	preOrder_recursive(root->left);
    	preOrder_recursive(root->right);
    	return ret;
    }
    // 使用栈
    // 时间复杂度O(n)，空间复杂度O(n)
    vector<int> preOrder_iterative(TreeNode *root){
    	vector<int> result;
    	stack<const TreeNode*> s;
    	if(root != nullptr)  s.push(root);

    	while(!s.empty()){
    		const TreeNode *p = s.top();
    		s.pop();
    		result.push_back(p->val);

    		if(p->right != nullptr) s.push(p->right);
    		if(p->left != nullptr) s.push(p->left);
    	}
    	return result;
    }
    // Morris先序遍历
    vector<int> preOrder_iterative_Morris(TreeNode *root){

    }

    // 获取二叉树的 中序遍历序列
    vector<int> inOrder_recursive(TreeNode *root){
    	if(root == NULL){ 
    		ret.clear();
    		return ret;
    	}
    	preOrder_recursive(root->left);
    	ret.push_back(root->val);
    	preOrder_recursive(root->right);
    	return ret;
    }
    vector<int> inOrder_iterative(TreeNode *root){
    	vector<int> result;
    	stack<const TreeNode*> s;
    	const TreeNode *p = root;

    	// 终止条件：栈s空且p为空指针
    	while(!s.empty() || p!= nullptr){
    		// 递归将左子树节点压栈，直到遇到叶节点
    		if(p != nullptr){
    			s.push(p);
    			p = p->left;
    		}
    		else{
    			// 取出栈顶元素，弹出，压入result尾部
    			p = s.top();
    			s.pop();
    			result.push_back(p->val);
    			// 出栈时将p更新为右子树，
    			// 若右子树为空，继续执行下一次else分支
    			// 否则，执行if分支
    			p = p->right;
    		}
    	}
    	return result;
    }

    // 获取二叉树的 后序遍历序列
    vector<int> postOrder_recursive(TreeNode *root){
    	
    	if(root == NULL){ 
    		ret.clear();
    		return ret;
    	}
    	preOrder_recursive(root->left);
    	preOrder_recursive(root->right);
    	ret.push_back(root->val);
    	return ret;
    }

    vector<int> postOrder_iterative(TreeNode *root){
    	vector<int> result;
    	stack<const TreeNode*> s;
    	// q刚刚访问的节点
    	const TreeNode *p = root, *q = nullptr;
    	while(!s.empty() || p != nullptr){
    		if( p != nullptr){
    			s.push(p);
    			p = p->left;
    		}
    		else{
    			p = s.top();
    			// 右子树存在 且 没有被访问
    			if(p->right != nullptr && p->right != q){
    				p = p->right;
    			}
    			// 右子树不存在 或者 右子树已经被访问
    			else{
    				result.push_back(p->val);
    				s.pop();
    				q = p;
    			}
    		}
    	}
		return result;
	}
    // 层序遍历 递归版
    // 时间复杂度O(n)，空间复杂度O(n)
    // 辅助函数
    void traverse(TreeNode *root, size_t level, vector<vector<int> > &result){
    	if(root == nullptr) return;
    	// 若
    	if(level > result.size())
    		result.push_back(vector<int>()); // 创建新的一层 
    	result[level-1].push_back(root->val);
    	traverse(root->left, level+1, result);
    	traverse(root->right, level+1, result);
    }
    vector<vector<int> > levelOrder_recursive(TreeNode *root){
    	vector<vector<int> > result;
    	traverse(root, 1, result);
    	return result;
    }
    // 层序遍历，非递归
    // 时间复杂度O(n)，空间复杂度O(1)
    vector<vector<int> >  levelOrder_iterative(TreeNode *root){
    	vector<vector<int> > result;
    	queue<TreeNode *> current_que,next_que;

    	if(root == nullptr){
    		return result;
    	}
    	else{
    		current_que.push(root);
    	}
    	while(!current_que.empty()){
    		vector<int> layer;
			while(!current_que.empty()){
				// 出队
				TreeNode *node = current_que.front();
				current_que.pop();
				// 收集当前层的节点值序列
				layer.push_back(node->val);
				// 下层节点入next_que队列
				if(node->left != nullptr) next_que.push(node->left);
				if(node->right != nullptr) next_que.push(node->right);
			}
			// 将收集的整个一层的节点值序列放入result
			result.push_back(layer);
			// current_que所有元素均已出队，交换下一层访问队列置换为当前访问队列
			swap(current_que,next_que);
		}
    	return result;
    }
};