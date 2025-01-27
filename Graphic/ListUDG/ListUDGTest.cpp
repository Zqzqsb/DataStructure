#include "ListUDG.hpp"
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
    
    ListUDG<char> graph(vertices, 4, edges, 4);
    
    // Test vertex and edge count
    assert(graph.getVertexNum() == 4 && "Vertex count should be 4");
    assert(graph.getEdgeNum() == 4 && "Edge count should be 4");

    // Test edge existence
    assert(graph.hasEdge('A', 'B') && "Edge A-B should exist");
    assert(graph.hasEdge('B', 'A') && "Edge B-A should exist (undirected)");
    assert(!graph.hasEdge('A', 'C') && "Edge A-C should not exist");

    // Test neighbors
    auto neighbors = graph.getNeighbors('B');
    assert(neighbors.size() == 2 && "Vertex B should have 2 neighbors");

    // Test degree
    assert(graph.getDegree('B') == 2 && "Vertex B should have degree 2");
    assert(graph.getDegree('X') == -1 && "Non-existent vertex should have degree -1");
    
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
    
    ListUDG<char> graph(vertices, 4, edges, 4);
    
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

void testPrimMST() {
    std::cout << "Testing Prim's MST algorithm..." << std::endl;
    
    char vertices[] = {'A', 'B', 'C'};
    char edges[][2] = {
        {'A', 'B'},
        {'B', 'C'},
        {'C', 'A'}
    };
    
    ListUDG<char> graph(vertices, 3, edges, 3);
    
    {
        CaptureOutput capture;
        graph.Prim(0);
        std::string output = capture.getOutput();
        assert(output.find("Prim's MST") != std::string::npos && "Prim output should contain header");
        assert(output.find("Total MST weight:") != std::string::npos && "Prim output should show total weight");
    }

    std::cout << "Prim's MST algorithm tests passed!" << std::endl;
}

void testErrorHandling() {
    std::cout << "Testing error handling..." << std::endl;
    
    char vertices[] = {'A', 'B'};
    char edges[][2] = {{'A', 'C'}};  // Invalid vertex C
    
    try {
        ListUDG<char> graph(vertices, 2, edges, 1);
        assert(false && "Should throw exception for invalid vertex");
    } catch (const std::invalid_argument&) {
        // Expected exception
    }

    ListUDG<char> graph(vertices, 2, edges, 0);
    try {
        graph.Prim(-1);
        assert(false && "Should throw exception for invalid starting vertex");
    } catch (const std::invalid_argument&) {
        // Expected exception
    }

    std::cout << "Error handling tests passed!" << std::endl;
}

void testDisconnectedGraph() {
    std::cout << "Testing disconnected graph..." << std::endl;
    
    char vertices[] = {'A', 'B', 'C', 'D'};
    char edges[][2] = {
        {'A', 'B'},
        {'C', 'D'}
    };
    
    ListUDG<char> graph(vertices, 4, edges, 2);
    
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
        testPrimMST();
        testErrorHandling();
        testDisconnectedGraph();
        
        std::cout << "\nAll tests passed successfully!" << std::endl;
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Test failed with exception: " << e.what() << std::endl;
        return 1;
    }
}
