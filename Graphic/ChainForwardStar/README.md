# 链式前向星（Chain Forward Star）

这是一个使用链式前向星实现的图数据结构。链式前向星是一种高效的图存储方式，特别适合于处理稀疏图。

## 概述

链式前向星是一种介于邻接表和边集数组之间的数据结构，它同时具备这两种结构的优点：
- 像邻接表一样，可以方便地获取一个顶点的所有出边
- 像边集数组一样，使用连续的数组存储，具有较好的缓存性能
- 实现简单，代码量小，易于调试

## 特性

- 基于模板实现，支持任意数据类型的顶点
- 支持有向图和无向图
- 支持带权边
- 提供完整的图操作接口
- 支持图的遍历（DFS和BFS）
- 支持拓扑排序（仅适用于有向无环图）
- 包含边界检查和异常处理
- 支持度的计算

## 实现原理

### 数据结构

```cpp
template<typename T, size_t MAX_EDGES = 1000>
class ChainForwardStar {
    struct Edge {
        int to;         // 边的终点
        int weight;     // 边的权重
        int next;       // 与该边同起点的下一条边的编号
    };

    std::vector<T> vertices;     // 顶点数组
    std::vector<Edge> edges;     // 边数组
    std::vector<int> head;       // head[i]表示以i为起点的第一条边的编号
    int edgeCount;              // 当前边的数量
    bool isDirected;            // 是否为有向图
};
```

### 关键算法

1. **添加边**
```cpp
void addEdge(int from, int to, int weight = 1) {
    // 添加边 from -> to
    edges.emplace_back(to, weight, head[from]);
    head[from] = edgeCount++;

    // 如果是无向图，添加反向边
    if (!isDirected) {
        edges.emplace_back(from, weight, head[to]);
        head[to] = edgeCount++;
    }
}
```

2. **遍历顶点的所有出边**
```cpp
for (int i = head[vertex]; i != -1; i = edges[i].next) {
    int to = edges[i].to;
    int weight = edges[i].weight;
    // 处理边(vertex, to, weight)
}
```

## API 接口说明

### 构造函数
```cpp
// 创建一个具有vertexNum个顶点的图，可以指定是否为有向图
ChainForwardStar(int vertexNum, bool directed = true);
```

### 基本操作

```cpp
// 添加边
void addEdge(int from, int to, int weight = 1);

// 设置顶点值
void setVertex(int index, const T& value);

// 获取顶点值
T getVertex(int index) const;

// 获取顶点数量
int getVertexCount() const;

// 获取边数量
int getEdgeCount() const;

// 判断是否存在从from到to的边
bool hasEdge(int from, int to) const;

// 获取从from到to的边的权重
int getWeight(int from, int to) const;

// 获取顶点的出度/入度
int getOutDegree(int vertex) const;
int getInDegree(int vertex) const;
```

### 图遍历

```cpp
// 深度优先搜索
void DFS() const;

// 广度优先搜索
void BFS() const;

// 拓扑排序（仅适用于有向无环图）
bool topologicalSort() const;
```

## 使用示例

```cpp
#include "ChainForwardStar.hpp"

int main() {
    // 创建一个有4个顶点的有向图
    ChainForwardStar<char> graph(4);
    
    // 设置顶点值
    graph.setVertex(0, 'A');
    graph.setVertex(1, 'B');
    graph.setVertex(2, 'C');
    graph.setVertex(3, 'D');
    
    // 添加边
    graph.addEdge(0, 1);  // A -> B
    graph.addEdge(1, 2);  // B -> C
    graph.addEdge(2, 3);  // C -> D
    graph.addEdge(3, 0);  // D -> A
    
    // 打印图结构
    graph.print();
    
    // 图遍历
    graph.DFS();  // 深度优先搜索
    graph.BFS();  // 广度优先搜索
    
    return 0;
}
```

## 复杂度分析

| 操作 | 时间复杂度 | 空间复杂度 |
|-----|-----------|------------|
| 创建图 | O(V) | O(V + E) |
| 添加边 | O(1) | O(1) |
| 查找边 | O(E/V) | O(1) |
| 获取顶点的所有出边 | O(out_degree) | O(1) |
| DFS | O(V + E) | O(V) |
| BFS | O(V + E) | O(V) |
| 拓扑排序 | O(V + E) | O(V) |

其中，V是顶点数量，E是边数量。

## 优缺点分析

### 优点
1. 空间效率高，特别适合稀疏图
2. 边的存储是连续的，具有良好的缓存性能
3. 实现简单，代码量小
4. 适合需要快速遍历某个顶点所有出边的场景

### 缺点
1. 不支持删除边操作
2. 需要预先知道最大边数
3. 查找特定边的效率不如邻接矩阵
4. 获取顶点的入度需要遍历所有边

## 应用场景

1. **网络流问题**：链式前向星结构特别适合网络流算法，如最大流、最小费用最大流等

2. **图的遍历**：高效支持图的DFS和BFS遍历

3. **最短路径**：适用于Dijkstra、Bellman-Ford等最短路径算法

4. **拓扑排序**：支持有向无环图的拓扑排序

5. **稀疏图处理**：当图比较稀疏时，链式前向星比邻接矩阵更节省空间

## 注意事项

1. **内存管理**：
   - 预分配足够的边空间
   - 注意边数量的限制

2. **边的添加**：
   - 注意有向图和无向图的区别
   - 处理平行边的情况
   - 注意边权重的合法性

3. **遍历实现**：
   - 处理非连通图的情况
   - 注意访问标记的重置
   - 考虑递归栈溢出的风险

4. **拓扑排序**：
   - 仅适用于有向无环图
   - 需要正确处理环的检测

5. **异常处理**：
   - 检查输入参数的合法性
   - 处理边数超限的情况
   - 提供清晰的错误信息
