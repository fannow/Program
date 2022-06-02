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
		//当前节点为NULL就插入节点
		if ((*root) == NULL) {
			(*root) = new STree(val);
			return;
		}
		//比当前节点小就递归到左子树
		//比当前节点大就递归到右子树
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
	//删除节点
	bool del(STree** root, int val) {
		//当前节点为NULL就插入节点
		if ((*root) == NULL) {
			return false;
		}
		//比当前节点小就递归到左子树
		//比当前节点大就递归到右子树
		if (val > (*root)->val) {
			del(&(*root)->right, val);
		}
		else if (val < (*root)->val) {
			del(&(*root)->left, val);

		}
		else {
			//找到当前节点

			if ((*root)->left && (*root)->right) {
				STree* rnode = (*root)->right;//右子树的根节点
				//右子树的根节点存在左子树   --最左节点节点充当
				if (rnode->left) {
					while (rnode->left) {
						rnode=rnode->left;
					}
					//替换值
					(*root)->val=rnode->val;
					//递归删除右子树根节点的最左节点
					del(&((*root)->right), rnode->val);
				}
			}	//右子树的根节点不存在左子树  右子树根节点充当当前节点
			else {
				//右子树不为NULL
				if ((*root)->right) {
					//取右子树的最左节点
					STree* left = (*root)->right;
					while (left->left) {
						left = left->left;
					}
					(*root)->val = left->val;
					//递归删除右子树子树根节点的最左节点
					del(&((*root)->right), left->val);
				}//左子树不为NULL
				else if ((*root)->left) {
					//左子树的最右节点
					STree* left = (*root)->left;
					while (left->right) {
						left = left->right;
					}
					(*root)->val = left->val;
					//递归删除左子树根节点的最右节点
					del(&((*root)->left), left->val);
				}
				else {
					//叶子节点直接删除
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