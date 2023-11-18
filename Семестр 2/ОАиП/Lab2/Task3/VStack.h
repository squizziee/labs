#include <iostream>

template <typename T>
class VStack {
private:
    template <typename M>
    struct Node {
        Node<M>* prev = nullptr;
        Node<M>* next = nullptr;
        M data;
    public:
        Node() {}
        Node(Node<M>* prev, Node<M>* next, M data) :
            prev(prev), next(next), data(data) {}
    };
    Node<T>* top = nullptr;
    int size = 0;
public:
    void push_front(T data) {
        if (top) {
            //std::cout << "here\n";
            Node<T>* temp = new Node<T>();
            temp->data = data;
            temp->prev = top;
            top->next = temp;
            top = temp;
        } else {
            Node<T>* temp = new Node<T>();
            temp->data = data;
            top = temp;
        }
        size++;
    }

    T& front() {
        return top->data;
    }

    void pop_front() {
        Node<T>* temp = top;
        top = top->prev;
        delete temp;
        size--;
    }

    bool empty() {
        return size == 0;
    }
};
