#include "iostream"
#define ll long long

template <typename DT>
class CVector {
private:
	DT* arr;
	ll capacity;
	ll length;

public:
	explicit CVector(ll n = 100) : capacity(n), arr(new DT[n]), length(0) {};

	ll push_back(DT data) {
		if (length == capacity) {
			DT* old = arr;
			arr = new DT[capacity = capacity * 2];
			std::copy(old, old + length, arr);
			delete[] old;
		}
		arr[length++] = data;
		return length;
	};

	~CVector() {
		delete[] arr;
	}

	DT pop_back() {
		return arr[length-- - 1];
	};

	ll size() const {
		return length;
	};
	DT& operator[](ll index) {
		if (index >= length) {
			std::cout << "Error: Array index out of bound";
			exit(0);
		}
		return *(arr + index);
	};

	class iterator {
	private:
		DT* ptr;

	public:
		explicit iterator() : ptr(nullptr) {}
		explicit iterator(DT* p) : ptr(p) {}

		bool operator==(const iterator& rhs) const {
			return ptr == rhs.ptr;
		}
		bool operator!=(const iterator& rhs) const {
			return !(*this == rhs);
		}

		DT operator*() const {
			return *ptr;
		}

		iterator& operator++() {
			++ptr;
			return *this;
		}

		iterator operator++(int) {
			iterator temp(*this);
			++* this;
			return temp;
		}
	};

	iterator begin() const {
		return iterator(arr);
	};
	iterator end() const {
		return iterator(arr + length);
	};
};