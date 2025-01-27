#ifndef SEQ_STACK_HPP
#define SEQ_STACK_HPP

#include <iostream>

template<typename T>
class SeqStack {
private:
    T* data;
    int maxSize;
    int top;

public:
    // Constructor
    explicit SeqStack(int size = 10) : maxSize(size), top(-1) {
        data = new T[size];
    }

    // Destructor
    ~SeqStack() {
        delete[] data;
    }

    // Copy constructor (Rule of 3)
    SeqStack(const SeqStack& other) : maxSize(other.maxSize), top(other.top) {
        data = new T[maxSize];
        for (int i = 0; i <= top; ++i) {
            data[i] = other.data[i];
        }
    }

    // Assignment operator (Rule of 3)
    SeqStack& operator=(const SeqStack& other) {
        if (this != &other) {
            T* newData = new T[other.maxSize];
            for (int i = 0; i <= other.top; ++i) {
                newData[i] = other.data[i];
            }
            delete[] data;
            data = newData;
            maxSize = other.maxSize;
            top = other.top;
        }
        return *this;
    }

    // Check if stack is empty
    bool empty() const {
        return top == -1;
    }

    // Check if stack is full
    bool full() const {
        return top == maxSize - 1;
    }

    // Push element onto stack
    bool push(const T& x) {
        if (full()) {
            return false;
        }
        data[++top] = x;
        return true;
    }

    // Pop element from stack
    bool pop(T& e) {
        if (empty()) {
            return false;
        }
        e = data[top--];
        return true;
    }

    // Get top element without removing it
    bool getTop(T& e) const {
        if (empty()) {
            return false;
        }
        e = data[top];
        return true;
    }

    // Get current size of stack
    int size() const {
        return top + 1;
    }

    // Get maximum capacity of stack
    int capacity() const {
        return maxSize;
    }
}; 

#endif // SEQ_STACK_HPP
