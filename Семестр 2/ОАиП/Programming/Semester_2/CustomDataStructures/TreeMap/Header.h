#pragma once

#include <memory>
#include <iostream>
#include <cmath>
#include <vector>

namespace custom {
	template<typename T>
	class binary_search_tree {
	private:
		template<typename M>
		struct node {
			node<M>* left = nullptr;
			node<M>* right = nullptr;
			M data;
		};
		node<T>* root = nullptr;
		void insert_internal(T data, node<T>*& anchor) {
			if (!anchor) {
				anchor = new node<T>{ nullptr, nullptr, data };
			}
			else if (data < anchor->data) {
				insert_internal(data, anchor->left);
			}
			else {
				insert_internal(data, anchor->right);
			}
		}

		node<T>* find_minimal(node<T>* temp) {
			while (temp->left) {
				temp = temp->left;
			}
			return temp;
		}

		node<T>* remove_internal(T data, node<T>* anchor) {
			if (!anchor) return anchor;
			else if (data < anchor->data) anchor->left = remove_internal(data, anchor->left);
			else if (data > anchor->data) anchor->right = remove_internal(data, anchor->right);
			else {
				if (!anchor->left && !anchor->right) {
					delete anchor;
					anchor = nullptr;
				}
				else if (!anchor->left) {
					auto temp = anchor;
					anchor = anchor->right;
					delete temp;
				}
				else if (!anchor->right) {
					auto temp = anchor;
					anchor = anchor->left;
					delete temp;
				}
				else {
					auto temp = find_minimal(anchor->right);
					anchor->data = temp->data;
					anchor->right = remove_internal(temp->data, anchor->right);
				}
			}
			return anchor;
		}

		int get_height_util(node<T>* anchor, int& height) {
			if (!anchor) {
				return height;
			}
			int left_height = get_height_util(anchor->left, height);
			int right_height = get_height_util(anchor->right, height);

			int ans = std::max<int>(left_height, right_height) + 1;

			if (!anchor) {
				height = ans;
			}
			return ans;
		}

		size_t get_height(node<T>* anchor) {
			int h = -1;
			return get_height_util(anchor, h);
		}

		node<T>* balance_util(std::vector<T> elements, int start, int end) {
			if (start > end) return nullptr;
			int mid = (start + end) / 2;
			auto anchor = new node<T>{ nullptr, nullptr, elements[mid] };
			anchor->left = balance_util(elements, start, mid - 1);
			anchor->right = balance_util(elements, mid + 1, end);
			return anchor;
		}

		void balance() {
			if (!root) return;
			if (fabsl(
				get_height(root->left) -
				get_height(root->right)) >= 2) {
				std::vector<T> tmp;
				to_vector_inorder(root, tmp);
				root = balance_util(tmp, 0, tmp.size() - 1);
			}
		}

		void to_vector_inorder(node<T>*& anchor, std::vector<T>& vect) {
			if (!anchor) {
				return;
			}
			to_vector_inorder(anchor->left, vect);
			vect.push_back(anchor->data);
			to_vector_inorder(anchor->right, vect);
		}

		void print_inorder(node<T>*& anchor) {
			if (!anchor) {
				return;
			}
			print_inorder(anchor->left);
			std::cout << anchor->data << " ";
			print_inorder(anchor->right);
		}

		void print_preorder(node<T>*& anchor) {
			if (!anchor) {
				return;
			}
			std::cout << anchor->data << " ";
			print_preorder(anchor->left);
			print_preorder(anchor->right);
		}

		void print_postorder(node<T>*& anchor) {
			if (!anchor) {
				return;
			}
			print_postorder(anchor->left);
			print_postorder(anchor->right);
			std::cout << anchor->data << " ";
		}

	public:
		void insert(T data) {
			if (!root) {
				root = new node<T>{ nullptr, nullptr, data };
			}
			else {
				insert_internal(data, root);
			}
			balance();
		}

		void show(const int MODE) {
			switch (MODE) {
			case 0:
				print_inorder(root);
				break;
			case 1:
				print_preorder(root);
				break;
			case 2:
				print_postorder(root);
				break;
			default:
				break;
			}
			std::cout << "\n";
		}

		void remove(T key) {
			root = remove_internal(key, root);
			balance();
		}
	};

	template<typename K, typename V>
	struct pair {
		K key;
		V value;
	};

	template<typename T = pair<>>
	class 
}