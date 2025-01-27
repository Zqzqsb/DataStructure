#ifndef SEQLIST_HPP
#define SEQLIST_HPP

#include <stdexcept>
#include <algorithm>

template<typename T>
class SeqList {
private:
    T* data;
    int maxSize;
    int length;

public:
    // 构造函数
    explicit SeqList(int size) : maxSize(size), length(0) {
        if (size <= 0) {
            throw std::invalid_argument("Size must be positive");
        }
        data = new T[size];
    }

    // 析构函数
    ~SeqList() {
        delete[] data;
    }

    // 拷贝构造函数
    SeqList(const SeqList& other) : maxSize(other.maxSize), length(other.length) {
        data = new T[maxSize];
        for (int i = 0; i < length; ++i) {
            data[i] = other.data[i];
        }
    }

    // 赋值运算符
    SeqList& operator=(const SeqList& other) {
        if (this != &other) {
            T* newData = new T[other.maxSize];
            for (int i = 0; i < other.length; ++i) {
                newData[i] = other.data[i];
            }
            delete[] data;
            data = newData;
            maxSize = other.maxSize;
            length = other.length;
        }
        return *this;
    }

    // 在末尾添加元素
    bool append(const T& element) {
        if (length >= maxSize) {
            return false;
        }
        data[length++] = element;
        return true;
    }
    
    // 在指定位置插入元素
    bool insert(int index, const T& element) {
        if (index < 1 || index > length + 1) {
            return false;
        }
        
        if (length >= maxSize) {
            return false;
        }
        
        // 移动元素腾出空间
        for (int i = length; i >= index; --i) {
            data[i] = data[i-1];
        }
        data[index-1] = element;
        ++length;
        return true;
    }
    
    // 删除指定位置的元素
    bool remove(int index, T& element) {
        if (index < 1 || index > length) {
            return false;
        }
        element = data[index-1];
        for (int i = index - 1; i < length - 1; ++i) {
            data[i] = data[i+1];
        }
        --length;
        return true;
    }

    // 查找元素位置
    int locate(const T& element) const {
        for (int i = 0; i < length; ++i) {
            if (data[i] == element) {
                return i + 1;
            }
        }
        return 0;
    }

    // 删除最小元素
    bool deleteMin(T& minElement) {
        if (length == 0) {
            return false;
        }
        int minIndex = 0;
        for (int i = 1; i < length; ++i) {
            if (data[i] < data[minIndex]) {
                minIndex = i;
            }
        }
        minElement = data[minIndex];
        data[minIndex] = data[length-1];
        --length;
        return true;
    }

    // 翻转顺序表
    void reverse() {
        int left = 0;
        int right = length - 1;
        while (left < right) {
            std::swap(data[left], data[right]);
            left++;
            right--;
        }
    }

    // 获取元素
    bool get(int index, T& element) const {
        if (index < 1 || index > length) {
            return false;
        }
        element = data[index-1];
        return true;
    }

    // 修改元素
    bool set(int index, const T& element) {
        if (index < 1 || index > length) {
            return false;
        }
        data[index-1] = element;
        return true;
    }

    // 获取长度
    int size() const {
        return length;
    }

    // 获取容量
    int capacity() const {
        return maxSize;
    }

    // 判断是否为空
    bool empty() const {
        return length == 0;
    }

    // 判断是否已满
    bool full() const {
        return length == maxSize;
    }

    // 清空顺序表
    void clear() {
        length = 0;
    }
};

#endif // SEQLIST_HPP
