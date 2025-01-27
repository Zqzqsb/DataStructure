#ifndef MATRIX_DG_HPP
#define MATRIX_DG_HPP

#include <iostream>
#include <queue>
#include <stack>
#include <vector>
#include <climits>
#include <stdexcept>

template<typename T, size_t MAX_SIZE = 100>
class MatrixDG {
private:
    T vertices[MAX_SIZE];          // 顶点集合
    int vertexNum;                 // 顶点数量
    int edgeNum;                   // 边数
    int matrix[MAX_SIZE][MAX_SIZE]; // 邻接矩阵

public:
    // 使用顶点集合和边集来创建图
    MatrixDG(T* verts, int vNum, T edges[][2], int eNum) {
        if (vNum > MAX_SIZE) {
            throw std::runtime_error("Vertex number exceeds maximum size");
        }

        vertexNum = vNum;
        edgeNum = eNum;
        
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
            
            if (p1 == -1 || p2 == -1) {
                throw std::invalid_argument("Invalid vertex in edge");
            }
            matrix[p1][p2] = 1;  // 有向图，只设置一个方向
        }
    }

    // 使用已知矩阵来创建图
    MatrixDG(T* verts, int vNum, const int mat[][MAX_SIZE]) {
        if (vNum > MAX_SIZE) {
            throw std::runtime_error("Vertex number exceeds maximum size");
        }

        vertexNum = vNum;
        edgeNum = 0;

        // 初始化顶点
        for (int i = 0; i < vertexNum; i++) {
            vertices[i] = verts[i];
        }

        // 复制矩阵并统计边数
        for (int i = 0; i < vertexNum; i++) {
            for (int j = 0; j < vertexNum; j++) {
                matrix[i][j] = mat[i][j];
                if (matrix[i][j]) {
                    edgeNum++;
                }
            }
        }
    }

    // 打印邻接矩阵
    void print() const {
        std::cout << "Adjacency Matrix:" << std::endl;
        for (int i = 0; i < vertexNum; i++) {
            for (int j = 0; j < vertexNum; j++) {
                std::cout << matrix[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }

    // 深度优先搜索（递归版本）
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
                    std::cout << vertices[v] << " ";

                    // 将所有未访问的邻接顶点入栈
                    for (int j = vertexNum - 1; j >= 0; j--) {
                        if (matrix[v][j] && !visited[j]) {
                            s.push(j);
                            visited[j] = true;
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
                    std::cout << vertices[v] << " ";

                    // 将所有未访问的邻接顶点入队
                    for (int j = 0; j < vertexNum; j++) {
                        if (matrix[v][j] && !visited[j]) {
                            q.push(j);
                            visited[j] = true;
                        }
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
        return matrix[p1][p2] != 0;
    }

    // 获取某个顶点的所有出边邻接顶点
    std::vector<T> getOutNeighbors(const T& vertex) const {
        std::vector<T> neighbors;
        int p = getPosition(vertex);
        if (p != -1) {
            for (int i = 0; i < vertexNum; i++) {
                if (matrix[p][i]) {
                    neighbors.push_back(vertices[i]);
                }
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
                if (matrix[i][p]) {
                    neighbors.push_back(vertices[i]);
                }
            }
        }
        return neighbors;
    }

    // 获取某个顶点的入度
    int getInDegree(const T& vertex) const {
        int p = getPosition(vertex);
        if (p == -1) return -1;
        
        int degree = 0;
        for (int i = 0; i < vertexNum; i++) {
            if (matrix[i][p]) {
                degree++;
            }
        }
        return degree;
    }

    // 获取某个顶点的出度
    int getOutDegree(const T& vertex) const {
        int p = getPosition(vertex);
        if (p == -1) return -1;
        
        int degree = 0;
        for (int i = 0; i < vertexNum; i++) {
            if (matrix[p][i]) {
                degree++;
            }
        }
        return degree;
    }

private:
    // 返回顶点在数组中的位置
    int getPosition(const T& vertex) const {
        for (int i = 0; i < vertexNum; i++) {
            if (vertices[i] == vertex) {
                return i;
            }
        }
        return -1;
    }

    // 深度优先搜索的递归辅助函数
    void DFS(int v, std::vector<bool>& visited) {
        visited[v] = true;
        std::cout << vertices[v] << " ";

        for (int i = 0; i < vertexNum; i++) {
            if (matrix[v][i] && !visited[i]) {
                DFS(i, visited);
            }
        }
    }

    // 获取所有顶点的入度
    std::vector<int> getInDegrees() const {
        std::vector<int> inDegree(vertexNum, 0);
        for (int i = 0; i < vertexNum; i++) {
            for (int j = 0; j < vertexNum; j++) {
                if (matrix[j][i]) {
                    inDegree[i]++;
                }
            }
        }
        return inDegree;
    }
};

#endif // MATRIX_DG_HPP
