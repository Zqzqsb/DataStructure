# 邻接矩阵实现的无向图（Matrix-based Undirected Graph）

这是一个使用邻接矩阵实现的无向图数据结构，支持基本的图操作、图遍历以及最小生成树算法。

## 概述

邻接矩阵是实现图的一种方式，它使用一个二维数组来表示顶点之间的连接关系。对于无向图，邻接矩阵是对称的。主要应用场景包括：
- 需要快速判断任意两个顶点之间是否有边
- 图比较稠密（边数接近于顶点数的平方）
- 需要频繁进行图的分析操作
- 空间要求相对不敏感的场景

## 特性

- 基于模板实现，支持任意数据类型的顶点
- 使用二维数组存储边的关系
- 提供完整的图操作接口
- 支持图的遍历（DFS和BFS）
- 实现了Prim最小生成树算法
- 包含边界检查和异常处理

## 核心算法实现思路

### 1. 图的创建

```cpp
MatrixUDG(T* verts, int vNum, T edges[][2], int eNum) {
    // 初始化顶点
    for (int i = 0; i < vertexNum; i++) {
        vertices[i] = verts[i];
    }
    
    // 初始化邻接矩阵
    for (int i = 0; i < MAX_SIZE; i++) {
        for (int j = 0; j < MAX_SIZE; j++) {
            matrix[i][j] = 0;
        }
    }
    
    // 添加边
    int p1, p2;
    for (int j = 0; j < edgeNum; j++) {
        p1 = getPosition(edges[j][0]);
        p2 = getPosition(edges[j][1]);
        matrix[p1][p2] = matrix[p2][p1] = 1;  // 无向图，对称设置
    }
}
```

### 2. 深度优先搜索（DFS）

```cpp
void DFS(int v, std::vector<bool>& visited) {
    visited[v] = true;
    std::cout << vertices[v] << " ";

    for (int i = 0; i < vertexNum; i++) {
        if (matrix[v][i] && !visited[i]) {
            DFS(i, visited);
        }
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
                std::cout << vertices[v] << " ";

                for (int j = 0; j < vertexNum; j++) {
                    if (matrix[v][j] && !visited[j]) {
                        q.push(j);
                        visited[j] = true;
                    }
                }
            }
        }
    }
}
```

### 4. Prim最小生成树算法

```cpp
void Prim(int start) {
    std::vector<int> weights(vertexNum, INT_MAX);
    std::vector<bool> included(vertexNum, false);
    std::vector<int> parent(vertexNum, -1);
    
    weights[start] = 0;
    
    for (int count = 0; count < vertexNum; count++) {
        // 找到权重最小的未包含顶点
        int minWeight = INT_MAX;
        int minIndex = -1;
        
        for (int v = 0; v < vertexNum; v++) {
            if (!included[v] && weights[v] < minWeight) {
                minWeight = weights[v];
                minIndex = v;
            }
        }
        
        included[minIndex] = true;
        
        // 更新相邻顶点的权重
        for (int v = 0; v < vertexNum; v++) {
            if (matrix[minIndex][v] && !included[v] && 
                matrix[minIndex][v] < weights[v]) {
                parent[v] = minIndex;
                weights[v] = matrix[minIndex][v];
            }
        }
    }
}
```

## API 接口说明

### 构造函数
```cpp
// 使用顶点集合和边集来创建图
MatrixUDG(T* verts, int vNum, T edges[][2], int eNum);

// 使用已知矩阵来创建图
MatrixUDG(T* verts, int vNum, const int mat[][MAX_SIZE]);
```

### 基本操作

```cpp
// 打印邻接矩阵
void print() const;

// 获取顶点数量
int getVertexNum() const;

// 获取边数量
int getEdgeNum() const;

// 判断两个顶点之间是否有边
bool hasEdge(const T& v1, const T& v2) const;

// 获取某个顶点的所有邻接顶点
std::vector<T> getNeighbors(const T& vertex) const;
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
#include "MatrixUDG.hpp"

int main() {
    // 创建图
    char vertices[] = {'A', 'B', 'C', 'D'};
    char edges[][2] = {
        {'A', 'B'},
        {'B', 'C'},
        {'C', 'D'},
        {'D', 'A'}
    };
    
    MatrixUDG<char> graph(vertices, 4, edges, 4);
    
    // 打印邻接矩阵
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
| 创建图 | O(V²) | O(V²) |
| 添加边 | O(1) | O(1) |
| 删除边 | O(1) | O(1) |
| 查找边 | O(1) | O(1) |
| 获取邻接点 | O(V) | O(V) |
| DFS | O(V²) | O(V) |
| BFS | O(V²) | O(V) |
| Prim | O(V²) | O(V) |

其中，V是顶点数量。

## 优缺点分析

### 优点
1. 实现简单，直观
2. 适合稠密图
3. 查找、修改边的操作效率高
4. 实现某些图算法时较为方便

### 缺点
1. 空间复杂度固定为O(V²)
2. 对于稀疏图来说浪费空间
3. 添加/删除顶点的操作效率低
4. 需要预先知道最大顶点数

## 注意事项

1. **内存使用**：
   - 合理设置最大顶点数
   - 注意空间使用效率
   - 考虑是否适合稀疏图

2. **边的处理**：
   - 注意无向图的对称性
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
