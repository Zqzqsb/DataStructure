# 二叉树（Binary Tree）

这是一个模板化的二叉树基类实现，提供了基本的树操作和多种遍历方式。这个类作为其他特定二叉树（如二叉搜索树、AVL树等）的基类，提供了共同的基础功能。

## 概述

二叉树是一种基础的树形数据结构，每个节点最多有两个子节点，分别称为左子节点和右子节点。本实现提供了二叉树的基本操作和多种遍历方式，包括递归和非递归实现。

## 特性

- 基于模板实现，支持任意数据类型
- 提供基本的树操作（获取大小、高度等）
- 实现多种遍历方式：
  - 前序遍历（递归和非递归）
  - 中序遍历（递归和非递归）
  - 后序遍历（递归和非递归）
  - 层序遍历
- 支持拷贝构造和赋值操作
- 完整的内存管理

## 核心实现思路

### 1. 节点结构
```cpp
struct Node {
    T data;
    Node* left;
    Node* right;
    
    Node(const T& value) : data(value), left(nullptr), right(nullptr) {}
};
```

### 2. 遍历算法

#### 递归实现
递归实现简单直观，以中序遍历为例：
```cpp
void inOrder(Node* node) const {
    if (node == nullptr) {
        return;
    }
    inOrder(node->left);
    std::cout << node->data << " ";
    inOrder(node->right);
}
```

#### 非递归实现
使用栈来模拟递归过程，以中序遍历为例：
```cpp
void inOrderNonRecursive() const {
    if (root == nullptr) {
        return;
    }

    std::stack<Node*> s;
    Node* current = root;

    while (current != nullptr || !s.empty()) {
        while (current != nullptr) {
            s.push(current);
            current = current->left;
        }

        current = s.top();
        s.pop();
        std::cout << current->data << " ";
        current = current->right;
    }
}
```

#### 层序遍历
使用队列实现：
```cpp
void levelOrder() const {
    if (root == nullptr) {
        return;
    }

    std::queue<Node*> q;
    q.push(root);

    while (!q.empty()) {
        Node* current = q.front();
        q.pop();
        std::cout << current->data << " ";

        if (current->left) {
            q.push(current->left);
        }
        if (current->right) {
            q.push(current->right);
        }
    }
}
```

## API 接口说明

### 构造和析构
```cpp
// 默认构造函数
BinTree();

// 虚析构函数
virtual ~BinTree();

// 拷贝构造函数
BinTree(const BinTree& other);

// 赋值运算符
BinTree& operator=(const BinTree& other);
```

### 基本操作

```cpp
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
// 递归遍历
void preOrder() const;
void inOrder() const;
void postOrder() const;

// 非递归遍历
void preOrderNonRecursive() const;
void inOrderNonRecursive() const;
void postOrderNonRecursive() const;

// 层序遍历
void levelOrder() const;
```

## 使用示例

```cpp
#include "BinTree.hpp"

// 创建一个测试用的二叉树类
template<typename T>
class TestBinTree : public BinTree<T> {
public:
    // 用于测试的插入函数
    void insert(const T& value, const std::string& path) {
        // 根据路径字符串插入节点
        // 'L'表示左子树，'R'表示右子树
    }
};

int main() {
    TestBinTree<int> tree;
    
    // 构建测试树
    tree.insert(1, "");      // 根节点
    tree.insert(2, "L");     // 左子节点
    tree.insert(3, "R");     // 右子节点
    tree.insert(4, "LL");    // 左子节点的左子节点
    
    // 遍历树
    tree.preOrder();     // 前序遍历
    tree.inOrder();      // 中序遍历
    tree.postOrder();    // 后序遍历
    tree.levelOrder();   // 层序遍历
    
    return 0;
}
```

## 复杂度分析

| 操作 | 时间复杂度 | 空间复杂度 |
|-----|-----------|-----------|
| 获取大小 | O(1) | O(1) |
| 获取高度 | O(n) | O(h) |
| 递归遍历 | O(n) | O(h) |
| 非递归遍历 | O(n) | O(h) |
| 层序遍历 | O(n) | O(w) |

其中：
- n 是树中节点的数量
- h 是树的高度
- w 是树的最大宽度

## 优缺点分析

### 优点
1. 实现清晰，易于理解和扩展
2. 提供了多种遍历方式的实现
3. 良好的内存管理
4. 可作为其他二叉树实现的基类

### 缺点
1. 基类本身不提供插入和删除操作
2. 遍历操作直接输出到标准输出，不够灵活
3. 没有实现迭代器接口

## 应用场景

1. **作为基类**：
   - 二叉搜索树
   - AVL树
   - 红黑树
   - 其他特殊的二叉树实现

2. **教学用途**：
   - 学习树的基本概念
   - 理解不同的遍历算法
   - 练习递归和非递归实现

## 注意事项

1. **内存管理**：
   - 注意析构函数的正确实现
   - 避免内存泄漏
   - 正确处理深拷贝

2. **继承使用**：
   - 注意虚析构函数的重要性
   - protected成员的访问控制
   - 子类的正确实现

3. **遍历实现**：
   - 理解递归和非递归的区别
   - 注意栈空间的使用
   - 考虑遍历的效率

4. **异常安全**：
   - 保证异常安全性
   - 正确处理内存分配失败
   - 维护类的不变量

5. **扩展性**：
   - 预留足够的扩展空间
   - 考虑未来的功能添加
   - 保持接口的一致性

6. **性能考虑**：
   - 注意递归深度
   - 合理使用栈和队列
   - 优化遍历性能
