#ifndef LINKED_QUEUE_HPP
#define LINKED_QUEUE_HPP

#include <iostream>
#include <stdexcept>

template<typename T>
struct Node {
    T data;
    Node<T>* next;
    Node(const T& d = T(), Node<T>* n = nullptr) : data(d), next(n) {}
};

template<typename T>
class LinkedQueue {
private:
    Node<T> *front, *rear;
    int size;

public:
    // 构造函数
    LinkedQueue() : size(0) {
        front = new Node<T>;
        front->next = nullptr;
        rear = front;
    }

    // 析构函数
    ~LinkedQueue() {
        clear();
        delete front;
    }

    // 拷贝构造函数
    LinkedQueue(const LinkedQueue& other) : LinkedQueue() {
        Node<T>* p = other.front->next;
        while (p != nullptr) {
            enQueue(p->data);
            p = p->next;
        }
    }

    // 赋值运算符
    LinkedQueue& operator=(const LinkedQueue& other) {
        if (this != &other) {
            LinkedQueue temp(other);
            std::swap(front, temp.front);
            std::swap(rear, temp.rear);
            std::swap(size, temp.size);
        }
        return *this;
    }

    // 清空队列
    void clear() {
        Node<T>* p = front->next;
        while (p != nullptr) {
            Node<T>* temp = p;
            p = p->next;
            delete temp;
        }
        rear = front;
        front->next = nullptr;
        size = 0;
    }

    // 检查队列是否为空
    bool isEmpty() const {
        return front == rear;
    }

    // 获取队列长度
    int length() const {
        return size;
    }
    
    // 入队操作
    void enQueue(const T& e) {
        Node<T>* newNode = new Node<T>(e);
        rear->next = newNode;
        rear = newNode;
        ++size;
    }

    // 出队操作
    bool deQueue(T& e) {
        if (isEmpty()) {
            return false;
        }
        Node<T>* temp = front->next;
        e = temp->data;
        front->next = temp->next;
        if (temp == rear) {
            rear = front;
        }
        delete temp;
        --size;
        return true;
    }

    // 获取队首元素
    bool getFront(T& e) const {
        if (isEmpty()) {
            return false;
        }
        e = front->next->data;
        return true;
    }

    // 获取队尾元素
    bool getRear(T& e) const {
        if (isEmpty()) {
            return false;
        }
        e = rear->data;
        return true;
    }
};

#endif // LINKED_QUEUE_HPP
