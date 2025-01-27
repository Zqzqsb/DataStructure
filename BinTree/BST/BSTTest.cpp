#include "BST.hpp"
#include <cassert>
#include <sstream>
#include <vector>

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
    
    BST<int> tree;
    
    // 测试空树属性
    assert(tree.isEmpty() && "Tree should be empty initially");
    assert(tree.getSize() == 0 && "Size should be 0 initially");
    assert(tree.getHeight() == 0 && "Height should be 0 for empty tree");

    // 插入节点
    tree.insert(10);
    tree.insert(5);
    tree.insert(15);
    tree.insert(3);
    tree.insert(7);

    // 测试树的属性
    assert(!tree.isEmpty() && "Tree should not be empty after insertions");
    assert(tree.getSize() == 5 && "Size should be 5 after insertions");
    assert(tree.contains(7) && "Tree should contain 7");
    assert(!tree.contains(100) && "Tree should not contain 100");

    std::cout << "Basic operations tests passed!" << std::endl;
}

void testDeletion() {
    std::cout << "Testing deletion..." << std::endl;
    
    BST<int> tree;
    
    // 插入一些节点
    std::vector<int> values = {10, 5, 15, 3, 7, 12, 17};
    for (int value : values) {
        tree.insert(value);
    }
    
    // 测试删除叶子节点
    tree.remove(3);
    assert(!tree.contains(3) && "Tree should not contain 3 after deletion");
    assert(tree.getSize() == 6 && "Size should be 6 after deletion");

    // 测试删除有一个子节点的节点
    tree.remove(5);
    assert(!tree.contains(5) && "Tree should not contain 5 after deletion");
    assert(tree.contains(7) && "Tree should still contain 7 after parent deletion");

    // 测试删除有两个子节点的节点
    tree.remove(15);
    assert(!tree.contains(15) && "Tree should not contain 15 after deletion");
    assert(tree.contains(12) && tree.contains(17) && "Tree should still contain children after parent deletion");

    // 测试删除不存在的节点
    try {
        tree.remove(100);
        assert(false && "Should throw exception when removing non-existent value");
    } catch (const std::runtime_error&) {
        // Expected exception
    }

    std::cout << "Deletion tests passed!" << std::endl;
}

void testTraversals() {
    std::cout << "Testing traversals..." << std::endl;
    
    BST<int> tree;
    
    // 创建一个测试树
    //       10
    //      /  \
    //     5    15
    //    / \
    //   3   7
    tree.insert(10);
    tree.insert(5);
    tree.insert(15);
    tree.insert(3);
    tree.insert(7);

    // 测试前序遍历
    {
        CaptureOutput capture;
        tree.preOrder();
        std::string output = capture.getOutput();
        assert(output.find("10 5 3 7 15") != std::string::npos && "Incorrect preorder traversal");
    }

    // 测试中序遍历
    {
        CaptureOutput capture;
        tree.inOrder();
        std::string output = capture.getOutput();
        assert(output.find("3 5 7 10 15") != std::string::npos && "Incorrect inorder traversal");
    }

    // 测试后序遍历
    {
        CaptureOutput capture;
        tree.postOrder();
        std::string output = capture.getOutput();
        assert(output.find("3 7 5 15 10") != std::string::npos && "Incorrect postorder traversal");
    }

    // 测试层序遍历
    {
        CaptureOutput capture;
        tree.levelOrder();
        std::string output = capture.getOutput();
        assert(output.find("10 5 15 3 7") != std::string::npos && "Incorrect level-order traversal");
    }

    std::cout << "Traversal tests passed!" << std::endl;
}

void testPredecessorSuccessor() {
    std::cout << "Testing predecessor and successor..." << std::endl;
    
    BST<int> tree;
    
    // 创建一个测试树
    //       10
    //      /  \
    //     5    15
    //    / \   /
    //   3   7 12
    tree.insert(10);
    tree.insert(5);
    tree.insert(15);
    tree.insert(3);
    tree.insert(7);
    tree.insert(12);

    // 测试前驱
    assert(tree.getPredecessor(10) == 7 && "Predecessor of 10 should be 7");
    assert(tree.getPredecessor(15) == 12 && "Predecessor of 15 should be 12");
    assert(tree.getPredecessor(5) == 3 && "Predecessor of 5 should be 3");

    // 测试后继
    assert(tree.getSuccessor(10) == 12 && "Successor of 10 should be 12");
    assert(tree.getSuccessor(5) == 7 && "Successor of 5 should be 7");
    assert(tree.getSuccessor(12) == 15 && "Successor of 12 should be 15");

    // 测试边界情况
    try {
        tree.getPredecessor(3);
        assert(false && "Should throw exception when getting predecessor of minimum value");
    } catch (const std::runtime_error&) {
        // Expected exception
    }

    try {
        tree.getSuccessor(15);
        assert(false && "Should throw exception when getting successor of maximum value");
    } catch (const std::runtime_error&) {
        // Expected exception
    }

    std::cout << "Predecessor and successor tests passed!" << std::endl;
}

void testMinMax() {
    std::cout << "Testing min/max operations..." << std::endl;
    
    BST<int> tree;
    
    // 测试空树
    try {
        tree.getMin();
        assert(false && "getMin should throw exception on empty tree");
    } catch (const std::runtime_error&) {
        // Expected exception
    }

    try {
        tree.getMax();
        assert(false && "getMax should throw exception on empty tree");
    } catch (const std::runtime_error&) {
        // Expected exception
    }

    // 插入节点
    tree.insert(10);
    tree.insert(5);
    tree.insert(15);
    tree.insert(3);
    tree.insert(7);

    // 测试最小值和最大值
    assert(tree.getMin() == 3 && "Minimum value should be 3");
    assert(tree.getMax() == 15 && "Maximum value should be 15");

    std::cout << "Min/max operations tests passed!" << std::endl;
}

void testCopyAndAssignment() {
    std::cout << "Testing copy and assignment..." << std::endl;
    
    BST<int> tree1;
    tree1.insert(10);
    tree1.insert(5);
    tree1.insert(15);

    // 测试拷贝构造
    BST<int> tree2(tree1);
    assert(tree2.getSize() == tree1.getSize() && "Copy constructor: sizes should match");
    
    // 测试赋值运算符
    BST<int> tree3;
    tree3 = tree1;
    assert(tree3.getSize() == tree1.getSize() && "Assignment operator: sizes should match");

    // 修改原树不应影响副本
    tree1.clear();
    assert(tree2.getSize() == 3 && "Copy should be independent");
    assert(tree3.getSize() == 3 && "Assignment copy should be independent");

    std::cout << "Copy and assignment tests passed!" << std::endl;
}

int main() {
    try {
        testBasicOperations();
        testDeletion();
        testTraversals();
        testPredecessorSuccessor();
        testMinMax();
        testCopyAndAssignment();
        
        std::cout << "\nAll tests passed successfully!" << std::endl;
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Test failed with exception: " << e.what() << std::endl;
        return 1;
    }
}
