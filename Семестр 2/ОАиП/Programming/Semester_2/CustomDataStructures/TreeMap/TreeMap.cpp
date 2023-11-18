#include <memory>
#include <iostream>
#include <cmath>
#include <vector>

/*namespace custom {
	template<typename K2, typename V2>
	struct pair {
		K2 key;
		V2 value;
	};
	template<typename K, typename V>
	class tree_map {
	private:
		template<typename M>
		struct node {
			node<M>* left = nullptr;
			node<M>* right = nullptr;
			M data;
		};
		node<pair<K, V>>* root = nullptr;
		void insert_internal(pair<K, V> data, node<pair<K, V>>*& anchor) {
			if (!anchor) {
				anchor = new node<pair<K, V>>{ nullptr, nullptr, data };
			}
			else if (data.key < anchor->data.key) {
				insert_internal(data, anchor->left);
			}
			else {
				insert_internal(data, anchor->right);
			}
		}

		node<pair<K, V>>* find_minimal(node<pair<K, V>>* temp) {
			while (temp->left) {
				temp = temp->left;
			}
			return temp;
		}

		node<pair<K, V>>* remove_internal(K data, node<pair<K, V>>* anchor) {
			if (!anchor) return anchor;
			else if (data < anchor->data.key) anchor->left = remove_internal(data, anchor->left);
			else if (data > anchor->data.key) anchor->right = remove_internal(data, anchor->right);
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
					anchor->right = remove_internal(temp->data.key, anchor->right);
				}
			}
			return anchor;
		}

		int get_height_util(node<pair<K, V>>* anchor, int& height) {
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

		size_t get_height(node<pair<K, V>>* anchor) {
			int h = -1;
			return get_height_util(anchor, h);
		}

		node<pair<K, V>>* balance_util(std::vector<pair<K, V>> elements, int start, int end) {
			if (start > end) return nullptr;
			int mid = (start + end) / 2;
			auto anchor = new node<pair<K, V>>{ nullptr, nullptr, elements[mid] };
			anchor->left = balance_util(elements, start, mid - 1);
			anchor->right = balance_util(elements, mid + 1, end);
			return anchor;
		}

		void balance() {
			if (!root) return;
			if (fabsl(
				get_height(root->left) -
				get_height(root->right)) >= 2) {
				std::vector<pair<K, V>> tmp;
				to_vector_inorder(root, tmp);
				root = balance_util(tmp, 0, tmp.size() - 1);
			}
		}

		void to_vector_inorder(node<pair<K, V>>*& anchor, std::vector<pair<K, V>>& vect) {
			if (!anchor) {
				return;
			}
			to_vector_inorder(anchor->left, vect);
			vect.push_back(anchor->data);
			to_vector_inorder(anchor->right, vect);
		}

		void print_inorder(node<pair<K, V>>*& anchor) {
			if (!anchor) {
				return;
			}
			print_inorder(anchor->left);
			std::cout << "{" << anchor->data.key << " " << anchor->data.value << "}";
			print_inorder(anchor->right);
		}

		void print_preorder(node<pair<K, V>>*& anchor) {
			if (!anchor) {
				return;
			}
			std::cout << "{" << anchor->data.key << " " << anchor->data.value << "}";
			print_preorder(anchor->left);
			print_preorder(anchor->right);
		}

		void print_postorder(node<pair<K, V>>*& anchor) {
			if (!anchor) {
				return;
			}
			print_postorder(anchor->left);
			print_postorder(anchor->right);
			std::cout << "{" << anchor->data.key << " " << anchor->data.value << "}";
		}

	public:
		void insert(K key, V value) {
			if (!root) {
				root = new node<pair<K, V>>{ nullptr, nullptr, pair<K, V>{key, value} };
			}
			else {
				insert_internal(pair<K, V>{key, value}, root);
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

		void remove(K key) {
			root = remove_internal(key, root);
			balance();
		}
	};
}

int main() {
	custom::tree_map<int, std::string > tree;
	for (int i = 0; i < 10; i++) {
		tree.insert(i, "moga");
	}
	tree.show(0);
	tree.show(1);
	tree.show(2);
	return 0;
}*/

template<typename K, typename V>
struct pair {
	K key;
	V value;
};
template<typename M>
struct node {
	node<M>* left = nullptr;
	node<M>* right = nullptr;
	M data;
};
template<typename K, typename V>
class tree_map {
protected:
	node<pair<K, V>>* root = nullptr;
	int print_mode;
	void insert_internal(pair<K, V> data, node<pair<K, V>>*& anchor) {
		if (!anchor) {
			anchor = new node<pair<K, V>>{ nullptr, nullptr, data };
		}
		else if (data.key < anchor->data.key) {
			insert_internal(data, anchor->left);
		}
		else if (data.key > anchor->data.key) {
			insert_internal(data, anchor->right);
		}
	}

	node<pair<K, V>>* find_minimal(node<pair<K, V>>* temp) {
		while (temp->left) {
			temp = temp->left;
		}
		return temp;
	}

	node<pair<K, V>>* remove_internal(K data, node<pair<K, V>>* anchor) {
		if (!anchor) return anchor;
		else if (data < anchor->data.key) anchor->left = remove_internal(data, anchor->left);
		else if (data > anchor->data.key) anchor->right = remove_internal(data, anchor->right);
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
				anchor->right = remove_internal(temp->data.key, anchor->right);
			}
		}
		return anchor;
	}

	int get_height_util(node<pair<K, V>>* anchor, int& height) {
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

	size_t get_height(node<pair<K, V>>* anchor) {
		int h = -1;
		return get_height_util(anchor, h);
	}

	node<pair<K, V>>* balance_util(std::vector<pair<K, V>> elements, int start, int end) {
		if (start > end) return nullptr;
		int mid = (start + end) / 2;
		auto anchor = new node<pair<K, V>>{ nullptr, nullptr, elements[mid] };
		anchor->left = balance_util(elements, start, mid - 1);
		anchor->right = balance_util(elements, mid + 1, end);
		return anchor;
	}

	void balance() {
		if (!root) return;
		if (fabsl(
			get_height(root->left) -
			get_height(root->right)) >= 2) {
			std::vector<pair<K, V>> tmp;
			to_vector_inorder(root, tmp);
			root = balance_util(tmp, 0, tmp.size() - 1);
		}
	}

	void to_vector_inorder(node<pair<K, V>>*& anchor, std::vector<pair<K, V>>& vect) {
		if (!anchor) {
			return;
		}
		to_vector_inorder(anchor->left, vect);
		vect.push_back(anchor->data);
		to_vector_inorder(anchor->right, vect);
	}

	void print_inorder(node<pair<K, V>>*& anchor) {
		if (!anchor) {
			return;
		}
		print_inorder(anchor->left);
		if (print_mode == 0) {
			std::cout << "{" << anchor->data.key << " " << anchor->data.value << "}";
		}
		else if (print_mode == 1) {
			std::cout << "{" << anchor->data.key << "}";
		}
		print_inorder(anchor->right);
	}

	void print_preorder(node<pair<K, V>>*& anchor) {
		if (!anchor) {
			return;
		}
		if (print_mode == 0) {
			std::cout << "{" << anchor->data.key << " " << anchor->data.value << "}";
		}
		else if (print_mode == 1) {
			std::cout << "{" << anchor->data.key << "}";
		}
		print_preorder(anchor->left);
		print_preorder(anchor->right);
	}

	void print_postorder(node<pair<K, V>>*& anchor) {
		if (!anchor) {
			return;
		}
		print_postorder(anchor->left);
		print_postorder(anchor->right);
		if (print_mode == 0) {
			std::cout << "{" << anchor->data.key << " " << anchor->data.value << "}";
		}
		else if (print_mode == 1) {
			std::cout << "{" << anchor->data.key << "}";
		}
	}

public:
	tree_map() {
		print_mode = 0;
	}

	void insert(K key, V value) {
		if (!root) {
			root = new node<pair<K, V>>{ nullptr, nullptr, pair<K, V>{key, value} };
		}
		else {
			insert_internal(pair<K, V>{key, value}, root);
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

	void remove(K key) {
		root = remove_internal(key, root);
		balance();
	}
};

template<typename K, typename V = K> 
class tree_set : public tree_map<K, V> {
public:
	tree_set() {
		tree_map<K, V>::print_mode = 1;
	}
	void insert(K key) {
		tree_map<K, V>::insert(key, key);
	}
};
template<typename K, typename V>
class tree_iterator {
	node<pair<K, V>>* curr;
public:
	tree_iterator(node<pair<K, V>>* root) {
		curr = root;
	}

	void go_left() {
		curr = curr->left;
	}

	void go_right() {
		curr = curr->right;
	}

	V& get() {
		return curr->data.value;
	}
};

int main() {
	tree_set<int> set;
	set.insert(1);
	set.insert(2);
	set.insert(3);
	set.insert(4);
	set.insert(4);
	set.show(0);
}