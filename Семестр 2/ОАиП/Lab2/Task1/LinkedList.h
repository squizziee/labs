#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#pragma once

#include <iostream>
#include <cstring>

template<typename T>
class LinkedList {
private:
    template<typename M>
    struct Node {
        Node<M>* previous = nullptr;
        Node<M>* next = nullptr;
        M data;
        Node() {}
        Node(M data) {
            this->data = data;
        }
    };
    Node<T>* head = nullptr;
    Node<T>* current = nullptr;
    int size = 0;
public:
    LinkedList() {

    }

    LinkedList(const LinkedList<T>& list) {
        head = list.head;
        current = list.current;
    }

    LinkedList(T headData) {
        head->data = headData;
        current = head;
        size++;
    }

    ~LinkedList() {
        /*Node<T>* temp;
        while (head)
        {
            temp = head->next;
            delete head;
            head = temp;
        }*/
    }

    void add(T element) {
        if (!head) {
            head = new Node<T>(element);
            current = head;
        }
        else {
            current->next = new Node<T>(element);
            current->next->previous = current;
            current = current->next;
        }
        size++;
    }

    void add(T element, int index) {
        if (index == 0) {
            if (head) {
                Node<T>* newNode = new Node<T>(element);
                head->previous = newNode;
                newNode->next = head;
                head = newNode;
            }
        }
        else if (index == size - 1) {
            add(element);
        }
        else {
            Node<T>* newNode = new Node<T>(element);
            Node<T>* ptr = head;
            int count = 0;
            while (count != index) {
                count++;
                ptr = ptr->next;
            }
            newNode->next = ptr->next;
            ptr->next = newNode;
            newNode->previous = ptr;
            newNode->next->previous = newNode;

        }
        size++;
    }

    void remove(int index) {
        if (index == 0) {
            head->next->previous = nullptr;
            Node<T>* temp = head;
            head = head->next;
            delete temp;
        }
        else if (index == size - 1) {
            Node<T>* ptr = current;
            current = current->previous;
            delete ptr;
        }
        else {
            Node<T>* ptr = head;
            int count = 0;
            while (count != index) {
                count++;
                ptr = ptr->next;
            }
            ptr->previous->next = ptr->next;
            ptr->next->previous = ptr->previous;
            delete ptr;
        }
        size--;
    }

    void clear() {
        /*if (head) {
            Node<T>* temp = head;
            while (temp) {
                head = head->next;
                if (temp) {
                    delete temp;
                }
            }
            size = 0;
        }*/
        Node<T>* temp;
        while (head)
        {
            temp = head->next;
            delete head;
            head = temp;
        }
        //delete head;
    }

    int getSize() {
        return size;
    }

    T& operator[](int index) {
        if (index == size - 1) {
            return current->data;
        }
        else if (index == 0) {
            return head->data;
        }
        int count = 0;
        Node<T> *temp = head;
        while (temp) {
            if (count == index) {
                return temp->data;
            }
            temp = temp->next;
            count++;
        }
    }
};
#endif // LINKEDLIST_H
