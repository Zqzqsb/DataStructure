#include "BinTree.cpp"

template <class T>
class BST : public BinTree<T>
{

public:
    BST() : BinTree<T>() {}
    BST(const vector<T>& a) : BinTree<T>()
    {
        for(auto i : a)
            Insert(i , this -> root);
    }
    ~BST() {}
    
    bool Insert(const T& x) {return Insert(x , this -> root);}
    
    bool Remove(const T& x) {return Remove(x , this -> root);}

protected:
    bool Insert(const T& e , BinTreeNode<T>* &node)
    {
        if(node == nullptr)
        {
            node = new BinTreeNode<T>(e);
            if(node == nullptr)
            {
                cout << "Memory allocation failed!" << endl;
                exit(1);
            }
            return true;
        }
        else if (e < node -> data)
            Insert(e , node -> leftchild);
        else if (e > node -> data)
            Insert(e , node -> rightchild);
        else
            return false; // duplicate data
    }

    bool Remove(const T& x , BinTreeNode<T>* &node)
    {
        if(node != nullptr) 
        {
            // 上两个递归找删除节点的位置
            if(x < node -> data)
                Remove(x , node -> leftchild);
            else if(x > node -> data)
                Remove(x , node -> rightchild);
            
            // 如果左右子树都不为空 使用中序遍历的前一个节点(排序序列的前一个)
            // 来代替该节点 这个节点在在左子树的最右
            // 当然这里也可用左子树中中序遍历的第一个节点(排序序列的后一个)
            // 它在右子树的最左边
            else if(node -> leftchild != nullptr && node -> rightchild != nullptr)
            {
                BinTreeNode<T> *temp = node -> rightchild;
                while(temp -> leftchild != nullptr)
                    temp = temp -> leftchild;
                // 将数据填充到要删除的节点中
                node -> data = temp -> data; 
                // 转而去删除个中序后节点
                // 这时会转到 只有右儿子 或者 没有儿子节点的情况来处理
                Remove(temp -> data , node -> rightchild);  
            }
            else // 不同时拥有左右子树
            {
                BinTreeNode<T> *temp = node;
                if(node -> rightchild != nullptr)
                    node = node -> rightchild;
                else 
                    node = node -> leftchild;
                
                // 删除原node所在的节点
                // 这里由于是指针的引用 所以不会造成断链
                // 具体来说node指针保存在其指向node的双亲节点中
                // 故让node的双亲节点直接指向了node的某个儿子
                // 释放原来node的空间即可实现删除的操作
                delete temp; 
                temp = nullptr;
                return true;
            }
            
        }
        return false;
    }

    BinTree<T>* Search(const T& x , BinTreeNode<T>* &node)
    {
        // 没到找
        if(node == nullptr)
            return nullptr;
        else if(x < node -> data)
            Search(x, node -> leftchild);
        else if (x > node -> data)
            Search(x , node -> rightchild);
        else // 找到
            return node;
    }

};


int BST_Test()
{
    vector<int> data({3  , 1 , 2 , 4 , 5});
    BST<int> tree(data);
    tree.PreOrder();  
    tree.InOrder();
    tree.Remove(3);
    tree.PreOrder();
    tree.InOrder();
}