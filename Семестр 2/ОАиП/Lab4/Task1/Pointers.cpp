#include <iostream>

template <typename T>
class SPointer {
private:
	T* m_ptr;
	int* reference_count;
public:
	operator bool() const {
		return m_ptr != nullptr;
	}

	SPointer(T* ptr = nullptr) : m_ptr(ptr), reference_count(new int(0)) {
		++(*reference_count);
	}

	~SPointer() {
		--(*reference_count);
		if (*reference_count == 0) {
			delete reference_count;
			delete m_ptr;
			std::cout << "vanished\n";
		}
	}

	SPointer(SPointer&& x) : m_ptr(x.m_ptr) {
		++(*reference_count);
	}

	SPointer(const SPointer& x) : m_ptr(x.m_ptr), reference_count(new int(0)) {}

	SPointer& operator=(SPointer& a) {
		++(*reference_count);
		m_ptr = a.m_ptr;
	}

	SPointer& operator=(SPointer&& x) {
		if (&x == this)
			return *this;
		delete m_ptr;
		m_ptr = x.m_ptr;
		++(*reference_count);
		return *this;
	}

	T& operator*() const { return *m_ptr; }
	T* operator->() const { return m_ptr; }
	bool isNull() const { return m_ptr == nullptr; }
};

template <typename T>
class UPointer {
private:
	T* m_ptr;
public:

	operator bool() const {
		return m_ptr != nullptr;
	}

	UPointer(T* ptr = nullptr) : m_ptr(ptr) {}

	~UPointer() {
		delete m_ptr;
	}

	UPointer(UPointer&& x) : m_ptr(x.m_ptr)
	{
		x.m_ptr = nullptr;
	}

	UPointer(const UPointer& x) = delete;
	
	UPointer& operator=(UPointer& a) = delete;

	UPointer& operator=(UPointer&& x) {
		if (&x == this)
			return *this;
		delete m_ptr;
		m_ptr = x.m_ptr;
		x.m_ptr = nullptr;
		return *this;
	}

	T& operator*() const { return *m_ptr; }
	T* operator->() const { return m_ptr; }
	bool isNull() const { return m_ptr == nullptr; }
};

int main()
{
	int* x = new int (5);
	{
		SPointer<int> ptr1(x);
		{
			SPointer<int> ptr2 = ptr1;
		}
		std::cout << "Hello World!\n";
	}
	std::cout << "Hello World!\n";
}