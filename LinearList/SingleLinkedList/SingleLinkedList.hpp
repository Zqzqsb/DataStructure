#ifndef SINGLE_LINKED_LIST_HPP
#define SINGLE_LINKED_LIST_HPP

#include <iostream>
#include <vector>
#include <stdexcept>

template<typename T>
struct Node {
    T data;
    Node<T>* next;
    Node(const T& d = T(), Node<T>* n = nullptr) : data(d), next(n) {}
};

template<typename T>
class SingleLinkedList {
private:
    Node<T>* head;  // 头结点（虚拟节点）
    int length;     // 链表长度（不包括头结点）

public:
    // 默认构造函数
    SingleLinkedList() : length(0) {
        head = new Node<T>;
        head->next = nullptr;
    }
    
    // 使用vector构造
    SingleLinkedList(const std::vector<T>& v, bool reverse = true) : SingleLinkedList() {
        if (reverse) {
            // 头插法
            for (const auto& item : v) {
                insertHead(item);
            }
        } else {
            // 尾插法
            for (const auto& item : v) {
                append(item);
            }
        }
    }

    // 拷贝构造函数
    SingleLinkedList(const SingleLinkedList& other) : SingleLinkedList() {
        Node<T>* p = other.head->next;
        while (p != nullptr) {
            append(p->data);
            p = p->next;
        }
    }

    // 赋值运算符
    SingleLinkedList& operator=(const SingleLinkedList& other) {
        if (this != &other) {
            SingleLinkedList temp(other);
            std::swap(head, temp.head);
            std::swap(length, temp.length);
        }
        return *this;
    }
    
    // 析构函数
    ~SingleLinkedList() {
        clear();
        delete head;
    }

    // 清空链表
    void clear() {
        Node<T>* current = head->next;
        while (current != nullptr) {
            Node<T>* next = current->next;
            delete current;
            current = next;
        }
        head->next = nullptr;
        length = 0;
    }
    
    // 头插法
    void insertHead(const T& data) {
        Node<T>* newNode = new Node<T>(data);
        newNode->next = head->next;
        head->next = newNode;
        ++length;
    }

    // 尾插法
    void append(const T& data) {
        Node<T>* newNode = new Node<T>(data);
        Node<T>* p = head;
        while (p->next != nullptr) {
            p = p->next;
        }
        p->next = newNode;
        ++length;
    }
    
    // 在指定位置插入元素
    bool insert(int index, const T& data) {
        if (index < 1 || index > length + 1) {
            return false;
        }
        
        Node<T>* p = head;
        for (int i = 1; i < index; ++i) {
            p = p->next;
        }
        
        Node<T>* newNode = new Node<T>(data);
        newNode->next = p->next;
        p->next = newNode;
        ++length;
        return true;
    }
    
    // 删除指定位置的元素
    bool remove(int index, T& data) {
        if (index < 1 || index > length) {
            return false;
        }
        
        Node<T>* p = head;
        for (int i = 1; i < index; ++i) {
            p = p->next;
        }
        
        Node<T>* toDelete = p->next;
        data = toDelete->data;
        p->next = toDelete->next;
        delete toDelete;
        --length;
        return true;
    }
    
    // 获取指定位置的元素
    bool get(int index, T& data) const {
        if (index < 1 || index > length) {
            return false;
        }
        
        Node<T>* p = head->next;
        for (int i = 1; i < index; ++i) {
            p = p->next;
        }
        data = p->data;
        return true;
    }

    // 修改指定位置的元素
    bool set(int index, const T& data) {
        if (index < 1 || index > length) {
            return false;
        }
        
        Node<T>* p = head->next;
        for (int i = 1; i < index; ++i) {
            p = p->next;
        }
        p->data = data;
        return true;
    }

    // 查找元素位置
    int locate(const T& data) const {
        Node<T>* p = head->next;
        int index = 1;
        while (p != nullptr && p->data != data) {
            p = p->next;
            ++index;
        }
        return (p != nullptr) ? index : 0;
    }

    // 翻转链表
    void reverse() {
        if (length <= 1) return;
        
        Node<T>* prev = nullptr;
        Node<T>* curr = head->next;
        Node<T>* next = nullptr;
        
        while (curr != nullptr) {
            next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }
        
        head->next = prev;
    }

    // 获取长度
    int size() const {
        return length;
    }

    // 判断是否为空
    bool empty() const {
        return length == 0;
    }

    // 打印链表
    void print() const {
        Node<T>* p = head->next;
        while (p != nullptr) {
            std::cout << p->data;
            if (p->next != nullptr) {
                std::cout << " -> ";
            }
            p = p->next;
        }
        std::cout << std::endl;
    }
};

#endif // SINGLE_LINKED_LIST_HPP
