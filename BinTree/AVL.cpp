#include "BST.cpp"

template <class T>
class AVL : public BST<T>
{
public:
    AVL() : BST<T>() {}
    AVL(const vector<T>& v) : BST<T>(v) {}
    int height() {return height(this -> root);}
    void insert(const T& key){insert(this -> root , key);}

private:
    int height(BinTreeNode<T>* node) {return node == nullptr ? 0 : node->height;}
    
    /* LL：左子树的左边失去平衡(左单旋转) X为在左子树插入后的结构
     *       k2              k1     
     *      /  \            /  \
     *     k1   z   ===>   X    k2
     *    /  \                 /  \
     *   X    y               y    z
     */
    BinTreeNode<T>* leftLeftRotation(BinTreeNode<T>* &k2)
    {
        BinTreeNode<T>* k1 = k2 -> leftchild;
        k2 -> leftchild = k1 -> rightchild;
        k1 -> rightchild = k2;
        
        // 设置高度
        k2 -> height = max(height(k2 -> rightchild) ,height(k2 -> leftchild)) + 1;
        k1 -> height = max(height(k1 -> leftchild) , k2->height);
        return k1; // 返回子树的父节点
    }

    /* RR：右子树的右边失去平衡(右单旋转) Z为在右子树插入后的结构
     *       k1              k2     
     *      /  \            /  \
     *     x   k2   ===>   k1   Z
     *        /  \        /  \   
     *       y    Z      x    y  
     */
    BinTreeNode<T>* rightRightRotation(BinTreeNode<T>* &k1)
    {
        BinTreeNode<T>* k2 = k1 -> rightchild;
        k1 -> rightchild = k2 -> leftchild;
        k2 ->  leftchild = k1;
        // 设置高度
        k1 -> height = max(height(k1 -> rightchild) , height(k1 -> leftchild)) + 1;
        k2 -> height = max(height(k2 -> rightchild) , k1->height);
        return k2;
    }
    
    /* LR：左子树的右边失去平衡(左双旋转)
     *       k3               k3               k2
     *      /  \     RR      /  \     LL      /  \
     *     k1   D   ===>   k2    D   ===>   k1    k3
     *    /  \            /  \             /  \  /  \
     *   A    K2         k1   C           A    B C   D
     *       /  \       /  \
     *      B    C     A    B
     */
    BinTreeNode<T>* leftRightRotation(BinTreeNode<T>* &k3)
    {
        // 在k1节点做RR旋转
        k3 -> leftchild = rightRightRotation(k3 -> leftchild);
        // 在k3节点做LL旋转
        return leftLeftRotation(k3);
    }
    
    /* RL：右子树的左边失去平衡(右双旋转)
     *     k1               k1                K2
     *    /  \      LL     /  \      RR      /  \
     *   A    k3   ===>   A    k2   ===>   k1    K3
     *       /  \             /  \        /  \  /  \
     *      k2   D           B    k3     A    B C   D
     *     /  \                  /   \
     *    B    D                C     D
     */
    BinTreeNode<T>* rightLeftRotation(BinTreeNode<T>* &k1)
    {
        k1 -> rightchild = leftLeftRotation(k1 -> rightchild);
        return rightRightRotation(k1);
    }

    BinTreeNode<T>* insert(BinTreeNode<T>* &node , const T& key)
    {
        if(node == NULL)
            node = new BinTreeNode<T>(key);
        else if(key < node -> data)
        {
            // 为了这里要使用递归每个节点都判断
            // 因为插入造成的影响(不平衡)是向上传递的
            // 使用递归可以在最底层的结构中解决这个问题
            // 而在函数退栈的过程中 不平衡的影响已经解决
            node -> leftchild = insert(node -> leftchild, key);
            // 左子树比右子树高
            if(height(node -> leftchild) - height(node -> rightchild) == 2)
            {
                if(key < node -> leftchild -> data)
                {
                    cout << "LL" << node -> data << endl;
                    node = leftLeftRotation(node); // 在左子树的左子树中插入
                }
                else
                {
                    cout << "LR" << node -> data << endl;
                    node = leftRightRotation(node); // 在左子树的右子树中插入
                }
                    
            }
        }
        else if(key > node -> data) // 在右子树中插入 原理类似
        {
            node -> rightchild = insert(node -> rightchild , key);
            if(height(node -> rightchild) - height(node -> leftchild) == 2)
            {
                if(key > node -> rightchild -> data) // RR失衡
                {
                    cout << "RR" << node -> data << endl;
                    node = rightRightRotation(node); 
                }  
                else
                {
                    cout << "RL" << node -> data << endl;
                    node = rightLeftRotation(node); // RL失衡
                }     
            }
        }
        else
        {
            cout << "cannot add duplicate key!" << endl;
        }
        // 这是一个恒等式 也在递归的过程中调整树的高度
        // 当插入成功时 叶子节点(插入的节点都为叶子节点)的高度自动调整为1 
        // 这种高度调整将向上传递
        node -> height = max(height(node->leftchild) , height(node->rightchild)) + 1; 
        return node;
    }

    // BinTreeNode<T>* remove(BinTreeNode<T>* &node , BinTreeNode<T>* z)
    // {
    //     if(node == nullptr || z == nullptr) 
    //         return nullptr;
    //     if(z -> data < node -> data) // 小于当前节点  在左子树中递归删除
    //     {
    //         node -> leftchild = remove(node -> leftchild , z);
    //         // 由于在左子树中删除了节点 有可能造成右子树过高
    //         if(height(node -> rightchild) > height(node -> rightchild) == 2)
    //         {
    //             BinTreeNode<T>* r = node -> rightchild;
    //             if()
    //         }
    //     }
    // }
};


int main()
{
    AVL<int> tree;
    tree.insert(3);
    tree.insert(2);
    tree.insert(1);
    tree.insert(4);
    tree.insert(5);
    tree.insert(6);
    tree.insert(7);

    tree.insert(16);
    tree.insert(15);
    // tree.insert(14);
    // tree.insert(13);
    // tree.insert(12);
    // tree.insert(11);
    // tree.insert(10);
    // tree.insert(8);
    // tree.insert(9);


    tree.PreOrder();
    tree.InOrder();
}
