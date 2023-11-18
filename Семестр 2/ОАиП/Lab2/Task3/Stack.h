#include <algorithm>
#include <iostream>
#include <string>

#define ll long long

template <typename DT> class Vector {
private:
  DT *arr;
  ll capacity;
  ll length;

public:
  explicit Vector(ll = 500);
  ll push_back(DT);
  DT pop_back();
  ll size() const;
  DT &operator[](ll);
};

template <typename DT>
Vector<DT>::Vector(ll n) : capacity(n), arr(new DT[n]), length(0) {}

template <typename DT> ll Vector<DT>::push_back(DT data) {
  if (length == capacity) {
    DT *old = arr;
    arr = new DT[capacity = capacity * 2];
    copy(old, old + length, arr);
    delete[] old;
  }
  arr[length++] = data;
  return length;
}

template <typename DT> ll Vector<DT>::size() const { return length; }

template <typename DT> DT &Vector<DT>::operator[](ll index) {
  if (index >= length) {
    std::cout << "Error: Array index out of bound";
    throw new std::exception();
  }
  return *(arr + index);
}

template <typename DT> DT Vector<DT>::pop_back() { return arr[length-- - 1]; }

struct Node {
  std::string data;
  Node *link;
};

class Stack {
public:
  void push(Node **head, std::string data);
  bool isEmpty(Node **head);
  std::string top(Node *node);
  std::string pop(Node *node, Node **head);
};

void Stack::push(Node **head, std::string data) {
  Node *temp = new Node;
  if (!temp) {
    std::cout << "\nStack Overflow";
    exit(1);
  }
  temp->data = data;
  temp->link = (*head);
  (*head) = temp;
}

bool Stack::isEmpty(Node **head) { return *head == NULL; }

std::string Stack::top(Node *node) {
  if (!node) {
    std::cout << "Empty";
    exit(1);
  }
  return node->data;
}

std::string Stack::pop(Node *node, Node **head) {
  Node *temp = new Node;
  if (*head == NULL) {
    std::cout << "Stack is Empty";
    exit(1);
  } else {
    std::string get = node->data;
    temp = *head;
    *head = temp->link;
    free(temp);
    return get;
  }
}
