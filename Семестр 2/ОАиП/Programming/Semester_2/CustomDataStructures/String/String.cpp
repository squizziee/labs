#include <iostream>

class UPointer {
private:
	char* head;
public:

	operator bool() const {
		return head != nullptr;
	}

	UPointer(char* ptr = nullptr) : 
		head(ptr) {}

	~UPointer() {
		delete head;
	}

	UPointer(UPointer&& x) noexcept : 
		head(x.head) {
		x.head = nullptr;
	}

	UPointer(const UPointer& x) = delete;

	UPointer& operator=(UPointer& a) = delete;

	UPointer& operator=(UPointer&& x) noexcept {
		if (&x == this)
			return *this;
		delete[] head;
		head = x.head;
		x.head = nullptr;
		return *this;
	}

	UPointer& operator++() {
		head++;
		return *this;
	}

	UPointer& operator--() {
		head--;
		return *this;
	}

	UPointer* operator+(int offset) {
		std::cout << head << "\n";
		head = head + offset;
		std::cout << head << "\n";
		return this;
	}

	char* get() {
		return head;
	}

	char& operator*() const { return *head; }
	char* operator->() const { return head; }
	bool isNull() const { return head == nullptr; }

	friend size_t cst_strlen(UPointer* arg);
};

class StringIterator {
public:
	StringIterator(UPointer* ptr) 
		: ptr(ptr) {}

	StringIterator& operator++() {
		++(*ptr);
		return *this;
	}

	StringIterator& operator++(int) {
		StringIterator temp = *this;
		++(*ptr);
		return temp;
	}

	StringIterator& operator--() {
		++(*ptr);
		return *this;
	}

	StringIterator& operator--(int) {
		StringIterator temp = *this;
		++(*ptr);
		return temp;
	}

	UPointer* operator->() {
		return ptr;
	}

	char& operator*() {
		return **ptr;
	}

	bool operator==(const StringIterator& other) const {
		return ptr == other.ptr;
	}
	bool operator!=(const StringIterator& other) const {
		return *ptr != '\0';
		//return ptr != other.ptr;
	}

private:
	UPointer* ptr;
};

class String {
private:
	UPointer* characters_begin;
	size_t size;

	StringIterator begin() {
		return StringIterator(characters_begin);
	}

	StringIterator end() {
		return StringIterator(characters_begin + size);
	}
	//UPointer* characters_end;
public:
	
	String() {}
	String(const String& str) {
		characters_begin = str.characters_begin;
		size = cst_strlen(characters_begin);
	}

	String (const char* str) {
		characters_begin = new UPointer((char*)str);
		size = cst_strlen(characters_begin);
	}

	String& operator=(const char* str) {
		characters_begin = new UPointer((char*)str);
		size = cst_strlen(characters_begin);
		return *this;
	}

	char* c_str() {
		return characters_begin->get();
	}

	friend std::ostream& operator<<(std::ostream& output, String str);
	//friend UPointer* strcpy(String& s1, const String& s2);
};

std::ostream& operator<<(std::ostream& output, String str) {
	for (auto i = str.begin();
		*i != '\0'; ++i) {
		output << (*i);
	}
	return output;
};

size_t cst_strlen(UPointer* arg) {
	const char* s = arg->head;
	size_t len = 0;
	while (*s != '\0')
	{
		s++;
		len++;
	}
	return len;
}

size_t cst_strlen(const char* s) {
	size_t len = 0;
	while (*s != '\0')
	{
		s++;
		len++;
	}
	return len;
}

char* cst_strncpy(char* s1, const char* s2, size_t n) {
	size_t i;
	for (i = 0; i < n && s2[i] != '\0'; i++)
		s1[i] = s2[i];
	for (; i < n; i++)
		s1[i] = '\0';
	return s1;
}

int main() {
	String a = "monger";
	String b = "fjhghg";
	std::cout << cst_strlen(b.c_str()) << "\n";
	cst_strncpy(b.c_str(), a.c_str(), cst_strlen(a.c_str()));
	std::cout << b;
	return 0;
}