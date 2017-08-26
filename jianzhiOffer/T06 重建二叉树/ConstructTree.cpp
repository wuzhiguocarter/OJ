#include <exception>
#include <iostream>

using namespace std;

struct BinaryTreeNode{
	int m_value;
	BinaryTreeNode* m_pLeft;
	BinaryTreeNode* m_pRight;
};
class Solution{
public:
	BinaryTreeNode * ConstructTree(int *preorder, int *inorder, size_t length){
		if(preorder == NULL || inorder == NULL || length <=0) return NULL;

		return ConstructRecursive(preorder, preorder+length-1,
		 inorder, inorder+length-1);
	}
private:
	BinaryTreeNode *ConstructRecursive(int *preorder_start, int *preorder_end, 
		 int *inorder_start, int *inorder_end){

		// 在前序遍历序列中查找根节点
		BinaryTreeNode *root = new BinaryTreeNode();
		root->m_value = preorder_start[0];
		root->m_pLeft = NULL;
		root->m_pRight = NULL;

		if(preorder_start == preorder_end){
			if(inorder_start == inorder_end && *preorder_start == *inorder_start){
				return root;
			}
			else{
				// throw std::logic_error("Invalid Input!");
				return NULL;
			}
		}

		// 在中序遍历序列中查找根节点
		int *inorder_root = inorder_start;
		while(inorder_root <= inorder_end && *inorder_root != root->m_value){
			inorder_root++;
		}
		if(inorder_root == inorder_end && *inorder_root != root->m_value){
			// throw std::logic_error("Invalid Input!");
			return NULL;
		}

		int leftPreorder_end_offset = inorder_root - inorder_start;
		int *leftPreorder_end = preorder_start + leftPreorder_end_offset;
		// 构建左子树
		if(leftPreorder_end_offset > 0){
			root->m_pLeft = ConstructRecursive(preorder_start+1,leftPreorder_end,
				inorder_start,inorder_root-1);
		}
		// 构建右子树
		if(leftPreorder_end_offset < preorder_end - preorder_start){
			root->m_pRight = ConstructRecursive(leftPreorder_end+1,preorder_end,
				inorder_root+1,inorder_end);
		}
		return root;
	}
};

int main(int argc, char const *argv[])
{
	
	int preorder[] = {1,2,4,7,3,5,6,8};
	int inorder[]  = {4,7,2,1,5,3,8,6};
	Solution s;
	s.ConstructTree(preorder,inorder,sizeof(preorder));
	return 0;
}