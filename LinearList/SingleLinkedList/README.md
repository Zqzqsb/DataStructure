# 单链表（Single Linked List）实现

这是一个带头结点的单链表实现，支持基本的线性表操作，包括插入、删除、查找等功能。

## 概述

单链表是一种动态的线性表数据结构，它通过节点之间的指针连接来组织数据。每个节点包含数据域和指向下一个节点的指针。主要应用场景包括：
- 需要频繁插入删除的场景
- 数据量不确定的场景
- 内存空间要求不严格的场景
- 不需要随机访问的场景

## 特性

- 基于模板实现，支持任意数据类型
- 使用带头结点的设计
- 提供完整的线性表操作
- 支持向量初始化
- 实现了拷贝构造和赋值操作
- 支持链表翻转等扩展操作

## 核心算法实现思路

### 1. 节点结构

```cpp
template<typename T>
struct Node {
    T data;
    Node<T>* next;
    Node(const T& d = T(), Node<T>* n = nullptr) : data(d), next(n) {}
};
```

### 2. 插入操作

```cpp
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
```

实现要点：
1. **位置合法性检查**：
   - 插入位置必须在[1, length+1]范围内

2. **注意事项**：
   - 先连接新节点的next
   - 再修改前驱节点的next
   - 正确维护长度信息

### 3. 删除操作

```cpp
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
```

实现要点：
1. **位置合法性检查**：
   - 删除位置必须在[1, length]范围内
   - 链表不能为空

2. **注意事项**：
   - 保存被删除节点的数据
   - 正确连接前后节点
   - 释放被删除节点的内存
   - 正确维护长度信息

### 4. 翻转操作

```cpp
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
```

实现要点：
1. **特殊情况处理**：
   - 空链表或单节点链表无需翻转

2. **注意事项**：
   - 使用三个指针维护翻转过程
   - 保持头结点不变
   - 正确处理最后一个节点

## API 接口说明

### 构造函数
```cpp
SingleLinkedList();  // 默认构造函数
SingleLinkedList(const std::vector<T>& v, bool reverse = true);  // 向量构造
```
- 创建空链表或从向量构造链表
- 参数：
  - `v`: 初始化数据向量
  - `reverse`: true表示头插法（逆序），false表示尾插法（顺序）

### 析构函数
```cpp
~SingleLinkedList();
```
- 释放所有节点的内存

### 拷贝控制
```cpp
SingleLinkedList(const SingleLinkedList& other);
SingleLinkedList& operator=(const SingleLinkedList& other);
```
- 深拷贝链表内容
- 保证独立的内存空间

### 基本操作

```cpp
void insertHead(const T& data);
```
- 在表头插入元素（头插法）
- 参数：要插入的元素
- 时间复杂度：O(1)

```cpp
void append(const T& data);
```
- 在表尾添加元素（尾插法）
- 参数：要添加的元素
- 时间复杂度：O(n)

```cpp
bool insert(int index, const T& data);
```
- 在指定位置插入元素
- 参数：
  - `index`: 插入位置[1, length+1]
  - `data`: 要插入的元素
- 返回：成功返回true，失败返回false
- 时间复杂度：O(n)

```cpp
bool remove(int index, T& data);
```
- 删除指定位置的元素
- 参数：
  - `index`: 删除位置[1, length]
  - `data`: 存储被删除的元素
- 返回：成功返回true，失败返回false
- 时间复杂度：O(n)

```cpp
int locate(const T& data) const;
```
- 查找元素位置
- 参数：要查找的元素
- 返回：元素位置（从1开始），未找到返回0
- 时间复杂度：O(n)

### 其他操作

```cpp
void reverse();
bool get(int index, T& data) const;
bool set(int index, const T& data);
int size() const;
bool empty() const;
void clear();
void print() const;
```

## 使用示例

```cpp
#include "SingleLinkedList.hpp"
#include <vector>

int main() {
    // 使用向量构造链表（头插法）
    std::vector<int> v = {1, 2, 3, 4, 5};
    SingleLinkedList<int> list1(v);  // 结果：5->4->3->2->1

    // 使用向量构造链表（尾插法）
    SingleLinkedList<int> list2(v, false);  // 结果：1->2->3->4->5

    // 基本操作
    list1.insertHead(0);  // 头插
    list1.append(6);      // 尾插
    list1.insert(3, 10);  // 在第3个位置插入10

    // 删除操作
    int removed;
    list1.remove(3, removed);  // 删除第3个位置的元素

    // 查找操作
    int pos = list1.locate(4);  // 查找元素4的位置

    // 获取和修改
    int value;
    if (list1.get(2, value)) {
        std::cout << "第2个元素是: " << value << std::endl;
    }

    // 翻转链表
    list1.reverse();

    // 打印链表
    list1.print();

    return 0;
}
```

## 复杂度分析

| 操作 | 时间复杂度 | 空间复杂度 |
|-----|-----------|------------|
| 构造（空） | O(1) | O(1) |
| 构造（向量） | O(n) | O(n) |
| 析构 | O(n) | O(1) |
| 头插 | O(1) | O(1) |
| 尾插 | O(n) | O(1) |
| 插入 | O(n) | O(1) |
| 删除 | O(n) | O(1) |
| 查找 | O(n) | O(1) |
| 获取/修改 | O(n) | O(1) |
| 翻转 | O(n) | O(1) |
| 清空 | O(n) | O(1) |

## 注意事项

- 使用头结点简化了操作实现
- 所有操作前都要检查参数合法性
- 注意内存管理，防止内存泄漏
- 注意检查返回值，合理处理失败情况
- 下标从1开始
- 非线程安全，多线程环境下需要额外同步
- 尾插操作效率较低，考虑维护尾指针优化
