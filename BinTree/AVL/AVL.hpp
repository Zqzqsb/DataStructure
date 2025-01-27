#ifndef AVL_HPP
#define AVL_HPP

#include <iostream>
#include <queue>
#include <stack>
#include <algorithm>
#include <stdexcept>

template<typename T>
class AVL {
private:
    struct Node {
        T data;
        Node* left;
        Node* right;
        int height;
        
        Node(const T& value) : data(value), left(nullptr), right(nullptr), height(1) {}
    };
    
    Node* root;
    int size;

public:
    // 构造函数
    AVL() : root(nullptr), size(0) {}
    
    // 析构函数
    ~AVL() {
        clear();
    }
    
    // 拷贝构造函数
    AVL(const AVL& other) : root(nullptr), size(0) {
        root = copyTree(other.root);
        size = other.size;
    }
    
    // 赋值运算符
    AVL& operator=(const AVL& other) {
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
        return node == nullptr ? 0 : node->height;
    }

    // 更新节点高度
    void updateHeight(Node* node) {
        if (node != nullptr) {
            node->height = std::max(getHeight(node->left), getHeight(node->right)) + 1;
        }
    }

    // 获取平衡因子
    int getBalanceFactor(Node* node) const {
        if (node == nullptr) {
            return 0;
        }
        return getHeight(node->left) - getHeight(node->right);
    }

    /*
     * 右旋转操作
     *     y                   x
     *    / \                 / \
     *   x   T3   ====>     T1  y
     *  / \                    / \
     * T1  T2                T2  T3
     */
    Node* rightRotate(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;

        x->right = y;
        y->left = T2;

        // 更新高度
        updateHeight(y);
        updateHeight(x);

        return x;
    }

    /*
     * 左旋转操作
     *   x                      y
     *  / \                    / \
     * T1  y      ====>      x   T3
     *    / \               / \
     *   T2  T3            T1 T2
     */
    Node* leftRotate(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;

        y->left = x;
        x->right = T2;

        // 更新高度
        updateHeight(x);
        updateHeight(y);

        return y;
    }

    // 插入节点的辅助函数
    Node* insert(Node* node, const T& value) {
        // 执行标准BST插入
        if (node == nullptr) {
            size++;
            return new Node(value);
        }

        if (value < node->data) {
            node->left = insert(node->left, value);
        } else if (value > node->data) {
            node->right = insert(node->right, value);
        } else {
            return node;  // 重复值不插入
        }

        // 更新节点高度
        updateHeight(node);

        // 获取平衡因子
        int balance = getBalanceFactor(node);

        // 左左情况
        if (balance > 1 && value < node->left->data) {
            return rightRotate(node);
        }

        // 右右情况
        if (balance < -1 && value > node->right->data) {
            return leftRotate(node);
        }

        // 左右情况
        /* LR：左子树的右边失去平衡(左双旋转)
        *       k3               k3               k2
        *      /  \     RR      /  \     LL      /  \
        *     k1   D   ===>   k2    D   ===>   k1    k3
        *    /  \            /  \             /  \  /  \
        *   A    K2         k1   C           A    B C   D
        *       /  \       /  \
        *      B    C     A    B
        */
        if (balance > 1 && value > node->left->data) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        // 右左情况
        /* RL：右子树的左边失去平衡(右双旋转)
        *     k1               k1                K2
        *    /  \      LL     /  \      RR      /  \
        *   A    k3   ===>   A    k2   ===>   k1    K3
        *       /  \             /  \        /  \  /  \
        *      k2   D           B    k3     A    B C   D
        *     /  \                  /   \
        *    B    D                C     D
     */
        if (balance < -1 && value < node->right->data) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

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
            if (node->left == nullptr || node->right == nullptr) {
                Node* temp = node->left ? node->left : node->right;
                if (temp == nullptr) {
                    temp = node;
                    node = nullptr;
                } else {
                    *node = *temp;
                }
                delete temp;
                size--;
            } else {
                // 有两个子节点的情况
                Node* temp = getMin(node->right);
                node->data = temp->data;
                node->right = remove(node->right, temp->data);
            }
        }

        if (node == nullptr) {
            return nullptr;
        }

        // 更新高度
        updateHeight(node);

        // 获取平衡因子
        int balance = getBalanceFactor(node);

        // 左左情况
        if (balance > 1 && getBalanceFactor(node->left) >= 0) {
            return rightRotate(node);
        }

        // 左右情况
        if (balance > 1 && getBalanceFactor(node->left) < 0) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        // 右右情况
        if (balance < -1 && getBalanceFactor(node->right) <= 0) {
            return leftRotate(node);
        }

        // 右左情况
        if (balance < -1 && getBalanceFactor(node->right) > 0) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
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

    // 复制树的辅助函数
    Node* copyTree(Node* node) {
        if (node == nullptr) {
            return nullptr;
        }
        Node* newNode = new Node(node->data);
        newNode->height = node->height;
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

#endif // AVL_HPP
