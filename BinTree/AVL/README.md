# AVL树（AVL Tree）

这是一个模板化的AVL树实现，AVL树是一种自平衡二叉搜索树。在这种树中，任意节点的两个子树的高度差最多为1。

## 概述

AVL树是以发明者Adelson-Velsky和Landis的名字命名的数据结构。它是最早被发明的自平衡二叉查找树之一。在AVL树中，每个节点的左右子树高度差不超过1，这个性质使得树的高度始终保持在O(log n)，从而保证了基本操作的时间复杂度为O(log n)。

## 特性

- 基于模板实现，支持任意可比较数据类型
- 自动维护树的平衡
- 支持标准的二叉搜索树操作
- 包含多种遍历方式
- 提供完整的错误处理
- 支持拷贝构造和赋值操作

## 核心算法实现思路

### 1. 平衡因子

每个节点都维护一个高度值，平衡因子通过计算左右子树的高度差得到：
```cpp
int getBalanceFactor(Node* node) const {
    if (node == nullptr) {
        return 0;
    }
    return getHeight(node->left) - getHeight(node->right);
}
```

### 2. 旋转操作

#### 右旋转
```cpp
/*
 * 右旋转操作
 *     y                   x
 *    / \                 / \
 *   x   T3   ====>     T1  y
 *  / \                    / \
 * T1  T2                T2  T3
 */
Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    updateHeight(y);
    updateHeight(x);

    return x;
}
```

#### 左旋转
```cpp
/*
 * 左旋转操作
 *   x                      y
 *  / \                    / \
 * T1  y      ====>      x   T3
 *    / \               / \
 *   T2  T3            T1 T2
 */
Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    updateHeight(x);
    updateHeight(y);

    return y;
}
```

### 3. 插入操作

插入节点后，从插入点向上回溯，对于每个节点：
1. 更新节点高度
2. 计算平衡因子
3. 如果不平衡，执行相应的旋转操作：
   - 左左情况：右旋
   - 右右情况：左旋
   - 左右情况：先左旋后右旋
   - 右左情况：先右旋后左旋

### 4. 删除操作

删除节点后，同样需要从删除点向上回溯，维护树的平衡。

## API 接口说明

### 构造和析构
```cpp
// 默认构造函数
AVL();

// 析构函数
~AVL();

// 拷贝构造函数
AVL(const AVL& other);

// 赋值运算符
AVL& operator=(const AVL& other);
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
#include "AVL.hpp"

int main() {
    // 创建AVL树
    AVL<int> tree;
    
    // 插入一些节点
    tree.insert(10);
    tree.insert(5);
    tree.insert(15);
    tree.insert(3);
    tree.insert(7);
    
    // 遍历树
    tree.inOrder();    // 输出：3 5 7 10 15
    tree.levelOrder(); // 输出：10 5 15 3 7
    
    // 删除节点
    tree.remove(5);
    
    // 查找节点
    if (tree.contains(7)) {
        std::cout << "Found 7!" << std::endl;
    }
    
    return 0;
}
```

## 复杂度分析

| 操作 | 平均时间复杂度 | 最坏时间复杂度 | 空间复杂度 |
|-----|--------------|--------------|----------|
| 插入 | O(log n) | O(log n) | O(1) |
| 删除 | O(log n) | O(log n) | O(1) |
| 查找 | O(log n) | O(log n) | O(1) |
| 遍历 | O(n) | O(n) | O(h) |

其中，n是树中节点的数量，h是树的高度。由于AVL树的平衡特性，h = O(log n)。

## 优缺点分析

### 优点
1. 保证了查找、插入和删除操作的时间复杂度为O(log n)
2. 不需要额外的平衡信息
3. 适合频繁查找的场景
4. 实现相对简单，易于理解

### 缺点
1. 需要额外的空间存储高度信息
2. 插入和删除操作可能需要多次旋转
3. 相比红黑树，平衡条件更严格，旋转操作更频繁
4. 不适合频繁插入删除的场景

## 应用场景

1. **数据库索引**：AVL树的高度平衡特性使其适合作为数据库的索引结构

2. **内存管理**：用于管理内存块的分配和释放

3. **文件系统**：用于管理文件系统中的目录结构

4. **词典和拼写检查**：用于存储和快速查找单词

## 注意事项

1. **内存管理**：
   - 注意节点的内存释放
   - 避免内存泄漏
   - 正确处理拷贝构造和赋值操作

2. **平衡维护**：
   - 正确计算平衡因子
   - 正确处理所有旋转情况
   - 注意更新节点高度

3. **异常处理**：
   - 处理空树情况
   - 处理不存在的值
   - 提供清晰的错误信息

4. **性能考虑**：
   - 避免不必要的平衡检查
   - 优化旋转操作
   - 考虑使用智能指针

5. **并发访问**：
   - AVL树本身不是线程安全的
   - 需要额外的同步机制
   - 考虑读写锁优化
