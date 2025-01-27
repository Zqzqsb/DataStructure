# 链式队列（Linked Queue）实现

这是一个基于链表实现的队列，支持基本的队列操作，包括入队、出队和查看队首元素。

## 概述

链式队列是一种基于链表实现的先进先出（FIFO）数据结构。相比顺序队列，链式队列不存在容量限制，可以根据需要动态增长。主要应用场景包括：
- 不定长数据的缓存
- 任务调度系统
- 消息队列
- 网络数据包处理
- 打印任务管理

## 特性

- 基于模板实现，支持任意数据类型
- 动态分配内存，无容量限制
- 支持基本队列操作（入队、出队、查看队首/队尾）
- 包含完整的内存管理
- 实现了拷贝构造和赋值操作
- 提供队列长度查询功能

## 核心算法实现思路

### 1. 链表节点设计

使用带头结点的单链表实现：
```cpp
template<typename T>
struct Node {
    T data;
    Node<T>* next;
    Node(const T& d = T(), Node<T>* n = nullptr) : data(d), next(n) {}
};
```

实现要点：
1. **头结点的使用**：
   - 使用头结点简化操作
   - 头结点不存储数据
   - 便于处理空队列情况

2. **注意事项**：
   - 节点构造函数提供默认参数
   - 数据成员使用模板类型
   - 提供初始化列表优化性能

### 2. 入队操作（enQueue）

```cpp
void enQueue(const T& e) {
    Node<T>* newNode = new Node<T>(e);
    rear->next = newNode;
    rear = newNode;
    ++size;
}
```

实现要点：
1. **节点插入**：
   - 创建新节点存储数据
   - 更新尾指针
   - 维护队列长度

2. **注意事项**：
   - 使用const引用参数
   - 正确处理指针连接
   - 注意内存分配异常安全

### 3. 出队操作（deQueue）

```cpp
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
```

实现要点：
1. **节点删除**：
   - 保存要删除的节点
   - 更新头结点的next指针
   - 特殊处理最后一个节点
   - 释放内存
   - 维护队列长度

2. **注意事项**：
   - 检查空队列
   - 正确处理尾指针
   - 避免内存泄漏

## API 接口说明

### 构造函数
```cpp
LinkedQueue();
```
- 创建空队列
- 初始化头结点
- 时间复杂度：O(1)

### 析构函数
```cpp
~LinkedQueue();
```
- 释放所有节点内存
- 时间复杂度：O(n)

### 拷贝控制
```cpp
LinkedQueue(const LinkedQueue& other);
LinkedQueue& operator=(const LinkedQueue& other);
```
- 深拷贝队列内容
- 确保独立的内存空间

### 核心操作

```cpp
bool isEmpty() const;
```
- 检查队列是否为空
- 返回：队空返回true，否则返回false
- 时间复杂度：O(1)

```cpp
int length() const;
```
- 获取队列中元素个数
- 返回：当前队列长度
- 时间复杂度：O(1)

```cpp
void enQueue(const T& e);
```
- 将元素加入队尾
- 参数：要入队的元素（常量引用）
- 时间复杂度：O(1)

```cpp
bool deQueue(T& e);
```
- 从队首移除元素
- 参数：用于存储出队元素的引用
- 返回：成功返回true，队空返回false
- 时间复杂度：O(1)

```cpp
bool getFront(T& e) const;
bool getRear(T& e) const;
```
- 获取队首/队尾元素但不删除
- 参数：用于存储元素的引用
- 返回：成功返回true，队空返回false
- 时间复杂度：O(1)

```cpp
void clear();
```
- 清空队列
- 释放所有节点（除头结点）
- 重置队列状态
- 时间复杂度：O(n)

## 使用示例

```cpp
#include "LinkedQueue.hpp"
#include <iostream>

int main() {
    // 创建整数队列
    LinkedQueue<int> queue;

    // 入队操作
    queue.enQueue(1);
    queue.enQueue(2);
    queue.enQueue(3);

    // 查看队首和队尾元素
    int front, rear;
    if (queue.getFront(front)) {
        std::cout << "队首元素: " << front << std::endl;  // 输出: 1
    }
    if (queue.getRear(rear)) {
        std::cout << "队尾元素: " << rear << std::endl;   // 输出: 3
    }

    // 出队操作
    int value;
    while (!queue.isEmpty()) {
        queue.deQueue(value);
        std::cout << value << " ";  // 输出: 1 2 3
    }

    return 0;
}
```

## 复杂度分析

| 操作 | 时间复杂度 | 空间复杂度 |
|-----|-----------|------------|
| 构造 | O(1) | O(1) |
| 析构 | O(n) | O(1) |
| 入队 | O(1) | O(1) |
| 出队 | O(1) | O(1) |
| 查看队首/队尾 | O(1) | O(1) |
| 判空 | O(1) | O(1) |
| 获取长度 | O(1) | O(1) |
| 清空 | O(n) | O(1) |

## 注意事项

- 所有操作前都要检查队列状态
- 注意内存管理，防止内存泄漏
- 拷贝操作会进行深拷贝
- 非线程安全，多线程环境下需要额外同步
- 注意检查返回值，合理处理异常情况
