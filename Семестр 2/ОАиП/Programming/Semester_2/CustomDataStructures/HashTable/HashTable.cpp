#include <iostream>
#include <vector>

constexpr auto PERCENTAGE_TO_RESIZE = 0.7;
constexpr auto CELL_EMPTY = 0;
constexpr auto CELL_FULL = 1;
constexpr auto CELL_DELETED = 2;

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

template<typename K, typename V, typename hash_provider = std::hash<K>>
class hash_table {
private:
	template<typename K2, typename V2>
	struct pair {
		K2 key;
		V2 value;
		// 0 - empty, 1 - full, 2 - deleted
		int status = CELL_EMPTY;
	};
	pair<K, V>* table;
	int table_capacity;
	int size;

	int get_index(K key) {		
		return hash_provider{}(key) % table_capacity;
	}

	void resize() {
		std::vector<pair<K, V>> tmp;
		for (int i = 0; i < table_capacity; i++) {
			if (table[i].status == 1) {
				tmp.push_back(table[i]);
			}
		}
		delete[] table;
		table = new pair<K, V>[table_capacity *= 2];
		for (int i = 0; i < table_capacity; i++) {
			table[i] = pair<K, V>();
		}
		for (auto& p : tmp) {
			int theoretical_index = get_index(p.key);
			if (table[theoretical_index].status == CELL_FULL) {
				while (table[theoretical_index].status != CELL_EMPTY &&
					table[theoretical_index].status != CELL_FULL) {
					theoretical_index++;
				}
			}
			table[theoretical_index].status = CELL_FULL;
			table[theoretical_index].key = p.key;
			table[theoretical_index].value = p.value;
		}
	}

public:
	hash_table() {
		size = 0;
		table_capacity = 32;
		table = new pair<K, V>[table_capacity];
		for (int i = 0; i < table_capacity; i++) {
			table[i] = pair<K, V>();
		}
	}

	void insert(K key, V value) {
		if (static_cast<int>(table_capacity * PERCENTAGE_TO_RESIZE) <= size) {
			resize();
		}
		int theoretical_index = get_index(key);
		if (table[theoretical_index].status == CELL_FULL) {
			while (table[theoretical_index].status != CELL_EMPTY && 
				   table[theoretical_index].status != CELL_FULL) {
				theoretical_index++;
			}
		}
		table[theoretical_index].status = CELL_FULL;
		table[theoretical_index].key = key;
		table[theoretical_index].value = value;
		size++;
	}

	V& get(K key) {
		int theoretical_index = get_index(key);
		while (table[theoretical_index].key != key && 
			   theoretical_index < table_capacity) {
			theoretical_index++;
		}
		if (table[theoretical_index].key == key) {
			return table[theoretical_index].value;
		}
	}

	bool contains(K key) {
		int theoretical_index = get_index(key);
		while (table[theoretical_index].key != key &&
			theoretical_index < table_capacity) {
			theoretical_index++;
		}
		if (table[theoretical_index].key == key) {
			return true;
		}
		return false;
	}

	void remove(K key) {
		int theoretical_index = get_index(key);
		while (table[theoretical_index].key != key &&
			theoretical_index < table_capacity) {
			theoretical_index++;
		}
		auto deleted_pair = pair<K, V>();
		deleted_pair.status = CELL_DELETED;
		table[theoretical_index] = deleted_pair;
	}

};

int main()
{
	hash_table<int, std::string> table;
	for (int i = 4; i < 40; i++) {
		table.insert(i, "mamba");
	}
	table.insert(1, "aboba");
	table.insert(2, "jabroni");
	table.insert(3, "bench press");
	std::cout << table.contains(547) << "**\n";
}