#ifndef LINKED_LIST_SIM_HPP
#define LINKED_LIST_SIM_HPP

#include <iostream>
#include <stdexcept>
#include <vector>

template<typename T, size_t N = 100000>
class LinkedListSim {
private:
    std::vector<T> data;      // 存储节点数据
    std::vector<int> next;    // 存储下一个节点的位置
    int head;                 // 头节点位置
    int firstFree;           // 第一个可用位置
    size_t length;           // 链表长度

    // 获取新节点的位置
    int getNewNode() {
        if (firstFree >= N) {
            throw std::runtime_error("No space available");
        }
        int pos = firstFree;
        firstFree++;
        return pos;
    }

public:
    // 构造函数
    LinkedListSim() : data(N), next(N, -1), head(-1), firstFree(1), length(0) {}

    // 头插法
    void insertHead(const T& element) {
        int pos = getNewNode();
        data[pos] = element;
        next[pos] = head;
        head = pos;
        ++length;
    }

    // 尾插法
    bool append(const T& element) {
        if (firstFree >= N) {
            return false;
        }
        int pos = getNewNode();
        data[pos] = element;
        next[pos] = -1;

        if (head == -1) {
            head = pos;
        } else {
            int p = head;
            while (next[p] != -1) {
                p = next[p];
            }
            next[p] = pos;
        }
        ++length;
        return true;
    }

    // 在指定位置插入
    bool insert(int index, const T& element) {
        if (index < 1 || index > length + 1) {
            return false;
        }

        if (index == 1) {
            insertHead(element);
            return true;
        }

        int pos = getNewNode();
        data[pos] = element;

        int p = head;
        for (int i = 1; i < index - 1; ++i) {
            p = next[p];
        }

        next[pos] = next[p];
        next[p] = pos;
        ++length;
        return true;
    }

    // 删除指定位置的元素
    bool remove(int index, T& element) {
        if (index < 1 || index > length) {
            return false;
        }

        int toDelete;
        if (index == 1) {
            toDelete = head;
            head = next[head];
        } else {
            int p = head;
            for (int i = 1; i < index - 1; ++i) {
                p = next[p];
            }
            toDelete = next[p];
            next[p] = next[toDelete];
        }

        element = data[toDelete];
        next[toDelete] = -1;  // 标记为已删除
        --length;
        return true;
    }

    // 获取指定位置的元素
    bool get(int index, T& element) const {
        if (index < 1 || index > length) {
            return false;
        }

        int p = head;
        for (int i = 1; i < index; ++i) {
            p = next[p];
        }
        element = data[p];
        return true;
    }

    // 修改指定位置的元素
    bool set(int index, const T& element) {
        if (index < 1 || index > length) {
            return false;
        }

        int p = head;
        for (int i = 1; i < index; ++i) {
            p = next[p];
        }
        data[p] = element;
        return true;
    }

    // 查找元素位置
    int locate(const T& element) const {
        int p = head;
        int index = 1;
        while (p != -1) {
            if (data[p] == element) {
                return index;
            }
            p = next[p];
            ++index;
        }
        return 0;
    }

    // 获取长度
    size_t size() const {
        return length;
    }

    // 判断是否为空
    bool empty() const {
        return length == 0;
    }

    // 判断是否已满
    bool full() const {
        return firstFree >= N;
    }

    // 清空链表
    void clear() {
        head = -1;
        firstFree = 1;
        length = 0;
        std::fill(next.begin(), next.end(), -1);
    }

    // 打印链表
    void print() const {
        int p = head;
        while (p != -1) {
            std::cout << data[p];
            if (next[p] != -1) {
                std::cout << " -> ";
            }
            p = next[p];
        }
        std::cout << std::endl;
    }
};

#endif // LINKED_LIST_SIM_HPP
