#ifndef BINTREE_HPP
#define BINTREE_HPP

#include <iostream>
#include <queue>
#include <stack>
#include <stdexcept>

template<typename T>
class BinTree {
protected:
    struct Node {
        T data;
        Node* left;
        Node* right;
        
        Node(const T& value) : data(value), left(nullptr), right(nullptr) {}
    };
    
    Node* root;
    int size;

public:
    // 构造函数
    BinTree() : root(nullptr), size(0) {}
    
    // 析构函数
    virtual ~BinTree() {
        clear();
    }
    
    // 拷贝构造函数
    BinTree(const BinTree& other) : root(nullptr), size(0) {
        root = copyTree(other.root);
        size = other.size;
    }
    
    // 赋值运算符
    BinTree& operator=(const BinTree& other) {
        if (this != &other) {
            clear();
            root = copyTree(other.root);
            size = other.size;
        }
        return *this;
    }

    // 获取树的大小
    int getSize() const {
        return size;
    }

    // 判断树是否为空
    bool isEmpty() const {
        return root == nullptr;
    }

    // 获取树的高度
    int getHeight() const {
        return getHeight(root);
    }

    // 清空树
    void clear() {
        clearTree(root);
        root = nullptr;
        size = 0;
    }

    // 前序遍历（递归版本）
    void preOrder() const {
        std::cout << "Preorder traversal: ";
        preOrder(root);
        std::cout << std::endl;
    }

    // 中序遍历（递归版本）
    void inOrder() const {
        std::cout << "Inorder traversal: ";
        inOrder(root);
        std::cout << std::endl;
    }

    // 后序遍历（递归版本）
    void postOrder() const {
        std::cout << "Postorder traversal: ";
        postOrder(root);
        std::cout << std::endl;
    }

    // 前序遍历（非递归版本）
    void preOrderNonRecursive() const {
        std::cout << "Non-recursive preorder traversal: ";
        if (root == nullptr) {
            std::cout << std::endl;
            return;
        }

        std::stack<Node*> s;
        s.push(root);

        while (!s.empty()) {
            Node* current = s.top();
            s.pop();
            std::cout << current->data << " ";

            if (current->right) {
                s.push(current->right);
            }
            if (current->left) {
                s.push(current->left);
            }
        }
        std::cout << std::endl;
    }

    // 中序遍历（非递归版本）
    void inOrderNonRecursive() const {
        std::cout << "Non-recursive inorder traversal: ";
        if (root == nullptr) {
            std::cout << std::endl;
            return;
        }

        std::stack<Node*> s;
        Node* current = root;

        while (current != nullptr || !s.empty()) {
            while (current != nullptr) {
                s.push(current);
                current = current->left;
            }

            current = s.top();
            s.pop();
            std::cout << current->data << " ";
            current = current->right;
        }
        std::cout << std::endl;
    }

    // 后序遍历（非递归版本）
    void postOrderNonRecursive() const {
        std::cout << "Non-recursive postorder traversal: ";
        if (root == nullptr) {
            std::cout << std::endl;
            return;
        }

        std::stack<Node*> s1, s2;
        s1.push(root);

        while (!s1.empty()) {
            Node* current = s1.top();
            s1.pop();
            s2.push(current);

            if (current->left) {
                s1.push(current->left);
            }
            if (current->right) {
                s1.push(current->right);
            }
        }

        while (!s2.empty()) {
            std::cout << s2.top()->data << " ";
            s2.pop();
        }
        std::cout << std::endl;
    }

    // 层序遍历
    void levelOrder() const {
        std::cout << "Level-order traversal: ";
        if (root == nullptr) {
            std::cout << std::endl;
            return;
        }

        std::queue<Node*> q;
        q.push(root);

        while (!q.empty()) {
            Node* current = q.front();
            q.pop();
            std::cout << current->data << " ";

            if (current->left) {
                q.push(current->left);
            }
            if (current->right) {
                q.push(current->right);
            }
        }
        std::cout << std::endl;
    }

protected:
    // 获取节点高度
    int getHeight(Node* node) const {
        if (node == nullptr) {
            return 0;
        }
        return std::max(getHeight(node->left), getHeight(node->right)) + 1;
    }

    // 复制树的辅助函数
    Node* copyTree(Node* node) {
        if (node == nullptr) {
            return nullptr;
        }
        Node* newNode = new Node(node->data);
        newNode->left = copyTree(node->left);
        newNode->right = copyTree(node->right);
        return newNode;
    }

    // 清空树的辅助函数
    void clearTree(Node* node) {
        if (node == nullptr) {
            return;
        }
        clearTree(node->left);
        clearTree(node->right);
        delete node;
    }

    // 前序遍历的辅助函数
    void preOrder(Node* node) const {
        if (node == nullptr) {
            return;
        }
        std::cout << node->data << " ";
        preOrder(node->left);
        preOrder(node->right);
    }

    // 中序遍历的辅助函数
    void inOrder(Node* node) const {
        if (node == nullptr) {
            return;
        }
        inOrder(node->left);
        std::cout << node->data << " ";
        inOrder(node->right);
    }

    // 后序遍历的辅助函数
    void postOrder(Node* node) const {
        if (node == nullptr) {
            return;
        }
        postOrder(node->left);
        postOrder(node->right);
        std::cout << node->data << " ";
    }
};

#endif // BINTREE_HPP
