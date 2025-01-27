#ifndef LIST_UDG_HPP
#define LIST_UDG_HPP

#include <iostream>
#include <queue>
#include <stack>
#include <vector>
#include <climits>
#include <stdexcept>

template<typename T, size_t MAX_SIZE = 100>
class ListUDG {
private:
    // 边节点结构
    struct EdgeNode {
        int index;              // 该边指向顶点的位置
        int weight;             // 该条边的权重
        EdgeNode* next;         // 下一条边的指针
        
        EdgeNode(int idx, int w = 1) : index(idx), weight(w), next(nullptr) {}
    };

    // 顶点节点结构
    struct VertexNode {
        T data;                // 顶点数据
        EdgeNode* firstEdge;   // 第一条边的指针
        
        VertexNode() : firstEdge(nullptr) {}
        explicit VertexNode(T d) : data(d), firstEdge(nullptr) {}
    };

    VertexNode vertices[MAX_SIZE];  // 顶点数组
    int vertexNum;                  // 顶点数量
    int edgeNum;                    // 边数量

public:
    // 使用顶点集合和边集来创建图
    ListUDG(T* verts, int vNum, T edges[][2], int eNum) {
        if (vNum > MAX_SIZE) {
            throw std::runtime_error("Vertex number exceeds maximum size");
        }

        vertexNum = vNum;
        edgeNum = eNum;
        
        // 初始化顶点
        for (int i = 0; i < vertexNum; i++) {
            vertices[i].data = verts[i];
        }
        
        // 添加边
        int p1, p2;
        for (int i = 0; i < edgeNum; i++) {
            p1 = getPosition(edges[i][0]);
            p2 = getPosition(edges[i][1]);
            
            if (p1 == -1 || p2 == -1) {
                throw std::invalid_argument("Invalid vertex in edge");
            }

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

    // 析构函数
    ~ListUDG() {
        // 释放所有边节点
        for (int i = 0; i < vertexNum; i++) {
            EdgeNode* current = vertices[i].firstEdge;
            while (current != nullptr) {
                EdgeNode* temp = current;
                current = current->next;
                delete temp;
            }
        }
    }

    // 打印邻接表
    void print() const {
        std::cout << "Adjacency List:" << std::endl;
        for (int i = 0; i < vertexNum; i++) {
            std::cout << vertices[i].data << " -> ";
            EdgeNode* current = vertices[i].firstEdge;
            while (current != nullptr) {
                std::cout << vertices[current->index].data;
                if (current->next != nullptr) {
                    std::cout << " -> ";
                }
                current = current->next;
            }
            std::cout << std::endl;
        }
    }

    // 深度优先搜索
    void DFS() {
        std::vector<bool> visited(vertexNum, false);
        std::cout << "DFS traversal: ";
        
        for (int i = 0; i < vertexNum; i++) {
            if (!visited[i]) {
                DFS(i, visited);
            }
        }
        std::cout << std::endl;
    }

    // 深度优先搜索（非递归版本）
    void DFS_NoRecursive() {
        std::vector<bool> visited(vertexNum, false);
        std::stack<int> s;
        std::cout << "Non-recursive DFS traversal: ";

        for (int i = 0; i < vertexNum; i++) {
            if (!visited[i]) {
                s.push(i);
                visited[i] = true;

                while (!s.empty()) {
                    int v = s.top();
                    s.pop();
                    std::cout << vertices[v].data << " ";

                    // 将所有未访问的邻接顶点入栈
                    EdgeNode* current = vertices[v].firstEdge;
                    std::stack<int> temp;  // 用于反转邻接点的顺序
                    while (current != nullptr) {
                        if (!visited[current->index]) {
                            temp.push(current->index);
                        }
                        current = current->next;
                    }
                    while (!temp.empty()) {
                        int w = temp.top();
                        temp.pop();
                        if (!visited[w]) {
                            s.push(w);
                            visited[w] = true;
                        }
                    }
                }
            }
        }
        std::cout << std::endl;
    }

    // 广度优先搜索
    void BFS() {
        std::vector<bool> visited(vertexNum, false);
        std::queue<int> q;
        std::cout << "BFS traversal: ";

        for (int i = 0; i < vertexNum; i++) {
            if (!visited[i]) {
                q.push(i);
                visited[i] = true;

                while (!q.empty()) {
                    int v = q.front();
                    q.pop();
                    std::cout << vertices[v].data << " ";

                    // 将所有未访问的邻接顶点入队
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
        std::cout << std::endl;
    }

    // 最小生成树 Prim 算法
    void Prim(int start) {
        if (start < 0 || start >= vertexNum) {
            throw std::invalid_argument("Invalid starting vertex");
        }

        std::vector<bool> included(vertexNum, false);
        std::vector<int> weights(vertexNum, INT_MAX);
        std::vector<int> parent(vertexNum, -1);
        int totalWeight = 0;

        weights[start] = 0;

        std::cout << "Prim's MST starting from " << vertices[start].data << ":" << std::endl;

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

            if (minIndex == -1) break;  // 图不连通

            included[minIndex] = true;
            totalWeight += minWeight;

            // 打印边
            if (parent[minIndex] != -1) {
                std::cout << vertices[parent[minIndex]].data << " -- " 
                         << vertices[minIndex].data << " : " 
                         << weights[minIndex] << std::endl;
            }

            // 更新相邻顶点的权重
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

        std::cout << "Total MST weight: " << totalWeight << std::endl;
    }

    // 获取顶点数量
    int getVertexNum() const {
        return vertexNum;
    }

    // 获取边数量
    int getEdgeNum() const {
        return edgeNum;
    }

    // 判断两个顶点之间是否有边
    bool hasEdge(const T& v1, const T& v2) const {
        int p1 = getPosition(v1);
        int p2 = getPosition(v2);
        if (p1 == -1 || p2 == -1) return false;

        EdgeNode* current = vertices[p1].firstEdge;
        while (current != nullptr) {
            if (current->index == p2) return true;
            current = current->next;
        }
        return false;
    }

    // 获取某个顶点的所有邻接顶点
    std::vector<T> getNeighbors(const T& vertex) const {
        std::vector<T> neighbors;
        int p = getPosition(vertex);
        if (p != -1) {
            EdgeNode* current = vertices[p].firstEdge;
            while (current != nullptr) {
                neighbors.push_back(vertices[current->index].data);
                current = current->next;
            }
        }
        return neighbors;
    }

    // 获取顶点的度
    int getDegree(const T& vertex) const {
        int p = getPosition(vertex);
        if (p == -1) return -1;

        int degree = 0;
        EdgeNode* current = vertices[p].firstEdge;
        while (current != nullptr) {
            degree++;
            current = current->next;
        }
        return degree;
    }

private:
    // 返回顶点在数组中的位置
    int getPosition(const T& vertex) const {
        for (int i = 0; i < vertexNum; i++) {
            if (vertices[i].data == vertex) {
                return i;
            }
        }
        return -1;
    }

    // 深度优先搜索的递归辅助函数
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
};

#endif // LIST_UDG_HPP
