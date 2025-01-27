# 顺序表（Sequential List）实现

这是一个基于数组实现的顺序表，支持基本的线性表操作，包括插入、删除、查找等功能。

## 概述

顺序表是一种基于数组实现的线性表，它的特点是逻辑上相邻的元素在物理位置上也相邻。主要应用场景包括：
- 需要频繁随机访问的场景
- 数据量相对固定的场景
- 需要快速存取数据的场景
- 对存储空间要求较高的场景

## 特性

- 基于模板实现，支持任意数据类型
- 使用动态数组实现，支持自定义容量
- 提供完整的线性表操作
- 包含边界检查和异常处理
- 实现了拷贝构造和赋值操作
- 支持扩展操作（删除最小值、翻转等）

## 核心算法实现思路

### 1. 插入操作（Insert）

```cpp
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
```

实现要点：
1. **位置合法性检查**：
   - 插入位置必须在[1, length+1]范围内
   - 检查表是否已满

2. **注意事项**：
   - 从后向前移动元素
   - 正确维护长度信息
   - 返回操作是否成功

### 2. 删除操作（Remove）

```cpp
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
```

实现要点：
1. **位置合法性检查**：
   - 删除位置必须在[1, length]范围内
   - 表不能为空

2. **注意事项**：
   - 保存被删除的元素
   - 从前向后移动元素
   - 正确维护长度信息

## API 接口说明

### 构造函数
```cpp
explicit SeqList(int size);
```
- 创建指定容量的顺序表
- 参数：
  - `size`: 顺序表的容量
- 异常：如果size <= 0，抛出std::invalid_argument

### 析构函数
```cpp
~SeqList();
```
- 释放动态分配的内存

### 拷贝控制
```cpp
SeqList(const SeqList& other);
SeqList& operator=(const SeqList& other);
```
- 深拷贝顺序表内容
- 保证独立的内存空间

### 基本操作

```cpp
bool append(const T& element);
```
- 在表尾添加元素
- 参数：要添加的元素（常量引用）
- 返回：成功返回true，表满返回false
- 时间复杂度：O(1)

```cpp
bool insert(int index, const T& element);
```
- 在指定位置插入元素
- 参数：
  - `index`: 插入位置[1, length+1]
  - `element`: 要插入的元素
- 返回：成功返回true，失败返回false
- 时间复杂度：O(n)

```cpp
bool remove(int index, T& element);
```
- 删除指定位置的元素
- 参数：
  - `index`: 删除位置[1, length]
  - `element`: 存储被删除的元素
- 返回：成功返回true，失败返回false
- 时间复杂度：O(n)

```cpp
int locate(const T& element) const;
```
- 查找元素位置
- 参数：要查找的元素
- 返回：元素位置（从1开始），未找到返回0
- 时间复杂度：O(n)

### 扩展操作

```cpp
bool deleteMin(T& minElement);
```
- 删除最小元素
- 参数：存储被删除的最小元素
- 返回：成功返回true，表空返回false
- 时间复杂度：O(n)

```cpp
void reverse();
```
- 翻转顺序表
- 时间复杂度：O(n)

### 其他操作

```cpp
bool get(int index, T& element) const;
bool set(int index, const T& element);
int size() const;
int capacity() const;
bool empty() const;
bool full() const;
void clear();
```

## 使用示例

```cpp
#include "SeqList.hpp"
#include <iostream>

int main() {
    // 创建容量为10的整数顺序表
    SeqList<int> list(10);

    // 添加元素
    for (int i = 1; i <= 5; ++i) {
        list.append(i);
    }

    // 插入元素
    list.insert(3, 0);  // 在第3个位置插入0

    // 删除元素
    int removed;
    list.remove(3, removed);  // 删除第3个位置的元素

    // 查找元素
    int pos = list.locate(4);  // 查找元素4的位置

    // 获取元素
    int value;
    if (list.get(2, value)) {
        std::cout << "第2个元素是: " << value << std::endl;
    }

    return 0;
}
```

## 复杂度分析

| 操作 | 时间复杂度 | 空间复杂度 |
|-----|-----------|------------|
| 构造 | O(1) | O(n) |
| 析构 | O(1) | O(1) |
| 插入 | O(n) | O(1) |
| 删除 | O(n) | O(1) |
| 查找 | O(n) | O(1) |
| 随机访问 | O(1) | O(1) |
| 追加 | O(1) | O(1) |
| 删除最小值 | O(n) | O(1) |
| 翻转 | O(n) | O(1) |

## 注意事项

- 创建顺序表时必须指定正确的容量
- 所有操作前都要检查参数合法性
- 插入和删除操作需要移动大量元素，效率较低
- 注意检查返回值，合理处理失败情况
- 下标从1开始
- 非线程安全，多线程环境下需要额外同步
