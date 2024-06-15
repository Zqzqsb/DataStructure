#include <iostream>
#include <string>
#include <stack>
#include <queue>
using namespace std;

template<typename T>
struct BinTreeNode
{
    T data;
    BinTreeNode<T> *leftchild , *rightchild;
    int ltag , rtag;
    int height;
    BinTreeNode() : leftchild(nullptr) , rightchild(nullptr) , ltag(0) , rtag(0){}
    BinTreeNode(const T& x) : data(x) , leftchild() , rightchild() , ltag(0) , rtag(0) , height(0   ){}
};

template<typename T>
class BinTree
{
protected:
    BinTreeNode<T> *root;

public:

    //constructor && destructor
    BinTree() : root(nullptr) {}
    
    ~BinTree() {Destroy(root);}
    
    // creators

    // create with Generalized table
    void CreateBinTree(const string& GT) {CreateBinTree(root , GT);}
    
    void PreOrder() {PreOrder(root); cout << endl;}

    void InOrder() {InOrder(root); cout << endl;}

    void PostOrder() {PostOrder(root); cout << endl;}

    void PreOrder_NoRecursive() {PreOrder_NoRecursive(root); cout << endl;}

    void PreOrder_NoRecursive1() {PreOrder_NoRecursive1(root); cout << endl;}

    void InOrder_NoRecursive() {InOrder_NoRecursive(root); cout << endl;}

    void PostOrder_NoRecursive() {PostOrder_NoRecursive(root); cout << endl;}

    void LevelOrder() {LevelOrder(root); cout << endl;}

    int Size() {return Size(root);}

    int Height() {return Height(root);}

    void PrintBinTreeInGT() {PrintBinTreeInGT(root); cout << endl;}

    bool operator==(BinTree<T> &s) {return equal(root , s.getRoot());}

    BinTreeNode<T>* getRoot() const {return root;}

    void createInthread() 
    {
        BinTreeNode<T> *pre = nullptr;
        if(root != nullptr)
        {
            createInthread(root , pre);
            pre -> rightchild = nullptr; // last node
            pre -> rtag = 1;
        }
    }
    
    void InOrderWithThread() {InOrderWithThread(root); cout << endl;}

    int Cal() {return Cal(root);}
protected:

    void CreateBinTree(BinTreeNode<T> *&BT , const string& table)
    {
        // A(B(D,E(G,)),C(,F))
        stack<BinTreeNode<T> *> s;
        BT = nullptr;
        BinTreeNode<T> *p , *t; // p - work pointer t pointer to stack.top()
        int k; // flag for child

        for(char i : table)
        {
            switch(i)
            {
                // repesent the begin of substructure of p
                case '(' : s.push(p); k=1; break;
                // repesent the end of substructure of stack.top()
                case ')' : s.pop(); break;
                // switch between children
                case ',' : k=2; break;

                default:
                    p = new BinTreeNode<T>(i);
                    if(BT == nullptr) // create root
                    {
                        BT = p;
                    }
                    else if(k==1) // create leftchild
                    {
                        t = s.top();
                        t -> leftchild = p;
                    }
                    else // create rightchild
                    {
                        t = s.top();
                        t -> rightchild = p;
                    }
            }
        }
    }

    void Destroy(BinTreeNode<T> *&subTree)
    {
        if(subTree != nullptr)
        {
            // recursively destroy all children
            Destroy(subTree -> leftchild);
            Destroy(subTree -> rightchild);
            // free space
            delete subTree;
            // reset pointer
            subTree = nullptr;
        }
    }

    void PreOrder(BinTreeNode<T> *& subTree)
    {
        if(subTree != nullptr)
        {
            cout << subTree -> data << " ";
            PreOrder(subTree -> leftchild);
            PreOrder(subTree -> rightchild);
        }
    }

    void InOrder(BinTreeNode<T> *& subTree)
    {
        if(subTree != nullptr)
        {
            InOrder(subTree -> leftchild);
            cout << subTree -> data << " ";
            InOrder(subTree -> rightchild);
        }
    }

    void PostOrder(BinTreeNode<T> *& subTree)
    {
        if(subTree != nullptr)
        {
            PostOrder(subTree -> leftchild);
            PostOrder(subTree -> rightchild);
            cout << subTree -> data << " ";
        }
    }

    void PreOrder_NoRecursive(BinTreeNode<T> *p) // can't use & otherwise change root 
    {
        stack<BinTreeNode<T>*> s;
        s.push(nullptr);
        while(p != nullptr)
        {
            cout << p -> data << " "; // 先访问自己
            // 如果有右儿子 将右儿子压栈
            if(p -> rightchild != nullptr) 
                s.push(p -> rightchild);
            // 进到左儿子 重复该过程
            if(p -> leftchild != nullptr)
                p = p -> leftchild;
            else // 如果没有左儿子 则弹出一个右儿子作为当前节点
            {
                p = s.top();
                s.pop();
            }
        }
    }

    void PreOrder_NoRecursive1(BinTreeNode<T> *p)
    {
        stack<BinTreeNode<T>*> s;
        BinTreeNode<T> *t;
        s.push(p);
        while(!s.empty())
        {
            // 对于每个栈顶元素 先访问它自己 再将右子孙压栈(后访问)
            // 再将左子孙压栈
            t = s.top();
            cout << t -> data << " ";
            s.pop();
            if(t -> rightchild != nullptr)
                s.push(t -> rightchild);
            if(t -> leftchild != nullptr)
                s.push(t -> leftchild);
        }
    }

    void InOrder_NoRecursive(BinTreeNode<T> *p)
    {
        stack<BinTreeNode<T>*> s;
        do
        {
            // 直接去到最左子孙
            while(p != nullptr)
            {
                s.push(p);
                p = p -> leftchild; // 将所有的左子孙压栈
            }
            // 从栈中弹出先前压栈左儿子 并访问
            // 此时对于子树而言 其左儿子和当前节点(双亲节点)已经被访问
            // 可以去到右儿子并重复该过程
            if(!s.empty())
            {
                p = s.top();
                s.pop();
                cout << p -> data << " ";
                p = p -> rightchild;
            }
        }
        while(p != nullptr || !s.empty());
    }

    void PostOrder_NoRecursive(BinTreeNode<T> *p)
    {
        if(p == nullptr)
            return;
        stack<BinTreeNode<T>*> s;
        s.push(p);
        BinTreeNode<T> *lastPop = nullptr; // 记录上一个从栈中弹出的元素
        while(!s.empty())
        {
            // 压栈所有的左子孙节点 找到第一个访问的元素
            while(s.top() -> leftchild != nullptr)
                s.push(s.top() -> leftchild);
            
            while(!s.empty())
            {
                // 如果栈顶元素有右儿子 压栈右儿子 并且退出该过程
                // 在上面的循环中压栈该右儿子所有的左儿子
                // 这一步的原因是 如果栈顶元素没有右儿子 那么它是叶子节点 第一个被访问
                // 如果它有右儿子 则它的右子树应该在后续遍历中被第一个访问
                if(s.top() -> rightchild != nullptr)
                {
                    s.push(s.top() -> rightchild);
                    break;
                }
                // 如果上一个弹出的是栈顶的右儿子 或者 栈顶元素没有右儿子
                // 则说明对该节点左右子树的访问均已经完成
                // 可以弹出该节点
                else if(lastPop == s.top() -> rightchild || s.top() -> rightchild == nullptr)
                {
                    cout << s.top() -> data << " ";
                    lastPop = s.top();
                    s.pop();
                }
            }
        }
    }

    void LevelOrder(BinTreeNode<T> *p)
    {
        queue<BinTreeNode<T>*> Q;
        Q.push(p);
        while(!Q.empty())
        {
            if(Q.front() -> leftchild != nullptr)
                Q.push(Q.front() -> leftchild);
            if(Q.front() -> rightchild != nullptr)
                Q.push(Q.front() -> rightchild);
            cout << Q.front() -> data << " ";
            Q.pop();
        }
    }

    int Size(BinTreeNode<T> *subTree)
    {
        if(subTree == nullptr)
            return 0;
        return 1 + Size(subTree -> leftchild) + Size(subTree -> rightchild);
    }

    int Height(BinTreeNode<T> *subTree)
    {
        if (subTree == nullptr)
            return 0;
        return 1 + max(Height(subTree -> leftchild) ,Height(subTree -> rightchild));
    }

    void PrintBinTreeInGT(BinTreeNode<T> *BT)
    {
        if(BT != nullptr)
        {
            cout << BT -> data;
            if(BT -> leftchild != nullptr || BT -> rightchild!= nullptr) 
            {
                cout << '(';
                if(BT -> leftchild != nullptr)
                    PrintBinTreeInGT(BT -> leftchild);
                cout << ",";
                if(BT -> rightchild != nullptr)
                    PrintBinTreeInGT(BT -> rightchild);
                cout << ")";
            }
        }
    }

    BinTreeNode<T>* Parent(BinTreeNode<T>* subTree , BinTreeNode<T>* current)
    {
        if(subTree == nullptr)
            return nullptr;
        if(subTree -> leftchild == current || subTree -> rightchild == current)
            return subTree;
        BinTreeNode<T>* p; // reduce the time of recursive
        if((p = Parent(subTree->leftchild, current)) != nullptr)
            return p;
        else
            return Parent(subTree->right , current);
    }

    bool equal(BinTreeNode<T>* a , BinTreeNode<T>* b)
    {
        if(a == nullptr && b == nullptr)
            return true;
        if(a != nullptr && b != nullptr && a -> data == b -> data && equal(a -> leftchild , b -> leftchild) && equal(b -> rightchild , b -> rightchild))
            return true;
        return false;
    }

    void createInthread(BinTreeNode<T>* current , BinTreeNode<T> *&pre)
    {
        // 实现该算法时 需理解 根据二叉线索树建立的原理
        // pre 为 current的前一个 在它们之间建立线索只有两种情况
        // current的左为空(前) 或者 pre的右为空(后)
        if(current == nullptr)
            return;
        createInthread(current -> leftchild, pre); // recursive in left child
        // current左子树为空时 根据pre建立向前的线索
        if(current -> leftchild == nullptr) 
        {
            current -> leftchild = pre;
            current -> ltag = 1;
        }
        // pre的右子树为空时
        // 根据建立pre节点向后的线索(pre的后一个为current)
        if(pre != NULL && pre -> rightchild == NULL)
        {
            pre -> rightchild = current;
            pre -> rtag = 1;
        }
        pre = current; // 在函数调用退栈的过程中 pre总是记录刚刚访问的元素
        createInthread(current -> rightchild, pre);
    }

    BinTreeNode<T> *InOrderFirst(BinTreeNode<T>* current)
    {
        BinTreeNode<T> *p = current;
        // 找到正常中序遍历左下节点(不一定是叶节点,可能有一个右儿子)
        while(p -> ltag == 0)
            p = p -> leftchild;
        return p;
    }

    BinTreeNode<T> *InOrderNext(BinTreeNode<T>* current)
    {
        // p为当前节点的右孩子
        BinTreeNode<T> *p = current -> rightchild;
        // 如果右子树有子结构 那么返回该子结构的第一个
        if(current -> rtag == 0)
            return InOrderFirst(p);
        // 如果没有 返回p
        return p;
    }
    
    BinTreeNode<T> *InOrderLast(BinTreeNode<T>* current)
    {
        BinTreeNode<T>* p = current -> rightchild;
        // 最后一个元素一定在右子树中 且它的rtag为零
        // 该节点的右儿子为零或者转到其他分支上的节点
        while(p -> rtag == 0)
            p = p -> rightchild;
        return p;
        
    }

    BinTreeNode<T> *InOrderPrior(BinTreeNode<T>* current)
    {
        // 如果没有左儿子 第一个就是current(中间节点)
        if(current -> ltag == 1)
            return current;
        else // 如果有左儿子 即为左儿子遍历的最后一个节点
        {
            return InOrderLast(current);
        }
            
    }

    void InOrderWithThread(BinTreeNode<T> *p)
    {
        for(p = InOrderFirst(p) ; p != nullptr ; p = InOrderNext(p))
            cout << p -> data << " ";
    }

    int Cal(BinTreeNode<T> *p)
    {
        if(p == nullptr)
            return 0;
        int sum = (int) ((p -> data) - 'A');
        return sum + Cal(p -> leftchild) + Cal(p->rightchild);
    }
};

void testTree()
{
    string table = "A(B(D,E(G,)),C(,F)";
    BinTree<char> tree;
    tree.CreateBinTree(table);
    tree.PreOrder();
    tree.PreOrder_NoRecursive();
    tree.PreOrder_NoRecursive1();
    cout << endl;
    tree.InOrder();
    tree.InOrder_NoRecursive();
    cout << endl;
    tree.PostOrder();
    tree.PostOrder_NoRecursive();
    cout << endl;
    tree.LevelOrder();

    cout << tree.Size() << endl;
    cout << tree.Height() << endl;

    tree.PrintBinTreeInGT();
    
    // tree.createInthread();
    // tree.InOrderWithThread();

    cout << tree.Cal() << endl;
}