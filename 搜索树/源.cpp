#include<iostream>
#include<vector>
using namespace std;

class STree {
private:
	int val;
	STree* left;
	STree* right;
public:
	STree(int _val) :
		val(_val), left(NULL), right(NULL)
	{}
	STree() {}
	void Insert(STree** root, int val) {
		//��ǰ�ڵ�ΪNULL�Ͳ���ڵ�
		if ((*root) == NULL) {
			(*root) = new STree(val);
			return;
		}
		//�ȵ�ǰ�ڵ�С�͵ݹ鵽������
		//�ȵ�ǰ�ڵ��͵ݹ鵽������
		if (val > (*root)->val) {
			Insert(&(*root)->right, val);
		}
		else if (val <= (*root)->val) {
			Insert(&(*root)->left, val);

		}
	}

	void create_stree(STree** root, vector<int> v) {
		for (int i = 0;i < v.size();i++) {
			(*root)->Insert(&(*root), v[i]);
		}

	}
	//ɾ���ڵ�
	bool del(STree** root, int val) {
		//��ǰ�ڵ�ΪNULL�Ͳ���ڵ�
		if ((*root) == NULL) {
			return false;
		}
		//�ȵ�ǰ�ڵ�С�͵ݹ鵽������
		//�ȵ�ǰ�ڵ��͵ݹ鵽������
		if (val > (*root)->val) {
			del(&(*root)->right, val);
		}
		else if (val < (*root)->val) {
			del(&(*root)->left, val);

		}
		else {
			//�ҵ���ǰ�ڵ�

			if ((*root)->left && (*root)->right) {
				STree* rnode = (*root)->right;//�������ĸ��ڵ�
				//�������ĸ��ڵ����������   --����ڵ�ڵ�䵱
				if (rnode->left) {
					while (rnode->left) {
						rnode=rnode->left;
					}
					//�滻ֵ
					(*root)->val=rnode->val;
					//�ݹ�ɾ�����������ڵ������ڵ�
					del(&((*root)->right), rnode->val);
				}
			}	//�������ĸ��ڵ㲻����������  ���������ڵ�䵱��ǰ�ڵ�
			else {
				//��������ΪNULL
				if ((*root)->right) {
					//ȡ������������ڵ�
					STree* left = (*root)->right;
					while (left->left) {
						left = left->left;
					}
					(*root)->val = left->val;
					//�ݹ�ɾ���������������ڵ������ڵ�
					del(&((*root)->right), left->val);
				}//��������ΪNULL
				else if ((*root)->left) {
					//�����������ҽڵ�
					STree* left = (*root)->left;
					while (left->right) {
						left = left->right;
					}
					(*root)->val = left->val;
					//�ݹ�ɾ�����������ڵ�����ҽڵ�
					del(&((*root)->left), left->val);
				}
				else {
					//Ҷ�ӽڵ�ֱ��ɾ��
					delete (*root);
					(*root) = NULL;
				}


			}
		}
	}
	int depth(STree*root) {
		if (root == NULL) {
			return 0;
		}
		int left = depth(root->left);
		int right = depth(root->right);
		return max(left, right) + 1;
		
	}

};
int main() {

	STree *r=NULL;
	
	r->create_stree(&r, { 61, 87, 59,60, 47, 35, 73, 51, 98, 37, 93 });

	cout<<r->depth(r);
}