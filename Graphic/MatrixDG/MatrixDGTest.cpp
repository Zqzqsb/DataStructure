#include "MatrixDG.hpp"
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
    
    char vertices[] = {'A', 'B', 'C', 'D'};
    char edges[][2] = {
        {'A', 'B'},
        {'B', 'C'},
        {'C', 'D'},
        {'D', 'A'}
    };
    
    MatrixDG<char> graph(vertices, 4, edges, 4);
    
    // Test vertex and edge count
    assert(graph.getVertexNum() == 4 && "Vertex count should be 4");
    assert(graph.getEdgeNum() == 4 && "Edge count should be 4");

    // Test edge existence
    assert(graph.hasEdge('A', 'B') && "Edge A->B should exist");
    assert(!graph.hasEdge('B', 'A') && "Edge B->A should not exist");

    // Test in/out neighbors
    auto outNeighbors = graph.getOutNeighbors('B');
    assert(outNeighbors.size() == 1 && "Vertex B should have 1 out-neighbor");
    auto inNeighbors = graph.getInNeighbors('B');
    assert(inNeighbors.size() == 1 && "Vertex B should have 1 in-neighbor");
    
    // Test degrees
    assert(graph.getOutDegree('B') == 1 && "Vertex B should have out-degree 1");
    assert(graph.getInDegree('B') == 1 && "Vertex B should have in-degree 1");
    
    std::cout << "Basic operations tests passed!" << std::endl;
}

void testGraphTraversal() {
    std::cout << "Testing graph traversal..." << std::endl;
    
    char vertices[] = {'A', 'B', 'C', 'D'};
    char edges[][2] = {
        {'A', 'B'},
        {'B', 'C'},
        {'C', 'D'},
        {'D', 'A'}
    };
    
    MatrixDG<char> graph(vertices, 4, edges, 4);
    
    // Test DFS
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

    // Test BFS
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
    
    // Test case 1: DAG
    {
        char vertices[] = {'A', 'B', 'C', 'D'};
        char edges[][2] = {
            {'A', 'B'},
            {'B', 'C'},
            {'A', 'C'},
            {'C', 'D'}
        };
        
        MatrixDG<char> dag(vertices, 4, edges, 4);
        
        CaptureOutput capture;
        bool result = dag.topologicalSort();
        std::string output = capture.getOutput();
        
        assert(result && "Topological sort should succeed for DAG");
        assert(output.find("Topological sort result:") != std::string::npos);
    }
    
    // Test case 2: Graph with cycle
    {
        char vertices[] = {'A', 'B', 'C'};
        char edges[][2] = {
            {'A', 'B'},
            {'B', 'C'},
            {'C', 'A'}
        };
        
        MatrixDG<char> cyclic(vertices, 3, edges, 3);
        
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
    
    char vertices[] = {'A', 'B'};
    char edges[][2] = {{'A', 'C'}};  // Invalid vertex C
    
    try {
        MatrixDG<char> graph(vertices, 2, edges, 1);
        assert(false && "Should throw exception for invalid vertex");
    } catch (const std::invalid_argument&) {
        // Expected exception
    }

    MatrixDG<char> graph(vertices, 2, edges, 0);
    assert(graph.getInDegree('X') == -1 && "Should return -1 for non-existent vertex");
    assert(graph.getOutDegree('X') == -1 && "Should return -1 for non-existent vertex");

    std::cout << "Error handling tests passed!" << std::endl;
}

void testDisconnectedGraph() {
    std::cout << "Testing disconnected graph..." << std::endl;
    
    char vertices[] = {'A', 'B', 'C', 'D'};
    char edges[][2] = {
        {'A', 'B'},
        {'C', 'D'}
    };
    
    MatrixDG<char> graph(vertices, 4, edges, 2);
    
    // Test DFS on disconnected graph
    {
        CaptureOutput capture;
        graph.DFS();
        std::string output = capture.getOutput();
        assert(output.find('A') != std::string::npos && "DFS should visit component with A");
        assert(output.find('C') != std::string::npos && "DFS should visit component with C");
    }

    // Test BFS on disconnected graph
    {
        CaptureOutput capture;
        graph.BFS();
        std::string output = capture.getOutput();
        assert(output.find('A') != std::string::npos && "BFS should visit component with A");
        assert(output.find('C') != std::string::npos && "BFS should visit component with C");
    }

    std::cout << "Disconnected graph tests passed!" << std::endl;
}

int main() {
    try {
        testBasicOperations();
        testGraphTraversal();
        testTopologicalSort();
        testErrorHandling();
        testDisconnectedGraph();
        
        std::cout << "\nAll tests passed successfully!" << std::endl;
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Test failed with exception: " << e.what() << std::endl;
        return 1;
    }
}
