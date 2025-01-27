# 数组模拟链表（Simulated Linked List）实现

这是一个使用数组模拟实现的链表，通过两个数组分别存储数据和节点之间的关系，实现链表的基本功能。

## 概述

数组模拟链表是一种特殊的链表实现方式，它使用两个数组来模拟链表结构：一个数组存储数据，另一个数组存储节点之间的关系。这种实现方式的主要优点是：
- 内存分配更加高效（一次性分配）
- 内存布局更加紧凑
- 缓存友好性更好
- 适合特定场景下的链表操作

## 特性

- 基于模板实现，支持任意数据类型
- 使用两个数组模拟链表结构
- 提供完整的线性表操作
- 支持自定义容量
- 包含边界检查和异常处理
- 空间利用率高

## 核心算法实现思路

### 1. 数据结构

```cpp
template<typename T, size_t N = 100000>
class LinkedListSim {
private:
    std::vector<T> data;      // 存储节点数据
    std::vector<int> next;    // 存储下一个节点的位置
    int head;                 // 头节点位置
    int firstFree;           // 第一个可用位置
    size_t length;           // 链表长度
};
```

### 2. 获取新节点

```cpp
int getNewNode() {
    if (firstFree >= N) {
        throw std::runtime_error("No space available");
    }
    int pos = firstFree;
    firstFree++;
    return pos;
}
```

实现要点：
1. **空间管理**：
   - 检查是否还有可用空间
   - 更新firstFree指针

2. **注意事项**：
   - 容量限制检查
   - 异常处理

### 3. 插入操作

```cpp
void insertHead(const T& element) {
    int pos = getNewNode();
    data[pos] = element;
    next[pos] = head;
    head = pos;
    ++length;
}
```

实现要点：
1. **节点分配**：
   - 获取新节点位置
   - 存储数据

2. **链接更新**：
   - 更新next数组
   - 维护head指针
   - 更新长度信息

### 4. 删除操作

```cpp
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
```

实现要点：
1. **位置合法性检查**：
   - 删除位置必须在[1, length]范围内

2. **特殊情况处理**：
   - 删除头节点的情况
   - 删除其他位置的节点

3. **注意事项**：
   - 保存被删除的数据
   - 正确更新next数组
   - 维护长度信息

## API 接口说明

### 构造函数
```cpp
LinkedListSim();  // 默认构造函数
```
- 初始化数组和相关变量
- 设置head为-1表示空链表
- 设置firstFree为1（0通常不使用）

### 基本操作

```cpp
void insertHead(const T& element);
```
- 在链表头部插入元素
- 参数：要插入的元素
- 时间复杂度：O(1)

```cpp
void append(const T& element);
```
- 在链表尾部添加元素
- 参数：要添加的元素
- 时间复杂度：O(n)

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

### 其他操作

```cpp
bool get(int index, T& element) const;
bool set(int index, const T& element);
int locate(const T& element) const;
size_t size() const;
bool empty() const;
bool full() const;
void clear();
void print() const;
```

## 使用示例

```cpp
#include "LinkedListSim.hpp"
#include <iostream>

int main() {
    // 创建默认容量的链表
    LinkedListSim<int> list;

    // 添加元素
    list.append(1);
    list.append(2);
    list.append(3);

    // 在头部插入
    list.insertHead(0);

    // 在指定位置插入
    list.insert(3, 10);

    // 删除元素
    int removed;
    list.remove(3, removed);

    // 查找元素
    int pos = list.locate(2);

    // 获取元素
    int value;
    if (list.get(2, value)) {
        std::cout << "第2个元素是: " << value << std::endl;
    }

    // 打印链表
    list.print();

    return 0;
}
```

## 复杂度分析

| 操作 | 时间复杂度 | 空间复杂度 |
|-----|-----------|------------|
| 构造 | O(N) | O(N) |
| 头插 | O(1) | O(1) |
| 尾插 | O(n) | O(1) |
| 插入 | O(n) | O(1) |
| 删除 | O(n) | O(1) |
| 查找 | O(n) | O(1) |
| 获取/修改 | O(n) | O(1) |
| 清空 | O(N) | O(1) |

其中，N是链表的容量，n是当前链表的长度。

## 优缺点分析

### 优点
1. 内存分配一次完成，避免频繁的动态分配
2. 内存布局连续，缓存友好
3. 不会产生内存碎片
4. 适合频繁插入删除的场景
5. 实现简单，易于理解

### 缺点
1. 需要预先分配固定大小的空间
2. 不支持动态扩容
3. 可能会浪费一些空间
4. 删除节点后的空间无法重复利用

## 注意事项

1. **容量设置**：
   - 根据实际需求合理设置容量
   - 考虑内存使用和性能平衡

2. **索引管理**：
   - 通常不使用数组的0号位置
   - 使用-1表示空指针
   - 正确维护firstFree指针

3. **异常处理**：
   - 检查容量限制
   - 处理内存分配失败
   - 检查参数合法性

4. **性能考虑**：
   - 尾插操作效率较低
   - 考虑维护尾指针优化
   - 注意缓存命中率

5. **使用场景**：
   - 适合固定大小的链表应用
   - 适合高性能要求的场景
   - 适合内存受限的环境
