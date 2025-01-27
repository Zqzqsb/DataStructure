#ifndef LINKED_QUEUE_HPP
#define LINKED_QUEUE_HPP

#include <iostream>

template<typename T>
struct Node {
    T data;
    Node<T>* next;
};

template<typename T>
class linkedQueue {
    Node<T> *front, *rear;
public:
    linkedQueue() {
        front = new Node<T>;
        front->next = nullptr;
        rear = front;
    }

    ~linkedQueue() {
        rear = front->next;
        while(front != nullptr) {
            delete front;
            front = rear;
            if (rear) rear = front->next;
        }
    }

    bool isEmpty() const {
        return (front == rear);
    }
    
    void enQueue(const T& e) {
        Node<T> *q = new Node<T>;
        q->data = e;
        q->next = nullptr;
        rear->next = q; 
        rear = q;    
    }

    bool deQueue(T& e) {
        if(isEmpty())
            return false;
        Node<T>* work = front->next;
        e = work->data;
        front->next = work->next;        
        if(work == rear)
            rear = front;
        delete work;
        return true;
    }
};

#endif // LINKED_QUEUE_HPP
