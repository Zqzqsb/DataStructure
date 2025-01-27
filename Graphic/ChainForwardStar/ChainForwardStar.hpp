#ifndef CHAIN_FORWARD_STAR_HPP
#define CHAIN_FORWARD_STAR_HPP

#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <climits>
#include <stdexcept>

template<typename T, size_t MAX_EDGES = 1000>
class ChainForwardStar {
private:
    struct Edge {
        int to;         // 边的终点
        int weight;     // 边的权重
        int next;       // 与该边同起点的下一条边的编号
        
        Edge(int t = 0, int w = 0, int n = -1) : to(t), weight(w), next(n) {}
    };

    std::vector<T> vertices;     // 顶点数组
    std::vector<Edge> edges;     // 边数组
    std::vector<int> head;       // head[i]表示以i为起点的第一条边的编号
    int edgeCount;              // 当前边的数量
    bool isDirected;            // 是否为有向图

public:
    ChainForwardStar(int vertexNum, bool directed = true) 
        : vertices(vertexNum), head(vertexNum, -1), edgeCount(0), isDirected(directed) {
        edges.reserve(MAX_EDGES);
    }

    // 添加边
    void addEdge(int from, int to, int weight = 1) {
        if (from < 0 || from >= vertices.size() || 
            to < 0 || to >= vertices.size()) {
            throw std::out_of_range("Vertex index out of range");
        }

        if (edgeCount >= MAX_EDGES) {
            throw std::runtime_error("Maximum number of edges exceeded");
        }

        // 添加边 from -> to
        edges.emplace_back(to, weight, head[from]);
        head[from] = edgeCount++;

        // 如果是无向图，添加反向边
        if (!isDirected) {
            edges.emplace_back(from, weight, head[to]);
            head[to] = edgeCount++;
        }
    }

    // 设置顶点值
    void setVertex(int index, const T& value) {
        if (index < 0 || index >= vertices.size()) {
            throw std::out_of_range("Vertex index out of range");
        }
        vertices[index] = value;
    }

    // 获取顶点值
    T getVertex(int index) const {
        if (index < 0 || index >= vertices.size()) {
            throw std::out_of_range("Vertex index out of range");
        }
        return vertices[index];
    }

    // 获取顶点数量
    int getVertexCount() const {
        return vertices.size();
    }

    // 获取边数量
    int getEdgeCount() const {
        return isDirected ? edgeCount : edgeCount / 2;
    }

    // 判断是否存在从from到to的边
    bool hasEdge(int from, int to) const {
        if (from < 0 || from >= vertices.size() || 
            to < 0 || to >= vertices.size()) {
            return false;
        }

        for (int i = head[from]; i != -1; i = edges[i].next) {
            if (edges[i].to == to) {
                return true;
            }
        }
        return false;
    }

    // 获取从from到to的边的权重，如果边不存在返回INT_MAX
    int getWeight(int from, int to) const {
        if (from < 0 || from >= vertices.size() || 
            to < 0 || to >= vertices.size()) {
            return INT_MAX;
        }

        for (int i = head[from]; i != -1; i = edges[i].next) {
            if (edges[i].to == to) {
                return edges[i].weight;
            }
        }
        return INT_MAX;
    }

    // 获取顶点的出度
    int getOutDegree(int vertex) const {
        if (vertex < 0 || vertex >= vertices.size()) {
            return -1;
        }

        int degree = 0;
        for (int i = head[vertex]; i != -1; i = edges[i].next) {
            degree++;
        }
        return degree;
    }

    // 获取顶点的入度
    int getInDegree(int vertex) const {
        if (vertex < 0 || vertex >= vertices.size()) {
            return -1;
        }

        int degree = 0;
        for (int i = 0; i < vertices.size(); i++) {
            for (int j = head[i]; j != -1; j = edges[j].next) {
                if (edges[j].to == vertex) {
                    degree++;
                }
            }
        }
        return degree;
    }

    // 深度优先搜索
    void DFS() const {
        std::vector<bool> visited(vertices.size(), false);
        std::cout << "DFS traversal: ";
        
        for (int i = 0; i < vertices.size(); i++) {
            if (!visited[i]) {
                DFS(i, visited);
            }
        }
        std::cout << std::endl;
    }

    // 广度优先搜索
    void BFS() const {
        std::vector<bool> visited(vertices.size(), false);
        std::queue<int> q;
        std::cout << "BFS traversal: ";

        for (int i = 0; i < vertices.size(); i++) {
            if (!visited[i]) {
                q.push(i);
                visited[i] = true;

                while (!q.empty()) {
                    int v = q.front();
                    q.pop();
                    std::cout << vertices[v] << " ";

                    for (int j = head[v]; j != -1; j = edges[j].next) {
                        int u = edges[j].to;
                        if (!visited[u]) {
                            q.push(u);
                            visited[u] = true;
                        }
                    }
                }
            }
        }
        std::cout << std::endl;
    }

    // 拓扑排序（仅适用于有向无环图）
    bool topologicalSort() const {
        if (!isDirected) {
            throw std::runtime_error("Topological sort is only applicable to directed graphs");
        }

        std::vector<int> inDegree(vertices.size(), 0);
        std::queue<int> q;
        std::vector<T> result;

        // 计算入度
        for (int i = 0; i < vertices.size(); i++) {
            for (int j = head[i]; j != -1; j = edges[j].next) {
                inDegree[edges[j].to]++;
            }
        }

        // 将入度为0的顶点入队
        for (int i = 0; i < vertices.size(); i++) {
            if (inDegree[i] == 0) {
                q.push(i);
            }
        }

        while (!q.empty()) {
            int v = q.front();
            q.pop();
            result.push_back(vertices[v]);

            for (int i = head[v]; i != -1; i = edges[i].next) {
                int u = edges[i].to;
                if (--inDegree[u] == 0) {
                    q.push(u);
                }
            }
        }

        if (result.size() < vertices.size()) {
            std::cout << "Graph contains a cycle!" << std::endl;
            return false;
        }

        std::cout << "Topological sort result: ";
        for (const T& vertex : result) {
            std::cout << vertex << " ";
        }
        std::cout << std::endl;
        return true;
    }

    // 打印图的结构
    void print() const {
        std::cout << "Chain Forward Star structure:" << std::endl;
        for (int i = 0; i < vertices.size(); i++) {
            std::cout << vertices[i] << " -> ";
            for (int j = head[i]; j != -1; j = edges[j].next) {
                std::cout << vertices[edges[j].to];
                if (edges[j].weight != 1) {
                    std::cout << "(" << edges[j].weight << ")";
                }
                if (edges[j].next != -1) {
                    std::cout << " -> ";
                }
            }
            std::cout << std::endl;
        }
    }

private:
    // 深度优先搜索的递归辅助函数
    void DFS(int v, std::vector<bool>& visited) const {
        visited[v] = true;
        std::cout << vertices[v] << " ";

        for (int i = head[v]; i != -1; i = edges[i].next) {
            int u = edges[i].to;
            if (!visited[u]) {
                DFS(u, visited);
            }
        }
    }
};

#endif // CHAIN_FORWARD_STAR_HPP
