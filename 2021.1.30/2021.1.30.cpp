#include<stdio.h>
#include<stdlib.h>
typedef char BTDataType;
typedef struct BinaryTreeNode
{
	BTDataType _data;
	struct BinaryTreeNode* _left;
	struct BinaryTreeNode* _right;
}BTNode;
//��ӽڵ�
BTNode* CreateNode(int x)
{
	BTNode* node = (BTNode*)malloc(sizeof(BTNode));
	node->_data = x;
	node->_left = NULL;
	node->_right = NULL;

	return node;
}
// ͨ��ǰ�����������"ABD##E#H##CF##G##"����������
BTNode* BinaryTreeCreate(BTDataType* a, int n, int* pi);
// ����������
void BinaryTreeDestory(BTNode** root);
// �������ڵ����
int BinaryTreeSize(BTNode* root) {
	if (root == NULL) {

		return 0;
	}
	else {
		return 1 + BinaryTreeSize(root->_left) + BinaryTreeSize(root->_right);
	}
}
// ������Ҷ�ӽڵ����
int BinaryTreeLeafSize(BTNode* root) {
	if (root == NULL) {
		return 0;
	}
	if (root->_left == NULL && root->_right == NULL) {
		return 1;
	}
	return BinaryTreeLeafSize(root->_left) + BinaryTreeLeafSize(root->_right);
}
// ��������k��ڵ����
int BinaryTreeLevelKSize(BTNode* root, int k);
// ����������ֵΪx�Ľڵ�
//BTNode* BinaryTreeFind(BTNode* root, BTDataType x) {
//	if (root == NULL) {
//		return;
//	}
//	printf("%c ", root);
//	BinaryTreeFind(roo)
//
//
//}
// ������ǰ�����
void BinaryTreePrevOrder(BTNode* root) {

	if (root == NULL) {
		return;
	}
	printf("%c ", root->_data);
	BinaryTreePrevOrder(root->_left);
	BinaryTreePrevOrder(root->_right);
}
// �������������
void BinaryTreeInOrder(BTNode* root) {
	if (root == NULL) {
		return;
	}

	BinaryTreeInOrder(root->_left);
	printf("%c ", root->_data);
	BinaryTreeInOrder(root->_right);

}
// �������������
void BinaryTreePostOrder(BTNode* root) {
	if (root == NULL) {
		return;
	}

	BinaryTreePostOrder(root->_left);
	BinaryTreePostOrder(root->_right);
	printf("%c ", root->_data);

}
// �������
void BinaryTreeLevelOrder(BTNode* root);
// �ж϶������Ƿ�����ȫ������
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
	printf("TreeLeafSize��%d", a);
}
int main() {

	tree();
	return 0;
}