#include<stdio.h>
#include<stdlib.h>
typedef char BTDataType;
typedef struct BinaryTreeNode
{
	BTDataType _data;
	struct BinaryTreeNode* _left;
	struct BinaryTreeNode* _right;
}BTNode;
//添加节点
BTNode* CreateNode(int x)
{
	BTNode* node = (BTNode*)malloc(sizeof(BTNode));
	node->_data = x;
	node->_left = NULL;
	node->_right = NULL;

	return node;
}
// 通过前序遍历的数组"ABD##E#H##CF##G##"构建二叉树
BTNode* BinaryTreeCreate(BTDataType* a, int n, int* pi);
// 二叉树销毁
void BinaryTreeDestory(BTNode** root);
// 二叉树节点个数
int BinaryTreeSize(BTNode* root) {
	if (root == NULL) {

		return 0;
	}
	else {
		return 1 + BinaryTreeSize(root->_left) + BinaryTreeSize(root->_right);
	}
}
// 二叉树叶子节点个数
int BinaryTreeLeafSize(BTNode* root) {
	if (root == NULL) {
		return 0;
	}
	if (root->_left == NULL && root->_right == NULL) {
		return 1;
	}
	return BinaryTreeLeafSize(root->_left) + BinaryTreeLeafSize(root->_right);
}
// 二叉树第k层节点个数
int BinaryTreeLevelKSize(BTNode* root, int k);
// 二叉树查找值为x的节点
//BTNode* BinaryTreeFind(BTNode* root, BTDataType x) {
//	if (root == NULL) {
//		return;
//	}
//	printf("%c ", root);
//	BinaryTreeFind(roo)
//
//
//}
// 二叉树前序遍历
void BinaryTreePrevOrder(BTNode* root) {

	if (root == NULL) {
		return;
	}
	printf("%c ", root->_data);
	BinaryTreePrevOrder(root->_left);
	BinaryTreePrevOrder(root->_right);
}
// 二叉树中序遍历
void BinaryTreeInOrder(BTNode* root) {
	if (root == NULL) {
		return;
	}

	BinaryTreeInOrder(root->_left);
	printf("%c ", root->_data);
	BinaryTreeInOrder(root->_right);

}
// 二叉树后序遍历
void BinaryTreePostOrder(BTNode* root) {
	if (root == NULL) {
		return;
	}

	BinaryTreePostOrder(root->_left);
	BinaryTreePostOrder(root->_right);
	printf("%c ", root->_data);

}
// 层序遍历
void BinaryTreeLevelOrder(BTNode* root);
// 判断二叉树是否是完全二叉树
int BinaryTreeComplete(BTNode* root);
void tree() {

	BTNode* A = CreateNode('A');
	BTNode* B = CreateNode('B');
	BTNode* C = CreateNode('C');
	BTNode* D = CreateNode('D');
	BTNode* E = CreateNode('E');
	A->_left = B;
	A->_right = C;
	B->_left = D;
	B->_right = E;
	BinaryTreePrevOrder(A);
	printf("\n");
	BinaryTreePrevOrder(B);
	printf("\n");
	BinaryTreeInOrder(A);
	printf("\n");
	BinaryTreePostOrder(A);
	printf("\n");
	int a= BinaryTreeSize(A);
	printf("TreeLeafSize：%d", a);
}
int main() {

	tree();
	return 0;
}