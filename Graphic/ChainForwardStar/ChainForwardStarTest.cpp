#include "ChainForwardStar.hpp"
#include <cassert>
#include <sstream>

// 辅助函数：捕获标准输出
class CaptureOutput {
    std::stringstream buffer;
    std::streambuf* old;
public:
    CaptureOutput() : old(std::cout.rdbuf(buffer.rdbuf())) {}
    ~CaptureOutput() { std::cout.rdbuf(old); }
    std::string getOutput() const { return buffer.str(); }
};

void testBasicOperations() {
    std::cout << "Testing basic operations..." << std::endl;
    
    // 创建一个有向图
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
    
    // 测试顶点和边的数量
    assert(graph.getVertexCount() == 4 && "Vertex count should be 4");
    assert(graph.getEdgeCount() == 4 && "Edge count should be 4");

    // 测试边的存在性
    assert(graph.hasEdge(0, 1) && "Edge A->B should exist");
    assert(!graph.hasEdge(1, 0) && "Edge B->A should not exist");

    // 测试顶点值的获取
    assert(graph.getVertex(0) == 'A' && "Vertex 0 should be A");
    assert(graph.getVertex(1) == 'B' && "Vertex 1 should be B");

    // 测试度数
    assert(graph.getOutDegree(1) == 1 && "Vertex B should have out-degree 1");
    assert(graph.getInDegree(1) == 1 && "Vertex B should have in-degree 1");
    
    std::cout << "Basic operations tests passed!" << std::endl;
}

void testUndirectedGraph() {
    std::cout << "Testing undirected graph..." << std::endl;
    
    // 创建一个无向图
    ChainForwardStar<char> graph(4, false);
    
    // 设置顶点值
    graph.setVertex(0, 'A');
    graph.setVertex(1, 'B');
    graph.setVertex(2, 'C');
    graph.setVertex(3, 'D');
    
    // 添加边
    graph.addEdge(0, 1);  // A - B
    graph.addEdge(1, 2);  // B - C
    
    // 测试边的存在性
    assert(graph.hasEdge(0, 1) && "Edge A-B should exist");
    assert(graph.hasEdge(1, 0) && "Edge B-A should exist");
    assert(graph.getEdgeCount() == 2 && "Edge count should be 2 (each undirected edge counts as 1)");
    
    std::cout << "Undirected graph tests passed!" << std::endl;
}

void testGraphTraversal() {
    std::cout << "Testing graph traversal..." << std::endl;
    
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
    
    // 测试DFS
    {
        CaptureOutput capture;
        graph.DFS();
        std::string output = capture.getOutput();
        assert(output.find("DFS traversal:") != std::string::npos && "DFS output should contain header");
        assert(output.find('A') != std::string::npos && "DFS should visit vertex A");
        assert(output.find('B') != std::string::npos && "DFS should visit vertex B");
        assert(output.find('C') != std::string::npos && "DFS should visit vertex C");
        assert(output.find('D') != std::string::npos && "DFS should visit vertex D");
    }

    // 测试BFS
    {
        CaptureOutput capture;
        graph.BFS();
        std::string output = capture.getOutput();
        assert(output.find("BFS traversal:") != std::string::npos && "BFS output should contain header");
        assert(output.find('A') != std::string::npos && "BFS should visit vertex A");
        assert(output.find('B') != std::string::npos && "BFS should visit vertex B");
        assert(output.find('C') != std::string::npos && "BFS should visit vertex C");
        assert(output.find('D') != std::string::npos && "BFS should visit vertex D");
    }

    std::cout << "Graph traversal tests passed!" << std::endl;
}

void testTopologicalSort() {
    std::cout << "Testing topological sort..." << std::endl;
    
    // 测试有向无环图
    {
        ChainForwardStar<char> dag(4);
        
        // 设置顶点值
        dag.setVertex(0, 'A');
        dag.setVertex(1, 'B');
        dag.setVertex(2, 'C');
        dag.setVertex(3, 'D');
        
        // 添加边
        dag.addEdge(0, 1);  // A -> B
        dag.addEdge(1, 2);  // B -> C
        dag.addEdge(0, 2);  // A -> C
        dag.addEdge(2, 3);  // C -> D
        
        CaptureOutput capture;
        bool result = dag.topologicalSort();
        std::string output = capture.getOutput();
        
        assert(result && "Topological sort should succeed for DAG");
        assert(output.find("Topological sort result:") != std::string::npos);
    }
    
    // 测试有环图
    {
        ChainForwardStar<char> cyclic(3);
        
        // 设置顶点值
        cyclic.setVertex(0, 'A');
        cyclic.setVertex(1, 'B');
        cyclic.setVertex(2, 'C');
        
        // 添加边形成环
        cyclic.addEdge(0, 1);  // A -> B
        cyclic.addEdge(1, 2);  // B -> C
        cyclic.addEdge(2, 0);  // C -> A
        
        CaptureOutput capture;
        bool result = cyclic.topologicalSort();
        std::string output = capture.getOutput();
        
        assert(!result && "Topological sort should fail for cyclic graph");
        assert(output.find("Graph contains a cycle") != std::string::npos);
    }

    std::cout << "Topological sort tests passed!" << std::endl;
}

void testErrorHandling() {
    std::cout << "Testing error handling..." << std::endl;
    
    ChainForwardStar<char> graph(2);
    graph.setVertex(0, 'A');
    graph.setVertex(1, 'B');
    
    // 测试无效顶点索引
    try {
        graph.setVertex(2, 'C');
        assert(false && "Should throw exception for invalid vertex index");
    } catch (const std::out_of_range&) {
        // Expected exception
    }
    
    // 测试无效边
    try {
        graph.addEdge(0, 2);
        assert(false && "Should throw exception for invalid edge");
    } catch (const std::out_of_range&) {
        // Expected exception
    }
    
    // 测试无效的顶点查询
    try {
        graph.getVertex(2);
        assert(false && "Should throw exception for invalid vertex query");
    } catch (const std::out_of_range&) {
        // Expected exception
    }

    std::cout << "Error handling tests passed!" << std::endl;
}

void testWeightedEdges() {
    std::cout << "Testing weighted edges..." << std::endl;
    
    ChainForwardStar<char> graph(3);
    
    // 设置顶点值
    graph.setVertex(0, 'A');
    graph.setVertex(1, 'B');
    graph.setVertex(2, 'C');
    
    // 添加带权边
    graph.addEdge(0, 1, 5);  // A -> B, weight = 5
    graph.addEdge(1, 2, 3);  // B -> C, weight = 3
    
    // 测试权重
    assert(graph.getWeight(0, 1) == 5 && "Edge A->B should have weight 5");
    assert(graph.getWeight(1, 2) == 3 && "Edge B->C should have weight 3");
    assert(graph.getWeight(0, 2) == INT_MAX && "Non-existent edge should return INT_MAX");
    
    std::cout << "Weighted edges tests passed!" << std::endl;
}

int main() {
    try {
        testBasicOperations();
        testUndirectedGraph();
        testGraphTraversal();
        testTopologicalSort();
        testErrorHandling();
        testWeightedEdges();
        
        std::cout << "\nAll tests passed successfully!" << std::endl;
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Test failed with exception: " << e.what() << std::endl;
        return 1;
    }
}
