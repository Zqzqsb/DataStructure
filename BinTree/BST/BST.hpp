#ifndef BST_HPP
#define BST_HPP

#include <iostream>
#include <queue>
#include <stack>
#include <stdexcept>

template<typename T>
class BST {
private:
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
    BST() : root(nullptr), size(0) {}
    
    // 析构函数
    ~BST() {
        clear();
    }
    
    // 拷贝构造函数
    BST(const BST& other) : root(nullptr), size(0) {
        root = copyTree(other.root);
        size = other.size;
    }
    
    // 赋值运算符
    BST& operator=(const BST& other) {
        if (this != &other) {
            clear();
            root = copyTree(other.root);
            size = other.size;
        }
        return *this;
    }

    // 插入节点
    void insert(const T& value) {
        root = insert(root, value);
    }

    // 删除节点
    void remove(const T& value) {
        int oldSize = size;
        root = remove(root, value);
        if (size == oldSize) {
            throw std::runtime_error("Value not found in the tree");
        }
    }

    // 查找节点
    bool contains(const T& value) const {
        return contains(root, value);
    }

    // 获取最小值
    T getMin() const {
        if (root == nullptr) {
            throw std::runtime_error("Tree is empty");
        }
        return getMin(root)->data;
    }

    // 获取最大值
    T getMax() const {
        if (root == nullptr) {
            throw std::runtime_error("Tree is empty");
        }
        return getMax(root)->data;
    }

    // 获取前驱
    T getPredecessor(const T& value) const {
        Node* node = findNode(root, value);
        if (node == nullptr) {
            throw std::runtime_error("Value not found in the tree");
        }
        Node* pred = getPredecessor(root, node);
        if (pred == nullptr) {
            throw std::runtime_error("No predecessor exists");
        }
        return pred->data;
    }

    // 获取后继
    T getSuccessor(const T& value) const {
        Node* node = findNode(root, value);
        if (node == nullptr) {
            throw std::runtime_error("Value not found in the tree");
        }
        Node* succ = getSuccessor(root, node);
        if (succ == nullptr) {
            throw std::runtime_error("No successor exists");
        }
        return succ->data;
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

    // 前序遍历
    void preOrder() const {
        std::cout << "Preorder traversal: ";
        preOrder(root);
        std::cout << std::endl;
    }

    // 中序遍历
    void inOrder() const {
        std::cout << "Inorder traversal: ";
        inOrder(root);
        std::cout << std::endl;
    }

    // 后序遍历
    void postOrder() const {
        std::cout << "Postorder traversal: ";
        postOrder(root);
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

private:
    // 获取节点高度
    int getHeight(Node* node) const {
        if (node == nullptr) {
            return 0;
        }
        return std::max(getHeight(node->left), getHeight(node->right)) + 1;
    }

    // 插入节点的辅助函数
    Node* insert(Node* node, const T& value) {
        if (node == nullptr) {
            size++;
            return new Node(value);
        }

        if (value < node->data) {
            node->left = insert(node->left, value);
        } else if (value > node->data) {
            node->right = insert(node->right, value);
        }
        // 如果值相等，不进行插入
        return node;
    }

    // 删除节点的辅助函数
    Node* remove(Node* node, const T& value) {
        if (node == nullptr) {
            return nullptr;
        }

        if (value < node->data) {
            node->left = remove(node->left, value);
        } else if (value > node->data) {
            node->right = remove(node->right, value);
        } else {
            // 找到要删除的节点
            if (node->left == nullptr) {
                Node* temp = node->right;
                delete node;
                size--;
                return temp;
            } else if (node->right == nullptr) {
                Node* temp = node->left;
                delete node;
                size--;
                return temp;
            }

            // 有两个子节点的情况
            Node* temp = getMin(node->right);
            node->data = temp->data;
            node->right = remove(node->right, temp->data);
        }
        return node;
    }

    // 查找节点的辅助函数
    bool contains(Node* node, const T& value) const {
        if (node == nullptr) {
            return false;
        }
        if (value < node->data) {
            return contains(node->left, value);
        } else if (value > node->data) {
            return contains(node->right, value);
        }
        return true;
    }

    // 查找节点
    Node* findNode(Node* node, const T& value) const {
        if (node == nullptr || node->data == value) {
            return node;
        }
        if (value < node->data) {
            return findNode(node->left, value);
        }
        return findNode(node->right, value);
    }

    // 获取最小值节点的辅助函数
    Node* getMin(Node* node) const {
        if (node == nullptr) {
            return nullptr;
        }
        while (node->left != nullptr) {
            node = node->left;
        }
        return node;
    }

    // 获取最大值节点的辅助函数
    Node* getMax(Node* node) const {
        if (node == nullptr) {
            return nullptr;
        }
        while (node->right != nullptr) {
            node = node->right;
        }
        return node;
    }

    // 获取前驱节点
    Node* getPredecessor(Node* root, Node* node) const {
        if (node->left != nullptr) {
            return getMax(node->left);
        }

        Node* predecessor = nullptr;
        while (root != nullptr) {
            if (node->data > root->data) {
                predecessor = root;
                root = root->right;
            } else if (node->data < root->data) {
                root = root->left;
            } else {
                break;
            }
        }
        return predecessor;
    }

    // 获取后继节点
    Node* getSuccessor(Node* root, Node* node) const {
        if (node->right != nullptr) {
            return getMin(node->right);
        }

        Node* successor = nullptr;
        while (root != nullptr) {
            if (node->data < root->data) {
                successor = root;
                root = root->left;
            } else if (node->data > root->data) {
                root = root->right;
            } else {
                break;
            }
        }
        return successor;
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

#endif // BST_HPP
