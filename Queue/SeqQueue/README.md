# 顺序队列（Sequential Queue）实现

这是一个基于数组实现的循环队列，支持基本的队列操作，包括入队、出队和查看队首元素。

## 概述

顺序队列是一种基于数组实现的先进先出（FIFO）数据结构。通过使用循环数组的方式，可以有效地利用空间，避免假溢出问题。主要应用场景包括：
- 任务调度
- 资源池管理
- 消息队列
- 打印机任务队列
- 进程/线程调度

## 特性

- 基于模板实现，支持任意数据类型
- 使用循环数组实现，空间利用率高
- 支持基本队列操作（入队、出队、查看队首）
- 包含完整的边界检查
- 实现了拷贝构造和赋值操作
- 异常安全

## 核心算法实现思路

### 1. 循环数组设计

为了有效利用空间，队列使用循环数组实现：
- front 指向队首元素
- rear 指向下一个可插入位置
- 通过取模运算实现循环：`(index + 1) % maxLen`

### 2. 入队操作（enQueue）

```cpp
bool enQueue(const T& e) {
    if ((rear + 1) % maxLen == front) {  // 队列已满
        return false;
    }
    data[rear] = e;
    rear = (rear + 1) % maxLen;
    return true;
}
```

实现要点：
1. **队满条件判断**：
   - 下一个位置是队首时表示队满
   - 需要预留一个位置区分队空和队满
   - 实际可用空间是数组大小减1

2. **注意事项**：
   - 使用取模运算实现循环
   - 先存储数据，再移动指针
   - 通过返回值表示操作成功与否

### 3. 出队操作（deQueue）

```cpp
bool deQueue(T& e) {
    if (empty()) {  // 队列为空
        return false;
    }
    e = data[front];
    front = (front + 1) % maxLen;
    return true;
}
```

实现要点：
1. **队空判断**：
   - front == rear 时表示队空
   - 通过引用返回出队元素

2. **注意事项**：
   - 先获取数据，再移动指针
   - 使用取模运算保持循环
   - 不需要实际删除数据

## API 接口说明

### 构造函数
```cpp
explicit SeqQueue(int len);
```
- 创建指定容量的队列（实际可用容量为len-1）
- 参数：
  - `len`: 队列的最大容量
- 异常：如果len <= 0，抛出std::invalid_argument

### 析构函数
```cpp
~SeqQueue();
```
- 释放动态分配的内存

### 拷贝控制
```cpp
SeqQueue(const SeqQueue& other);
SeqQueue& operator=(const SeqQueue& other);
```
- 深拷贝队列内容
- 保持队列状态一致

### 核心操作

```cpp
bool empty() const;
```
- 检查队列是否为空
- 返回：队空返回true，否则返回false
- 时间复杂度：O(1)

```cpp
int len() const;
```
- 获取队列中元素个数
- 返回：当前队列长度
- 时间复杂度：O(1)

```cpp
bool enQueue(const T& e);
```
- 将元素加入队尾
- 参数：要入队的元素（常量引用）
- 返回：成功返回true，队满返回false
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
```
- 获取队首元素但不删除
- 参数：用于存储队首元素的引用
- 返回：成功返回true，队空返回false
- 时间复杂度：O(1)

## 使用示例

```cpp
#include "SeqQueue.hpp"
#include <iostream>

int main() {
    // 创建容量为5的整数队列
    SeqQueue<int> queue(5);

    // 入队操作
    queue.enQueue(1);
    queue.enQueue(2);
    queue.enQueue(3);

    // 查看队首元素
    int front;
    if (queue.getFront(front)) {
        std::cout << "队首元素: " << front << std::endl;  // 输出: 1
    }

    // 出队操作
    int value;
    while (queue.deQueue(value)) {
        std::cout << value << " ";  // 输出: 1 2 3
    }

    return 0;
}
```

## 复杂度分析

| 操作 | 时间复杂度 | 空间复杂度 |
|-----|-----------|------------|
| 构造 | O(1) | O(n) |
| 析构 | O(1) | O(1) |
| 入队 | O(1) | O(1) |
| 出队 | O(1) | O(1) |
| 查看队首 | O(1) | O(1) |
| 判空 | O(1) | O(1) |
| 获取长度 | O(1) | O(1) |

## 注意事项

- 创建队列时，实际可用空间比指定的容量小1
- 所有操作都需要检查返回值
- 队列为空时，出队和获取队首元素操作会失败
- 队列满时，入队操作会失败
- 模板类的完整实现都在头文件中
- 非线程安全，多线程环境下需要额外同步
