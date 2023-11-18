#include <iostream>
#include <vector>
 
class binary_heap {
private:
	std::vector<int> tree;
public:
	binary_heap() {}

	binary_heap(std::vector<int>& src) {
		for (auto& el : src) {
			tree.push_back(el);
		}
		for (int i = size() / 2; i >= 0; i--)
		{
			heapify(i);
		}
	}

	void add(int val) {
		tree.push_back(val);
		int i = size() - 1;
		int parent = (i - 1) / 2;
		while (i > 0 && tree[parent] < tree[i])
		{
			int temp = tree[i];

			tree[i] = tree[parent];
			tree[parent] = temp;

			i = parent;
			parent = (i - 1) / 2;
		}
		heapify(size() - 1);
	}

	int size() {
		return tree.size();
	}

	void heapify(int i)
	{
		int leftChild;
		int rightChild;
		int largestChild;

		while (1)
		{
			leftChild = 2 * i + 1;
			rightChild = 2 * i + 2;
			largestChild = i;

			if (leftChild < size() &&
				tree[leftChild] > tree[largestChild])  largestChild = leftChild;
			if (rightChild < size() &&
				tree[rightChild] > tree[largestChild]) largestChild = rightChild;
			if (largestChild == i) break;

			int temp = tree[i];
			tree[i] = tree[largestChild];
			tree[largestChild] = temp;
			i = largestChild;
		}
	}
};

class array_binary_heap {
private:
	int* tree;
	size_t capacity;
	size_t current;
	int length;

	void grow() {
		int* temp = tree;
		int prevSize = capacity;
		tree = new int[capacity = capacity * 2];
		std::copy(temp, temp + current, tree);
		delete[] temp;
	}
public:
	array_binary_heap() : 
		length(0), capacity(32), current(0), tree(new int[capacity]) {}

	array_binary_heap(std::vector<int>& src) : 
		length(0), capacity(32), current(0), tree(new int[capacity]) {
		tree = new int[capacity];
		for (auto& el : src) {
			add(el);
		}
		for (int i = size() / 2; i >= 0; i--)
		{
			heapify(i);
		}
	}

	void add(int val) {
		if (current == capacity) grow();
		tree[current++] = val;
		length++;
		int i = size() - 1;
		int parent = (i - 1) / 2;
		while (i > 0 && tree[parent] < tree[i])
		{
			int temp = tree[i];
			tree[i] = tree[parent];
			tree[parent] = temp;

			i = parent;
			parent = (i - 1) / 2;
		}
		heapify(size() - 1);
	}

	int size() {
		return length;
	}

	void heapify(int i)
	{
		int leftChild;
		int rightChild;
		int largestChild;

		while (1)
		{
			leftChild = 2 * i + 1;
			rightChild = 2 * i + 2;
			largestChild = i;

			if (leftChild < size() &&
				tree[leftChild] > tree[largestChild])  largestChild = leftChild;
			if (rightChild < size() &&
				tree[rightChild] > tree[largestChild]) largestChild = rightChild;
			if (largestChild == i) break;

			int temp = tree[i];
			tree[i] = tree[largestChild];
			tree[largestChild] = temp;
			i = largestChild;
		}
	}
};

int main()
{
	std::cout << "Hello World!\n";
}