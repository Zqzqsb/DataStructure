# 邻接表实现的无向图（List-based Undirected Graph）

这是一个使用邻接表实现的无向图数据结构，支持基本的图操作、图遍历以及最小生成树算法。

## 概述

邻接表是实现图的一种方式，它使用链表数组来表示顶点之间的连接关系。对于每个顶点，都有一个链表存储与其相邻的顶点。主要应用场景包括：
- 适合表示稀疏图（边数远小于顶点数的平方）
- 需要快速获取顶点的邻接点
- 空间要求敏感的场景
- 需要频繁添加或删除边的场景

## 特性

- 基于模板实现，支持任意数据类型的顶点
- 使用链表数组存储边的关系
- 提供完整的图操作接口
- 支持图的遍历（DFS和BFS）
- 实现了Prim最小生成树算法
- 包含边界检查和异常处理
- 支持度的计算

## 核心算法实现思路

### 1. 图的创建

```cpp
ListUDG(T* verts, int vNum, T edges[][2], int eNum) {
    // 初始化顶点
    for (int i = 0; i < vertexNum; i++) {
        vertices[i].data = verts[i];
    }
    
    // 添加边
    for (int i = 0; i < edgeNum; i++) {
        int p1 = getPosition(edges[i][0]);
        int p2 = getPosition(edges[i][1]);
        
        // 添加边 p1 -> p2
        EdgeNode* edge1 = new EdgeNode(p2);
        edge1->next = vertices[p1].firstEdge;
        vertices[p1].firstEdge = edge1;

        // 添加边 p2 -> p1
        EdgeNode* edge2 = new EdgeNode(p1);
        edge2->next = vertices[p2].firstEdge;
        vertices[p2].firstEdge = edge2;
    }
}
```

### 2. 深度优先搜索（DFS）

```cpp
void DFS(int v, std::vector<bool>& visited) {
    visited[v] = true;
    std::cout << vertices[v].data << " ";

    EdgeNode* current = vertices[v].firstEdge;
    while (current != nullptr) {
        if (!visited[current->index]) {
            DFS(current->index, visited);
        }
        current = current->next;
    }
}
```

### 3. 广度优先搜索（BFS）

```cpp
void BFS() {
    std::vector<bool> visited(vertexNum, false);
    std::queue<int> q;

    for (int i = 0; i < vertexNum; i++) {
        if (!visited[i]) {
            q.push(i);
            visited[i] = true;

            while (!q.empty()) {
                int v = q.front();
                q.pop();
                std::cout << vertices[v].data << " ";

                EdgeNode* current = vertices[v].firstEdge;
                while (current != nullptr) {
                    if (!visited[current->index]) {
                        q.push(current->index);
                        visited[current->index] = true;
                    }
                    current = current->next;
                }
            }
        }
    }
}
```

### 4. Prim最小生成树算法

```cpp
void Prim(int start) {
    std::vector<bool> included(vertexNum, false);
    std::vector<int> weights(vertexNum, INT_MAX);
    std::vector<int> parent(vertexNum, -1);
    
    weights[start] = 0;
    
    for (int count = 0; count < vertexNum; count++) {
        int minIndex = findMinWeight(weights, included);
        if (minIndex == -1) break;
        
        included[minIndex] = true;
        
        EdgeNode* current = vertices[minIndex].firstEdge;
        while (current != nullptr) {
            int v = current->index;
            if (!included[v] && current->weight < weights[v]) {
                parent[v] = minIndex;
                weights[v] = current->weight;
            }
            current = current->next;
        }
    }
}
```

## API 接口说明

### 构造函数
```cpp
// 使用顶点集合和边集来创建图
ListUDG(T* verts, int vNum, T edges[][2], int eNum);
```

### 基本操作

```cpp
// 打印邻接表
void print() const;

// 获取顶点数量
int getVertexNum() const;

// 获取边数量
int getEdgeNum() const;

// 判断两个顶点之间是否有边
bool hasEdge(const T& v1, const T& v2) const;

// 获取某个顶点的所有邻接顶点
std::vector<T> getNeighbors(const T& vertex) const;

// 获取顶点的度
int getDegree(const T& vertex) const;
```

### 图遍历

```cpp
// 深度优先搜索（递归版本）
void DFS();

// 深度优先搜索（非递归版本）
void DFS_NoRecursive();

// 广度优先搜索
void BFS();
```

### 最小生成树

```cpp
// Prim算法
void Prim(int start);
```

## 使用示例

```cpp
#include "ListUDG.hpp"

int main() {
    // 创建图
    char vertices[] = {'A', 'B', 'C', 'D'};
    char edges[][2] = {
        {'A', 'B'},
        {'B', 'C'},
        {'C', 'D'},
        {'D', 'A'}
    };
    
    ListUDG<char> graph(vertices, 4, edges, 4);
    
    // 打印邻接表
    graph.print();
    
    // 图遍历
    graph.DFS();    // 深度优先搜索
    graph.BFS();    // 广度优先搜索
    
    // 最小生成树
    graph.Prim(0);  // 从顶点0开始构建最小生成树
    
    // 其他操作
    if (graph.hasEdge('A', 'B')) {
        std::cout << "Edge A-B exists" << std::endl;
    }
    
    auto neighbors = graph.getNeighbors('B');
    std::cout << "Neighbors of B: ";
    for (const auto& v : neighbors) {
        std::cout << v << " ";
    }
    std::cout << std::endl;
    
    return 0;
}
```

## 复杂度分析

| 操作 | 时间复杂度 | 空间复杂度 |
|-----|-----------|------------|
| 创建图 | O(V + E) | O(V + E) |
| 添加边 | O(1) | O(1) |
| 删除边 | O(E) | O(1) |
| 查找边 | O(E) | O(1) |
| 获取邻接点 | O(E) | O(V) |
| DFS | O(V + E) | O(V) |
| BFS | O(V + E) | O(V) |
| Prim | O(V² + E) | O(V) |

其中，V是顶点数量，E是边数量。

## 优缺点分析

### 优点
1. 空间效率高，特别是对于稀疏图
2. 容易获取顶点的所有邻接点
3. 添加边的操作效率高
4. 适合进行图的遍历操作

### 缺点
1. 不容易判断两个顶点之间是否有边
2. 删除边的操作较复杂
3. 需要额外的空间存储指针
4. 不适合稠密图

## 注意事项

1. **内存管理**：
   - 注意边节点的内存释放
   - 避免内存泄漏
   - 合理管理动态分配的内存

2. **边的处理**：
   - 注意无向边的对称性
   - 正确处理自环
   - 处理平行边的情况

3. **遍历实现**：
   - 处理非连通图的情况
   - 注意访问标记的重置
   - 考虑递归栈溢出的风险

4. **算法选择**：
   - 根据图的特性选择合适的实现方式
   - 考虑空间和时间的平衡
   - 注意算法的适用条件

5. **异常处理**：
   - 检查输入参数的合法性
   - 处理内存分配失败的情况
   - 提供清晰的错误信息
