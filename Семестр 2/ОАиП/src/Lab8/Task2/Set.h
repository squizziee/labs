#include <algorithm>
#include <iostream>
#include <math.h>
#include <stack>
#include <string>
using namespace std;

template <typename T>
struct Node {
	T data;
	Node* left;
	Node* right;
public:
	void inorder(Node* r)
	{
		if (r == NULL) {
			return;
		}
		inorder(r->left);
		cout << r->data << " ";
		inorder(r->right);
	}

	int containsNode(Node* r, T d)
	{
		if (r == NULL) {
			return 0;
		}
		int x = r->data == d ? 1 : 0;
		return x | containsNode(r->left, d) | containsNode(r->right, d);
	}

	Node* insert(Node* r, T d)
	{
		if (r == NULL) {
			Node<T>* tmp = new Node<T>;
			tmp->data = d;
			tmp->left = tmp->right = NULL;
			return tmp;
		}

		if (d < r->data) {
			r->left = insert(r->left, d);
			return r;
		}

		else if (d > r->data) {
			r->right = insert(r->right, d);
			return r;
		}
		else
			return r;
	}
};

// Class to implement a Set using BST
template <typename T>
class Set {
	Node<T>* root;
	int size;
public:
	Set()
	{
		root = NULL;
		size = 0;
	}

	Set(const Set& s)
	{
		root = s.root;
		size = s.size;
	}
	void add(const T data)
	{
		if (!root->containsNode(root, data)) {
			root = root->insert(root, data);
			size++;
		}
	}

	T* toArray() {
		T* A = new T[size];
		int i = 0;
		stack<Node<T>*> nodeStack;
		nodeStack.push(this->root);

		while (!nodeStack.empty()) {
			Node<T>* node;
			node = nodeStack.top();
			nodeStack.pop();

			A[i++] = node->data;

			if (node->right)
				nodeStack.push(node->right);
			if (node->left)
				nodeStack.push(node->left);
		}
		return A;
	}

	bool contains(T data) {
		return root->containsNode(root, data) ? true : false;
	}

	void displaySet() {
		cout << "{ ";
		root->inorder(root);
		cout << "}" << endl;
	}

	int getSize() {
		return size;
	}
};