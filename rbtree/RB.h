#pragma once
#include<iostream>
#include<assert.h>
#include<queue>
using namespace std;
enum Color{
	RED,
	BLOCK,
};
template<class K,class V>
struct TreeNode {
	pair<K, V> val;
	TreeNode<K, V>*left;
	TreeNode<K, V>* right;
	TreeNode<K, V>* parent;
	Color _c;
	TreeNode(const pair<K, V>_val) :
		val(_val), left(NULL), right(NULL),
		parent(NULL), _c(RED) {}
};
template<class K, class V>
class RBTree {
	typedef TreeNode< K,  V> Node;
private:
	Node* head;
public:
	void Mid() {
		Node* root = head;
		queue<Node*>q;
		q.push(root);
			vector<vector<Node*>> v;
			while (!q.empty()) {
				vector<Node*> vm;
				int size = q.size();
				while (size--) {
					Node* node = q.front();
					q.pop();
					vm.push_back(node);
					if (node->left) {
						q.push(node->left);

					}
					if (node->right) {
						q.push(node->right);
					}
				}
				if (!vm.empty()) {
					v.push_back(vm);
				}
			}
			for (int i = 0;i < v.size();i++) {
				for (int j = 0;j < v[i].size();j++) {
					cout << "[" << v[i][j]->val.first << "," << v[i][j]->_c << "] ";
				}
				cout << endl;
			}

		
	}
	template<class K, class V>
	void Insert(const pair<K, V> kv) {
		if (head == NULL) {
			head = new Node(kv);
			head->_c = BLOCK;
		}
		Node* root=head;
		Node* parent = NULL;
		while (root) {
			parent = root;
			if (root->val.first > kv.first) {
				root=root->left;
			}
			else if(root->val.first<kv.first) {
				root = root->right;
			}
			else {
				//相同替换value值
				root->val.second = kv.second;
				return;
			}
		}
		//找到要插入节点的位置
		root = new Node(kv);
		if (parent->val.first < kv.first) {
			parent->right = root;
		}
		else {
			parent->left = root;
		}
		root->parent = parent;

		//更新红黑树的结构
		//父节点存在并为红色 ---父节点如果为黑色就不会影响红黑树的结构
		while (parent && parent->_c == RED) {//父节点存在就一定存在祖父节点
			Node* gparent = parent->parent;//祖父节点  
			//4.1 父节点为祖父节点的左节点
			if (gparent->left == parent) {
				//4.1.1 叔叔节点存在并且为红色
				Node* unode = gparent->right;
				if (unode && unode->_c == RED) {
					//插入节点存在双红节点
					unode->_c = parent->_c = BLOCK;
					//祖父节点改为红色
					gparent->_c = RED;


					//循环更新祖宗节点颜色
					root = gparent;
					parent = root->parent;

				}//4.1.2  叔叔节点不存在 

				else {
					//4.1.2.1 插入节点在父节点的左侧  
					if (root == parent->left) {
						//父节点变为黑色 祖父节点设为红色
						//右旋
						parent->_c = BLOCK;
						gparent->_c = RED;

						//左旋
						LL(gparent);

					}//4.2.2 插入节点为父节点的右子节点
					else if (root == parent->right) {
						//先左旋
						LL(parent);
						//右旋
						RR(gparent);
						//变色
						root->_c = BLOCK;
						gparent->_c = RED;
						
					}
					break;

				}
			}//4.3 父节点插入到祖父节点的的右侧
			else if (gparent->right == parent) {
				//4.3.1 叔叔节点存在并且为红
				Node* unode = gparent->left;
				if (unode && unode->_c == RED) {
					//插入节点存在双红节点
					unode->_c = parent->_c = BLOCK;
					//祖父节点改为红色
					gparent->_c = RED;


					//循环更新祖宗节点颜色
					root = gparent;
					parent = root->parent;
				
				}//4.3.2  叔叔节点不存在
				else {
					//4.3.2.1 插入节点在父节点的右侧
					if (root == parent->right) {
						//变色 父节点为黑
						parent->_c = BLOCK;
						gparent->_c = RED;
					
						LL(gparent);
					}// 4.3.2.2 插入节点在父节点的左侧
					else {
						RR(parent);
						LL(gparent);
						gparent->_c = RED;
						root->_c = BLOCK;
						
					}
					
						break;
				}
			
			}
			

		}
		//根节点设为黑色
		head->_c = BLOCK;

	}
	//左旋
	void LL(Node*root) {
		Node* right = root->right;
		Node* noderl = right->left;

		Node* parent = root->parent;

		root->right = noderl;
		if (noderl) {
			noderl->parent = root;
		}

		right->left = root;
		root->parent = right;
		if (parent == NULL) {
			//跟节点
			head = right;
			head->parent = NULL;
		}
		else {
			if (parent->left == root) {
				parent->left = right;
			}
			else {
				parent->right = right;
			}
			right->parent = parent;
		
		}

	}
	//右旋
	void RR(Node* root) {
		Node* left = root->left;
		Node* nodelr = left->right;

		Node* parent = root->parent;

		root->left = nodelr;
		if (nodelr) {
			nodelr->parent = root;
		}

		left->right = root;
		root->parent = left;
		if (parent == NULL) {
			//跟节点
			head = left;
			left->parent = NULL;
		}
		else {
			if (parent->left == root) {
				parent->left = left;
			}
			else {
				parent->right = left;
			}
			left->parent = parent;

		}

	}

};

