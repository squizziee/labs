#ifndef ARRAYLIST_H
#define ARRAYLIST_H

#include <iostream>

template <typename T>
class ArrayList {
private:
  static int const MAX_SIZE = 1024;
  T *elements;
  size_t capacity;
  size_t current;

public:
  ArrayList(const ArrayList<T> &arr) : capacity(arr.capacity), elements(new T[arr.capacity]), current(arr.current) {}
  ArrayList(int n = 32) : capacity(n), elements(new T[n]), current(0) {}

  ArrayList<T> operator=(const ArrayList<T> &arr) {
      this->capacity = arr.capacity;
      this->elements = new T[arr.capacity];
      this->current = arr.current;
  }

  ~ArrayList() {
    // delete[] elements;
  }

  void push_back(T data) {
    if (current == capacity) {
      T *temp = elements;
      int prevSize = capacity;
      elements = new T[capacity = capacity * 2];
      std::copy(temp, temp + current, elements);
      delete[] temp;
    }
    elements[current++] = data;
  }

  void pop_back() { --current; }

  size_t size() { return current; }

  T &at(int index) {
    if (index >= 0 && index < current) {
      return elements[index];
    }
  }

  T &operator[](int index) { return at(index); }

  size_t getCapacity() { return capacity; }

  T &back() { return elements[current - 1]; }

  void clear() {
    current = 0;
    capacity = 32;
    elements = new T[capacity];
  }

  T *data() { return &elements[0]; }

  bool empty() { return current == 0; }

  T &front() { return elements[0]; }

  void insert(ArrayList<T> &toInsert, int begin) {
    size_t offset = toInsert.size();
    ArrayList<T> *tail = new ArrayList();
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

  int max_size() { return MAX_SIZE; }

  void reserve(size_t newCapacity) { capacity = newCapacity; }

  void resize(size_t newSize) { current = newSize; }

  void swap(ArrayList<T> &v) {
    T *temp = v.elements;
    v.elements = this->elements;
    this->elements = temp;
  }
};

#endif // ARRAYLIST_H
