# 邻接矩阵实现的有向图（Matrix-based Directed Graph）

这是一个使用邻接矩阵实现的有向图数据结构，支持基本的图操作、图遍历以及拓扑排序算法。

## 概述

邻接矩阵是实现图的一种方式，它使用一个二维数组来表示顶点之间的连接关系。对于有向图，邻接矩阵不一定是对称的。主要应用场景包括：
- 需要快速判断任意两个顶点之间是否有边
- 图比较稠密（边数接近于顶点数的平方）
- 需要频繁进行图的分析操作
- 空间要求相对不敏感的场景

## 特性

- 基于模板实现，支持任意数据类型的顶点
- 使用二维数组存储边的关系
- 提供完整的图操作接口
- 支持图的遍历（DFS和BFS）
- 实现了拓扑排序算法
- 包含边界检查和异常处理
- 支持入度和出度的计算

## 核心算法实现思路

### 1. 图的创建

```cpp
MatrixDG(T* verts, int vNum, T edges[][2], int eNum) {
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
        matrix[p1][p2] = 1;  // 有向图，只设置一个方向
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

### 4. 拓扑排序

```cpp
bool topologicalSort() {
    std::vector<int> inDegree = getInDegrees();
    std::queue<int> q;
    std::vector<T> result;

    // 将所有入度为0的顶点入队
    for (int i = 0; i < vertexNum; i++) {
        if (inDegree[i] == 0) {
            q.push(i);
        }
    }

    while (!q.empty()) {
        int v = q.front();
        q.pop();
        result.push_back(vertices[v]);

        // 将所有v指向的顶点的入度减1
        for (int i = 0; i < vertexNum; i++) {
            if (matrix[v][i]) {
                inDegree[i]--;
                if (inDegree[i] == 0) {
                    q.push(i);
                }
            }
        }
    }

    return result.size() == vertexNum;
}
```

## API 接口说明

### 构造函数
```cpp
// 使用顶点集合和边集来创建图
MatrixDG(T* verts, int vNum, T edges[][2], int eNum);

// 使用已知矩阵来创建图
MatrixDG(T* verts, int vNum, const int mat[][MAX_SIZE]);
```

### 基本操作

```cpp
// 打印邻接矩阵
void print() const;

// 获取顶点数量
int getVertexNum() const;

// 获取边数量
int getEdgeNum() const;

// 判断从v1到v2是否有边
bool hasEdge(const T& v1, const T& v2) const;

// 获取某个顶点的所有出边邻接顶点
std::vector<T> getOutNeighbors(const T& vertex) const;

// 获取某个顶点的所有入边邻接顶点
std::vector<T> getInNeighbors(const T& vertex) const;

// 获取某个顶点的入度
int getInDegree(const T& vertex) const;

// 获取某个顶点的出度
int getOutDegree(const T& vertex) const;
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

### 拓扑排序

```cpp
// 拓扑排序，如果图中有环则返回false
bool topologicalSort();
```

## 使用示例

```cpp
#include "MatrixDG.hpp"

int main() {
    // 创建图
    char vertices[] = {'A', 'B', 'C', 'D'};
    char edges[][2] = {
        {'A', 'B'},
        {'B', 'C'},
        {'C', 'D'}
    };
    
    MatrixDG<char> graph(vertices, 4, edges, 3);
    
    // 打印邻接矩阵
    graph.print();
    
    // 图遍历
    graph.DFS();    // 深度优先搜索
    graph.BFS();    // 广度优先搜索
    
    // 拓扑排序
    if (graph.topologicalSort()) {
        std::cout << "Graph is a DAG" << std::endl;
    }
    
    // 其他操作
    if (graph.hasEdge('A', 'B')) {
        std::cout << "Edge A->B exists" << std::endl;
    }
    
    auto outNeighbors = graph.getOutNeighbors('B');
    std::cout << "Out-neighbors of B: ";
    for (const auto& v : outNeighbors) {
        std::cout << v << " ";
    }
    std::cout << std::endl;
    
    auto inNeighbors = graph.getInNeighbors('B');
    std::cout << "In-neighbors of B: ";
    for (const auto& v : inNeighbors) {
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
| 拓扑排序 | O(V²) | O(V) |
| 计算入度/出度 | O(V) | O(1) |

其中，V是顶点数量。

## 优缺点分析

### 优点
1. 实现简单，直观
2. 适合稠密图
3. 查找、修改边的操作效率高
4. 方便计算入度和出度
5. 适合进行矩阵运算

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
   - 注意有向边的方向性
   - 正确处理自环
   - 处理平行边的情况

3. **遍历实现**：
   - 处理非连通图的情况
   - 注意访问标记的重置
   - 考虑递归栈溢出的风险

4. **拓扑排序**：
   - 检查图是否有环
   - 处理非DAG的情况
   - 考虑多个合法排序序列

5. **异常处理**：
   - 检查输入参数的合法性
   - 处理内存分配失败的情况
   - 提供清晰的错误信息
