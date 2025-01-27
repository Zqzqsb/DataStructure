# 并查集（Union-Find）数据结构实现

这是一个基于模板的C++并查集实现，包含路径压缩和按秩合并优化。

## 概述

并查集是一种用于维护不相交集合的数据结构。它主要应用于：
- 查找图中的连通分量
- 检测图中的环
- 实现 Kruskal 最小生成树算法
- 网络连接问题
- 图像处理中的连通区域标记

## 特性

- 基于模板实现，支持任意数据类型
- 使用路径压缩优化查找操作
- 使用按秩合并优化合并操作
- 常数时间的连通性检查
- 异常安全的错误处理
- 支持拷贝构造和赋值操作
- const 正确性实现

## 核心算法实现思路

### 1. 查找操作（Find）

查找操作用于找到元素所属集合的代表元素（根节点）。实现中使用了路径压缩优化：

```cpp
int find(int x) {
    if (x != parent[x]) {
        parent[x] = find(parent[x]);  // 路径压缩
    }
    return parent[x];
}
```

实现要点：
1. **路径压缩原理**：
   - 在查找过程中，将路径上的所有节点直接连接到根节点
   - 这样可以显著减少树的高度，提高后续操作的效率
   - 压缩后的路径长度为 O(1)，极大提升了查找效率

2. **注意事项**：
   - 需要处理数组越界情况
   - const 成员函数中不能修改父节点数组，需要单独实现一个不压缩路径的版本
   - 路径压缩不会改变集合的代表元素，只是优化了数据结构

### 2. 合并操作（Merge/Union）

合并操作用于将两个集合合并为一个。实现中使用了按秩合并优化：

```cpp
void merge(int x, int y) {
    int rootX = find(x);
    int rootY = find(y);
    
    if (rootX == rootY) return;  // 已经在同一集合中
    
    // 按秩合并
    if (rank[rootX] < rank[rootY]) {
        parent[rootX] = rootY;
    }
    else if (rank[rootX] > rank[rootY]) {
        parent[rootY] = rootX;
    }
    else {
        parent[rootX] = rootY;
        rank[rootY]++;
    }
}
```

实现要点：
1. **按秩合并原理**：
   - 秩（rank）表示树的高度的上界
   - 总是将较矮的树连接到较高的树的根节点上
   - 如果两棵树高度相同，随意选择一棵作为父树，并将其高度加1

2. **注意事项**：
   - 在合并前必须先找到两个元素的根节点
   - 需要检查两个元素是否已经在同一集合中
   - 合并操作会改变树的结构，影响后续查找
   - 结合路径压缩使用时，rank 不再精确等于树高，但仍然是树高的上界

## API 接口说明

### 构造函数

```cpp
explicit UnionSet(int size);
```
- 创建一个包含 size 个元素的并查集
- 初始时每个元素都在独立的集合中
- 如果 size ≤ 0 则抛出 std::invalid_argument 异常
- 时间复杂度：O(n)

### 核心操作

```cpp
void merge(int x, int y);
```
- 合并包含元素 x 和 y 的集合
- 使用按秩合并进行优化
- 如果索引无效则抛出 std::out_of_range 异常
- 时间复杂度：平均 O(α(n))，其中 α 是阿克曼函数的反函数

```cpp
int find(int x);
```
- 查找元素 x 所在集合的代表元素
- 使用路径压缩进行优化
- 如果索引无效则抛出 std::out_of_range 异常
- 时间复杂度：平均 O(α(n))

```cpp
bool isConnected(int x, int y) const;
```
- 检查元素 x 和 y 是否在同一个集合中
- 如果索引无效则抛出 std::out_of_range 异常
- 时间复杂度：平均 O(α(n))

### 数据管理

```cpp
void setData(int index, const T& value);
T getData(int index) const;
```
- 设置/获取元素关联的数据
- 如果索引无效则抛出 std::out_of_range 异常
- 时间复杂度：O(1)

### 工具函数

```cpp
int getSize() const;     // 返回元素总数，O(1)
int getSetCount() const; // 返回当前不相交集合的数量，O(n)
int getRank(int x) const; // 返回元素 x 所在集合的秩，O(1)
```

## 复杂度分析

| 操作        | 时间复杂度（平均） |
|------------|-----------------|
| 构造       | O(n)           |
| 查找       | O(α(n))        |
| 合并       | O(α(n))        |
| 连通性检查  | O(α(n))        |
| 获取数据    | O(1)           |
| 设置数据    | O(1)           |
| 获取大小    | O(1)           |
| 获取集合数量 | O(n)           |
| 获取秩      | O(1)           |

其中：
- n 是元素数量
- α(n) 是阿克曼函数的反函数，对于任何实际应用中的 n 值都可以认为是一个极小的常数（≤4）

## 使用示例

```cpp
#include "UnionSet.hpp"
#include <string>

// 创建一个存储字符串的并查集，大小为5
UnionSet<std::string> set(5);

// 设置元素数据
set.setData(0, "苹果");
set.setData(1, "香蕉");
set.setData(2, "樱桃");
set.setData(3, "枣");
set.setData(4, "接骨木果");

// 合并集合
set.merge(0, 1);  // 合并苹果和香蕉
set.merge(2, 3);  // 合并樱桃和枣

// 检查连通性
bool connected = set.isConnected(0, 1);  // true
bool separate = set.isConnected(0, 2);   // false

// 获取不相交集合的数量
int setCount = set.getSetCount();  // 3个集合
```

## 测试

实现包含了完整的测试套件（UnionSetTest.cpp），验证了：
- 基本操作（创建、数据访问）
- 合并和查找操作
- 拷贝构造和赋值
- 边界情况和错误处理
- 使用不同类型的模板功能
