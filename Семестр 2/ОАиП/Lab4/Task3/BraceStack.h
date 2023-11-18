#ifndef BRACESTACK_H
#define BRACESTACK_H
#include <QChar>

class BraceStack {
private:
    struct Node {
        Node* prev = nullptr;
        Node* next = nullptr;
        QChar data;
    public:
        Node() {}
        Node(Node* prev, Node* next, QChar data) :
            prev(prev), next(next), data(data) {}
    };
    Node* top = nullptr;
    int size = 0;
public:
    void push_front(QChar data) {
        if (top) {
            //std::cout << "here\n";
            Node* temp = new Node();
            temp->data = data;
            temp->prev = top;
            top->next = temp;
            top = temp;
        } else {
            Node* temp = new Node();
            temp->data = data;
            top = temp;
        }
        size++;
    }

    QChar& front() {
        return top->data;
    }

    void pop_front() {
        Node* temp = top;
        top = top->prev;
        delete temp;
        size--;
    }

    bool empty() {
        return size == 0;
    }
};

#endif // BRACESTACK_H
