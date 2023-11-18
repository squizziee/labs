#include <iostream>
#include <vector>
constexpr auto PERCENTAGE_TO_RESIZE = 0.7;

template<typename T>
class int_hash_generator {
public:
	static size_t get(T& key, int table_capacity) {
		size_t prime = 196613;
		size_t h1 = key % table_capacity;
		size_t h2 = 1 + (key % table_capacity);
		size_t hash = h1 + prime * h2;
		return hash;
	}
};

template<typename T>
class stack {
private:
	template<typename M>
	struct node {
		M data;
		node<M>* next;
	};
	node<T>* top = nullptr;
public:
	void push(T data) {
		if (!top) {
			top = new node<T>{ data, nullptr };
		}
		else {
			auto temp = top;
			top = new node<T>{ data, temp };
		}
	}

	void pop() {
		auto temp = top;
		top = top->next;
		delete temp;
	}

	T& get() {
		return top->data;
	}

	bool empty() {
		return top == nullptr;
	}
};

template<typename K, typename V, typename hash_provider = int_hash_generator<K>>
class stack_hash_table {
private:
	template<typename K2, typename V2>
	struct pair {
		K2 key;
		V2 value;
		// 0 - empty, 1 - full, 2 - deleted
		int status = 0;
	};
	stack<pair<K, V>>* table;
	int table_capacity;
	int size;

	int get_index(K key) {
		return hash_provider::get(key, table_capacity) % table_capacity;
	}

public:
	stack_hash_table() {
		table_capacity = 32;
		size = 0;
		table = new stack<pair<K, V>>[table_capacity];
		for (int i = 0; i < table_capacity; i++) {
			table[i] = stack<pair<K, V>>();
		}
	}

	void insert(K key, V value) {
		if (static_cast<int>(table_capacity * PERCENTAGE_TO_RESIZE) <= size) {
			std::vector<pair<K, V>> tmp;
			for (int i = 0; i < table_capacity; i++) {
				while (!table[i].empty()) {
					tmp.push_back(table[i].get());
					table[i].pop();
				}
			}
			delete[] table;
			table = new stack<pair<K, V>>[table_capacity *= 2];
			for (int i = 0; i < table_capacity; i++) {
				table[i] = stack<pair<K, V>>();
			}
			for (auto& p : tmp) {
				int theoretical_index = get_index(p.key);
				table[theoretical_index].push(pair<K, V>{p.key, p.value, 1});
			}
		}
		int theoretical_index = get_index(key);
		table[theoretical_index].push(pair<K, V>{key, value, 1});
		size++;
	}

	V& get(K key) {
		int theoretical_index = get_index(key);
		stack<pair<K, V>> tmp_stack;
		bool found = false;
		while (table[theoretical_index].get().key != key && !table[theoretical_index].empty()) {
			if (table[theoretical_index].get().key == key) {
				found = true;
			}
			tmp_stack.push(table[theoretical_index].get());
			table[theoretical_index].pop();
		}
		if (table[theoretical_index].get().key == key) {
			found = true;
		}
		while (!tmp_stack.empty()) {
			table[theoretical_index].push(tmp_stack.get());
			tmp_stack.pop();
		}
		if (found) {
			return table[theoretical_index].get().value;
		}
	}

	void remove(K key) {
		int theoretical_index = get_index(key);
		stack<pair<K, V>> tmp_stack;
		bool found = false;
		while (table[theoretical_index].get().key != key && !table[theoretical_index].empty()) {
			if (table[theoretical_index].get().key == key) {
				found = true;
				while (!tmp_stack.empty()) {
					table[theoretical_index].push(tmp_stack.get());
					tmp_stack.pop();
				}
				return;
			}
			tmp_stack.push(table[theoretical_index].get());
			table[theoretical_index].pop();
		}
		if (!table[theoretical_index].empty()) {
			table[theoretical_index].pop();
		}
		while (!tmp_stack.empty()) {
			table[theoretical_index].push(tmp_stack.get());
			tmp_stack.pop();
		}
	}

	int min_key() {
		int min_key = INT32_MAX;
		for (int i = 0; i < table_capacity; i++) {
			stack<pair<K, V>> tmp_stack;
			while (!table[i].empty()) {
				if (table[i].get().key < min_key) {
					min_key = table[i].get().key;
				}
				table[i].pop();
			}
			while (!tmp_stack.empty()) {
				table[i].push(tmp_stack.get());
				tmp_stack.pop();
			}
		}
		return min_key;
	}

};

int main()
{
	stack_hash_table<int, std::string> table;
	for (int i = 5; i < 40; i++) {
		table.insert(i, "mamba");
	}
	std::cout << table.get(39) << "\n";
	table.remove(23);
	std::cout << table.get(39) << "\n";
	std::cout << table.get(24) << "\n";
	std::cout << table.min_key();
}