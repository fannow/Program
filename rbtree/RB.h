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
				//��ͬ�滻valueֵ
				root->val.second = kv.second;
				return;
			}
		}
		//�ҵ�Ҫ����ڵ��λ��
		root = new Node(kv);
		if (parent->val.first < kv.first) {
			parent->right = root;
		}
		else {
			parent->left = root;
		}
		root->parent = parent;

		//���º�����Ľṹ
		//���ڵ���ڲ�Ϊ��ɫ ---���ڵ����Ϊ��ɫ�Ͳ���Ӱ�������Ľṹ
		while (parent && parent->_c == RED) {//���ڵ���ھ�һ�������游�ڵ�
			Node* gparent = parent->parent;//�游�ڵ�  
			//4.1 ���ڵ�Ϊ�游�ڵ����ڵ�
			if (gparent->left == parent) {
				//4.1.1 ����ڵ���ڲ���Ϊ��ɫ
				Node* unode = gparent->right;
				if (unode && unode->_c == RED) {
					//����ڵ����˫��ڵ�
					unode->_c = parent->_c = BLOCK;
					//�游�ڵ��Ϊ��ɫ
					gparent->_c = RED;


					//ѭ���������ڽڵ���ɫ
					root = gparent;
					parent = root->parent;

				}//4.1.2  ����ڵ㲻���� 

				else {
					//4.1.2.1 ����ڵ��ڸ��ڵ�����  
					if (root == parent->left) {
						//���ڵ��Ϊ��ɫ �游�ڵ���Ϊ��ɫ
						//����
						parent->_c = BLOCK;
						gparent->_c = RED;

						//����
						LL(gparent);

					}//4.2.2 ����ڵ�Ϊ���ڵ�����ӽڵ�
					else if (root == parent->right) {
						//������
						LL(parent);
						//����
						RR(gparent);
						//��ɫ
						root->_c = BLOCK;
						gparent->_c = RED;
						
					}
					break;

				}
			}//4.3 ���ڵ���뵽�游�ڵ�ĵ��Ҳ�
			else if (gparent->right == parent) {
				//4.3.1 ����ڵ���ڲ���Ϊ��
				Node* unode = gparent->left;
				if (unode && unode->_c == RED) {
					//����ڵ����˫��ڵ�
					unode->_c = parent->_c = BLOCK;
					//�游�ڵ��Ϊ��ɫ
					gparent->_c = RED;


					//ѭ���������ڽڵ���ɫ
					root = gparent;
					parent = root->parent;
				
				}//4.3.2  ����ڵ㲻����
				else {
					//4.3.2.1 ����ڵ��ڸ��ڵ���Ҳ�
					if (root == parent->right) {
						//��ɫ ���ڵ�Ϊ��
						parent->_c = BLOCK;
						gparent->_c = RED;
					
						LL(gparent);
					}// 4.3.2.2 ����ڵ��ڸ��ڵ�����
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
		//���ڵ���Ϊ��ɫ
		head->_c = BLOCK;

	}
	//����
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
			//���ڵ�
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
	//����
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
			//���ڵ�
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

