#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <initializer_list>

template <typename T, typename K>
struct Pair {
    T a;
    K b;

    Pair() {}
    Pair(T a, K b) : a(a), b(b) {}

    std::string toString() {
        return "{" + std::to_string(a) + ", " + std::to_string(b) + "}";
    }
};

template<typename Vector>
class ConstVectorIterator {
public:
    using valueType = typename Vector::valueType;
    using pointerType = const valueType*;
    using referenceType = const valueType&;

    ConstVectorIterator(pointerType ptr) : pointer(ptr) {}

    ConstVectorIterator& operator++() {
        pointer++;
        return *this;
    }

    ConstVectorIterator& operator++(int) {
        ConstVectorIterator temp = *this;
        ++(*this);
        return temp;
    }

    ConstVectorIterator& operator--() {
        pointer--;
        return *this;
    }

    ConstVectorIterator& operator--(int) {
        ConstVectorIterator temp = *this;
        --(*this);
        return temp;
    }

    referenceType operator[](int index) {
        return *(pointer + index);
    }

    pointerType operator->() {
        return pointer;
    }

    referenceType operator*() {
        return *pointer;
    }

    bool operator==(const ConstVectorIterator& other) const {
        return pointer == other.pointer;
    }

    bool operator!=(const ConstVectorIterator& other) const {
        return pointer != other.pointer;
    }

private:
    pointerType pointer;
};

template<typename Vector>
class ReverseVectorIterator {
public:
    using valueType = typename Vector::valueType;
    using pointerType = valueType*;
    using referenceType = valueType&;

    ReverseVectorIterator(pointerType ptr) : pointer(ptr) {}

    ReverseVectorIterator& operator++() {
        pointer--;
        return *this;
    }

    ReverseVectorIterator& operator++(int) {
        ReverseVectorIterator temp = *this;
        //--(*this);
        pointer--;
        return temp;
    }

    ReverseVectorIterator& operator--() {
        pointer++;
        return *this;
    }

    ReverseVectorIterator& operator--(int) {
        ReverseVectorIterator temp = *this;
        //++(*this);
        pointer--;
        return temp;
    }

    referenceType operator[](int index) {
        return *(pointer + index);
    }

    pointerType operator->() {
        return pointer;
    }

    referenceType operator*() {
        return *pointer;
    }

    bool operator==(const ReverseVectorIterator& other) const {
        return pointer == other.pointer;
    }
    bool operator!=(const ReverseVectorIterator& other) const {
        return pointer != other.pointer;
    }

private:
    pointerType pointer;
};

template<typename Vector>
class VectorIterator {
public:
    using valueType = typename Vector::valueType;
    using pointerType = valueType*;
    using referenceType = valueType&;

    VectorIterator(pointerType ptr) : pointer(ptr) {}

    VectorIterator& operator++() {
        pointer++;
        return *this;
    }

    VectorIterator& operator++(int) {
        VectorIterator temp = *this;
        ++(*this);
        return temp;
    }

    VectorIterator& operator--() {
        pointer--;
        return *this;
    }

    VectorIterator& operator--(int) {
        VectorIterator temp = *this;
        --(*this);
        return temp;
    }

    referenceType operator[](int index) {
        return *(pointer + index);
    }

    pointerType operator->() {
        return pointer;
    }

    referenceType operator*() {
        return *pointer;
    }

    bool operator==(const VectorIterator& other) const {
        return pointer == other.pointer;
    }
    bool operator!=(const VectorIterator& other) const {
        return pointer != other.pointer;
    }

private:
    pointerType pointer;
};

template<typename T>
class Vector {
private:
    static int const MAX_SIZE = 1024;
    T* elements;
    size_t capacity;
    size_t current;
public:
    using valueType = T;
    using iterator = VectorIterator<Vector<T>>;
    using reverse_iterator = ReverseVectorIterator<Vector<T>>;
    using const_iterator = ConstVectorIterator<Vector<T>>;
    Vector(int n = 32) : capacity(n), elements(new T[n]), current(0) {}
    Vector(std::initializer_list<T> data) : capacity(32), elements(new T[32]), current(0) {
        push_back(data);
    }

    ~Vector() {
        //delete[] elements;
    }

    void push_back(T data) {
        if (current == capacity) {
            grow();
        }
        elements[current++] = data;
    }

    void push_back(std::initializer_list<T> data) {
        for (auto el = data.begin(); el != data.end(); el++) {
            if (current == capacity) {
                grow();
            }
            elements[current++] = *el;
        }
    }

    void pop_back() {
        --current;
    }

    size_t size() {
        return current;
    }

    T& at(int index) {
        if (index >= 0 && index < current) {
            return elements[index];
        }
    }

    T& operator[](int index) {
        return at(index);
    }

    size_t getCapacity() {
        return capacity;
    }

    void assign(Vector<T>& dest) {
        if (dest.current != 0) {
            return;
        }
        for (int i = 0; i < current; i++) {
            dest.push_back(elements[i]);
        }
        clear();
    }

    T& back() {
        return elements[current - 1];
    }

    iterator begin() {
        return iterator(elements);
    }

    const_iterator cbegin() {
        return const_iterator(elements);
    }

    const_iterator cend() {
        return const_iterator(elements + current);
    }

    template <class... Args>
    void emplace(size_t index, Args&&... args) {
        insert(index, { T(std::forward<Args>(args)...) });
    }

    template <class... Args>
    void emplace_back(Args&&... args) {
        push_back(T(std::forward<Args>(args)...));
    }

    iterator end() {
        return iterator(elements + current);
    }

    reverse_iterator rbegin() {
        return reverse_iterator(elements + current - 1);
    }

    reverse_iterator rend() {
        return reverse_iterator(elements - 1);
    }

    void clear() {
        current = 0;
    }

    T* data() {
        return &elements[0];
    }

    bool empty() {
        return current == 0;
    }

    void erase(size_t start, size_t end) {
        Vector<T> temp;
        for (int i = 0; i < start; i++) {
            temp.push_back(elements[i]);
        }
        for (int i = end; i < current; i++) {
            temp.push_back(elements[i]);
        }
        clear();
        elements = temp.elements;
        current = temp.current;
        capacity = temp.capacity;
    }

    T& front() {
        return elements[0];
    }


    void insert(int index, std::initializer_list<T> data) {
        if (!(index >= 0 && index < current)) {
            return;
        }
        if (capacity == current) {
            grow();
        }
        Vector<T> temp;
        for (int i = 0; i < index; i++) {
            temp.push_back(elements[i]);
        }
        for (auto el = data.begin(); el != data.end(); el++) {
            temp.push_back(*el);
        }
        for (int i = index; i < current; i++) {
            temp.push_back(elements[i]);
        }
        clear();
        elements = temp.elements;
        current = temp.current;
        capacity = temp.capacity;
    }

    int max_size() {
        return MAX_SIZE;
    }

    void reserve(size_t newCapacity) {
        if (empty()) {
            elements = new T[newCapacity];
            capacity = newCapacity;
        }
    }

    void resize(size_t newSize) {
        if (newSize < current) {
            current = newSize;
        }
    }

    void swap(Vector<T>& v) {
        Vector<T> temp;
        for (T& el : this) {
            temp.push_back(el);
        }
        clear();
        for (T& el : v) {
            push_back(el);
        }
        v.clear();
        for (T& el : temp) {
            v.push_back(el);
        }
    }

    private:
        void grow() {
            T* temp = elements;
            int prevSize = capacity;
            elements = new T[capacity = capacity * 2];
            std::copy(temp, temp + current, elements);
            delete[] temp;
        }
};

#endif // VECTOR_H
