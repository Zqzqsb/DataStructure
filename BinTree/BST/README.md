# 二叉搜索树（Binary Search Tree）

这是一个模板化的二叉搜索树实现，支持基本的树操作以及前驱和后继节点的查找。

## 概述

二叉搜索树（BST）是一种特殊的二叉树，它具有以下性质：
1. 左子树中所有节点的值都小于根节点的值
2. 右子树中所有节点的值都大于根节点的值
3. 左右子树也都是二叉搜索树

这些性质使得二叉搜索树能够支持高效的查找、插入和删除操作。

## 特性

- 基于模板实现，支持任意可比较数据类型
- 支持标准的二叉搜索树操作
- 包含前驱和后继节点的查找功能
- 提供多种遍历方式
- 支持拷贝构造和赋值操作
- 完整的错误处理机制

## 核心算法实现思路

### 1. 插入操作

插入操作通过比较待插入值与当前节点值的大小，决定往左子树还是右子树继续搜索：
```cpp
Node* insert(Node* node, const T& value) {
    if (node == nullptr) {
        size++;
        return new Node(value);
    }

    if (value < node->data) {
        node->left = insert(node->left, value);
    } else if (value > node->data) {
        node->right = insert(node->right, value);
    }
    return node;
}
```

### 2. 删除操作

删除操作需要处理三种情况：
1. 叶子节点：直接删除
2. 只有一个子节点：用子节点替代当前节点
3. 有两个子节点：用右子树中的最小值替代当前节点，然后删除那个最小值节点

```cpp
Node* remove(Node* node, const T& value) {
    if (node == nullptr) {
        return nullptr;
    }

    if (value < node->data) {
        node->left = remove(node->left, value);
    } else if (value > node->data) {
        node->right = remove(node->right, value);
    } else {
        // 找到要删除的节点
        if (node->left == nullptr) {
            Node* temp = node->right;
            delete node;
            size--;
            return temp;
        } else if (node->right == nullptr) {
            Node* temp = node->left;
            delete node;
            size--;
            return temp;
        }

        // 有两个子节点的情况
        Node* temp = getMin(node->right);
        node->data = temp->data;
        node->right = remove(node->right, temp->data);
    }
    return node;
}
```

### 3. 前驱和后继查找

前驱是小于当前节点的最大值，后继是大于当前节点的最小值。查找过程需要考虑两种情况：
1. 节点有左/右子树：前驱是左子树中的最大值，后继是右子树中的最小值
2. 节点没有左/右子树：需要向上查找到第一个合适的祖先节点

## API 接口说明

### 构造和析构
```cpp
// 默认构造函数
BST();

// 析构函数
~BST();

// 拷贝构造函数
BST(const BST& other);

// 赋值运算符
BST& operator=(const BST& other);
```

### 基本操作

```cpp
// 插入节点
void insert(const T& value);

// 删除节点
void remove(const T& value);

// 查找节点
bool contains(const T& value) const;

// 获取最小值
T getMin() const;

// 获取最大值
T getMax() const;

// 获取前驱
T getPredecessor(const T& value) const;

// 获取后继
T getSuccessor(const T& value) const;

// 获取树的大小
int getSize() const;

// 判断树是否为空
bool isEmpty() const;

// 获取树的高度
int getHeight() const;

// 清空树
void clear();
```

### 遍历操作

```cpp
// 前序遍历
void preOrder() const;

// 中序遍历
void inOrder() const;

// 后序遍历
void postOrder() const;

// 层序遍历
void levelOrder() const;
```

## 使用示例

```cpp
#include "BST.hpp"

int main() {
    // 创建BST
    BST<int> tree;
    
    // 插入一些节点
    tree.insert(10);
    tree.insert(5);
    tree.insert(15);
    tree.insert(3);
    tree.insert(7);
    
    // 遍历树
    tree.inOrder();    // 输出：3 5 7 10 15
    tree.levelOrder(); // 输出：10 5 15 3 7
    
    // 查找前驱和后继
    std::cout << "Predecessor of 10: " << tree.getPredecessor(10) << std::endl;  // 输出：7
    std::cout << "Successor of 5: " << tree.getSuccessor(5) << std::endl;        // 输出：7
    
    return 0;
}
```

## 复杂度分析

| 操作 | 平均时间复杂度 | 最坏时间复杂度 | 空间复杂度 |
|-----|--------------|--------------|----------|
| 插入 | O(log n) | O(n) | O(1) |
| 删除 | O(log n) | O(n) | O(1) |
| 查找 | O(log n) | O(n) | O(1) |
| 前驱/后继 | O(log n) | O(n) | O(1) |
| 遍历 | O(n) | O(n) | O(h) |

其中，n是树中节点的数量，h是树的高度。在最坏情况下（树退化为链表时），h = O(n)。

## 优缺点分析

### 优点
1. 实现简单，易于理解
2. 支持动态数据集的维护
3. 可以保持数据的有序性
4. 支持范围查询

### 缺点
1. 没有自平衡机制，可能退化为链表
2. 性能依赖于输入数据的顺序
3. 不适合频繁的插入和删除操作
4. 对于完全随机的数据，性能不如哈希表

## 应用场景

1. **符号表**：用于编译器和解释器中存储变量和函数的信息

2. **文件系统**：用于组织目录结构

3. **数据库索引**：作为索引的基础数据结构

4. **优先队列**：用于实现优先级队列

## 注意事项

1. **数据平衡**：
   - 注意输入数据的顺序可能导致树的不平衡
   - 考虑使用随机化或平衡树（如AVL树、红黑树）来优化

2. **内存管理**：
   - 正确处理节点的内存分配和释放
   - 实现深拷贝以避免内存问题
   - 避免内存泄漏

3. **异常处理**：
   - 处理空树情况
   - 处理不存在的值
   - 提供清晰的错误信息

4. **遍历顺序**：
   - 中序遍历可以得到有序序列
   - 根据需求选择合适的遍历方式

5. **性能优化**：
   - 考虑缓存友好的节点布局
   - 减少不必要的递归调用
   - 适当使用迭代替代递归

6. **并发访问**：
   - BST本身不是线程安全的
   - 需要额外的同步机制
   - 考虑读写锁优化
