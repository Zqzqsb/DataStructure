#ifndef LIST_DG_HPP
#define LIST_DG_HPP

#include <iostream>
#include <queue>
#include <stack>
#include <vector>
#include <climits>
#include <stdexcept>

template<typename T, size_t MAX_SIZE = 100>
class ListDG {
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
    ListDG(T* verts, int vNum, T edges[][2], int eNum) {
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
            EdgeNode* edge = new EdgeNode(p2);
            edge->next = vertices[p1].firstEdge;
            vertices[p1].firstEdge = edge;
        }
    }

    // 析构函数
    ~ListDG() {
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
        
        // 对每个未访问的顶点进行DFS
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

    // 拓扑排序
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
            result.push_back(vertices[v].data);

            // 将所有v指向的顶点的入度减1
            EdgeNode* current = vertices[v].firstEdge;
            while (current != nullptr) {
                inDegree[current->index]--;
                if (inDegree[current->index] == 0) {
                    q.push(current->index);
                }
                current = current->next;
            }
        }

        // 如果结果中的顶点数小于图中的顶点数，说明图中有环
        if (result.size() < vertexNum) {
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

    // 获取顶点数量
    int getVertexNum() const {
        return vertexNum;
    }

    // 获取边数量
    int getEdgeNum() const {
        return edgeNum;
    }

    // 判断从v1到v2是否有边
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

    // 获取某个顶点的所有出边邻接顶点
    std::vector<T> getOutNeighbors(const T& vertex) const {
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

    // 获取某个顶点的所有入边邻接顶点
    std::vector<T> getInNeighbors(const T& vertex) const {
        std::vector<T> neighbors;
        int p = getPosition(vertex);
        if (p != -1) {
            for (int i = 0; i < vertexNum; i++) {
                EdgeNode* current = vertices[i].firstEdge;
                while (current != nullptr) {
                    if (current->index == p) {
                        neighbors.push_back(vertices[i].data);
                        break;
                    }
                    current = current->next;
                }
            }
        }
        return neighbors;
    }

    // 获取顶点的入度
    int getInDegree(const T& vertex) const {
        int p = getPosition(vertex);
        if (p == -1) return -1;

        int degree = 0;
        for (int i = 0; i < vertexNum; i++) {
            EdgeNode* current = vertices[i].firstEdge;
            while (current != nullptr) {
                if (current->index == p) {
                    degree++;
                    break;
                }
                current = current->next;
            }
        }
        return degree;
    }

    // 获取顶点的出度
    int getOutDegree(const T& vertex) const {
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

    // 获取所有顶点的入度
    std::vector<int> getInDegrees() const {
        std::vector<int> inDegree(vertexNum, 0);
        for (int i = 0; i < vertexNum; i++) {
            EdgeNode* current = vertices[i].firstEdge;
            while (current != nullptr) {
                inDegree[current->index]++;
                current = current->next;
            }
        }
        return inDegree;
    }
};

#endif // LIST_DG_HPP
