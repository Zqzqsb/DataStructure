#include "BinTree.hpp"
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

// 测试用的具体二叉树实现
template<typename T>
class TestBinTree : public BinTree<T> {
public:
    using Node = typename BinTree<T>::Node;
    using BinTree<T>::root;
    using BinTree<T>::size;

    // 用于测试的插入函数
    void insert(const T& value, const std::string& path) {
        Node** current = &root;
        for (char c : path) {
            if (c == 'L') {
                if (*current == nullptr) {
                    *current = new Node(value);
                    size++;
                }
                current = &((*current)->left);
            } else if (c == 'R') {
                if (*current == nullptr) {
                    *current = new Node(value);
                    size++;
                }
                current = &((*current)->right);
            }
        }
        if (*current == nullptr) {
            *current = new Node(value);
            size++;
        }
    }
};

void testBasicOperations() {
    std::cout << "Testing basic operations..." << std::endl;
    
    TestBinTree<int> tree;
    
    // 测试空树属性
    assert(tree.isEmpty() && "Tree should be empty initially");
    assert(tree.getSize() == 0 && "Size should be 0 initially");
    assert(tree.getHeight() == 0 && "Height should be 0 for empty tree");

    // 插入节点
    tree.insert(1, "");     // root
    tree.insert(2, "L");    // root->left
    tree.insert(3, "R");    // root->right
    tree.insert(4, "LL");   // root->left->left
    tree.insert(5, "LR");   // root->left->right

    // 测试树的属性
    assert(!tree.isEmpty() && "Tree should not be empty after insertions");
    assert(tree.getSize() == 5 && "Size should be 5 after insertions");
    assert(tree.getHeight() == 3 && "Height should be 3 after insertions");

    std::cout << "Basic operations tests passed!" << std::endl;
}

void testTraversals() {
    std::cout << "Testing traversals..." << std::endl;
    
    TestBinTree<char> tree;
    
    // 创建一个测试树
    //       A
    //      / \
    //     B   C
    //    / \
    //   D   E
    tree.insert('A', "");
    tree.insert('B', "L");
    tree.insert('C', "R");
    tree.insert('D', "LL");
    tree.insert('E', "LR");

    // 测试前序遍历
    {
        CaptureOutput capture;
        tree.preOrder();
        std::string output = capture.getOutput();
        assert(output.find("A B D E C") != std::string::npos && "Incorrect preorder traversal");
    }

    // 测试中序遍历
    {
        CaptureOutput capture;
        tree.inOrder();
        std::string output = capture.getOutput();
        assert(output.find("D B E A C") != std::string::npos && "Incorrect inorder traversal");
    }

    // 测试后序遍历
    {
        CaptureOutput capture;
        tree.postOrder();
        std::string output = capture.getOutput();
        assert(output.find("D E B C A") != std::string::npos && "Incorrect postorder traversal");
    }

    // 测试层序遍历
    {
        CaptureOutput capture;
        tree.levelOrder();
        std::string output = capture.getOutput();
        assert(output.find("A B C D E") != std::string::npos && "Incorrect level-order traversal");
    }

    std::cout << "Traversal tests passed!" << std::endl;
}

void testNonRecursiveTraversals() {
    std::cout << "Testing non-recursive traversals..." << std::endl;
    
    TestBinTree<char> tree;
    
    // 创建一个测试树
    //       A
    //      / \
    //     B   C
    //    / \
    //   D   E
    tree.insert('A', "");
    tree.insert('B', "L");
    tree.insert('C', "R");
    tree.insert('D', "LL");
    tree.insert('E', "LR");

    // 测试非递归前序遍历
    {
        CaptureOutput capture;
        tree.preOrderNonRecursive();
        std::string output = capture.getOutput();
        assert(output.find("A B D E C") != std::string::npos && "Incorrect non-recursive preorder traversal");
    }

    // 测试非递归中序遍历
    {
        CaptureOutput capture;
        tree.inOrderNonRecursive();
        std::string output = capture.getOutput();
        assert(output.find("D B E A C") != std::string::npos && "Incorrect non-recursive inorder traversal");
    }

    // 测试非递归后序遍历
    {
        CaptureOutput capture;
        tree.postOrderNonRecursive();
        std::string output = capture.getOutput();
        assert(output.find("D E B C A") != std::string::npos && "Incorrect non-recursive postorder traversal");
    }

    std::cout << "Non-recursive traversal tests passed!" << std::endl;
}

void testCopyAndAssignment() {
    std::cout << "Testing copy and assignment..." << std::endl;
    
    TestBinTree<int> tree1;
    tree1.insert(1, "");
    tree1.insert(2, "L");
    tree1.insert(3, "R");

    // 测试拷贝构造
    TestBinTree<int> tree2(tree1);
    assert(tree2.getSize() == tree1.getSize() && "Copy constructor: sizes should match");
    
    // 测试赋值运算符
    TestBinTree<int> tree3;
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
        testTraversals();
        testNonRecursiveTraversals();
        testCopyAndAssignment();
        
        std::cout << "\nAll tests passed successfully!" << std::endl;
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Test failed with exception: " << e.what() << std::endl;
        return 1;
    }
}
