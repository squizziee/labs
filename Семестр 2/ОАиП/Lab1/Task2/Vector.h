#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
/*
assign; Удаляет вектор и копирует указанные элементы в пустой вектор.
• + at; Возвращает ссылку на элемент в заданном положении в векторе.
• + back; Возвращает ссылку на последний элемент вектора.
• + begin; Возвращает итератор произвольного доступа, указывающий на первый элемент в векторе.
• + capacity; Возвращает число элементов, которое вектор может содержать без выделения дополнительного пространства.
• cbegin; Возвращает константный итератор произвольного доступа, указывающий на первый элемент в векторе.
• + clear; Очищает элементы вектора.
• + data; Возвращает указатель на первый элемент в векторе.
• emplace; Вставляет элемент, созданный на месте, в указанное положение в векторе.
• emplace_back; Добавляет элемент, созданный на месте, в конец вектора.
• + empty; Проверяет, пуст ли контейнер вектора.
• + end; Возвращает итератор произвольного доступа, который указывает на конец вектора.
• erase; Удаляет элемент или диапазон элементов в векторе из заданных позиций.
• + front; Возвращает ссылку на первый элемент в векторе.
• + insert; Вставляет элемент или множество элементов в заданную позиции в вектор.
• + max_size; Возвращает максимальную длину вектора.
• + pop_back; Удаляет элемент в конце вектора.
• + push_back; Добавляет элемент в конец вектора.
• rbegin; Возвращает итератор, указывающий на первый элемент в обратном векторе.
• rend; Возвращает итератор, который указывает на последний элемент в обратном векторе.
• + reserve; Резервирует минимальную длину хранилища для объекта вектора.
• + resize; Определяет новый размер вектора.
• + size; Возвращает количество элементов в векторе.
• + swap; Меняет местами элементы двух векторов.
*/

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
        return !(*this == other);
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
        VectorIterator temp = *this;
        --(*this);
        return temp;
    }

    ReverseVectorIterator& operator--() {
        pointer++;
        return *this;
    }

    ReverseVectorIterator& operator--(int) {
        VectorIterator temp = *this;
        ++(*this);
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

    inline ReverseVectorIterator operator- (const int val) const {
        ReverseVectorIterator<Vector> it = pointer + val;
        return it;
    }

    bool operator==(const ReverseVectorIterator& other) const {
        return pointer == other.pointer;
    }
    bool operator!=(const ReverseVectorIterator& other) const {
        return !(*this == other);
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
    using reverseIterator = ReverseVectorIterator<Vector<T>>;
    Vector(int n = 32) : capacity(n), elements(new T[n]), current(0) {}

    ~Vector() {
        delete[] elements;
    }

    void push_back(T data) {
        if (current == capacity) {
            T* temp = elements;
            int prevSize = capacity;
            elements = new T[capacity = capacity * 2];
            std::copy(temp, temp + current, elements);
            delete[] temp;
        }
        elements[current++] = data;
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

    T& back() {
        return elements[current - 1];
    }

    iterator begin() {
        return iterator(elements);
    }

    iterator rbegin() {
        return iterator(elements + current);
    }

    iterator end() {
        return iterator(elements + current);
    }

    iterator rend() {
        return iterator(elements);
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

    T& front() {
        return elements[0];
    }

    void insert(Vector<T> &toInsert, int begin) {
        size_t offset = toInsert.size();
        Vector<T>* tail = new Vector();
        for (int i = begin; i < toInsert.size(); i++) {
            tail->push_back(elements[i]);
        }
        resize(size() - offset);
        for (int i = 0; i < toInsert.size(); i++) {
            push_back(toInsert[i]);
        }
        for (int i = 0; i < tail->size(); i++) {
            push_back(tail->at(i));
        }
    }

    int max_size() {
        return MAX_SIZE;
    }

    void reserve(size_t newCapacity) {
        capacity = newCapacity;
    }

    void resize(size_t newSize) {
        current = newSize;
    }

    void swap(Vector<T> &v) {
        T* temp = v.elements;
        v.elements = this->elements;
        this->elements = temp;
    }
};

#endif // VECTOR_H
