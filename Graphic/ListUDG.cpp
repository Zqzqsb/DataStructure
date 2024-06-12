#include <iostream>
#include <queue>
#include <stack>
using namespace std;

#define MAX 100

template<typename T>
struct EData
{
    EData() {}
    EData(T s , T e , int w) : start(e) , end(e) , weight(w) {}
    
    T start;
    T end;
    int weight;
};

template<typename T>
class ListUDG
{
private:
    struct ENode
    {
        int iVex;  // 该边指向顶点的位置
        int weight; // 该条边的权重
        ENode *nextEdge = nullptr; // 下一条边的指针
    };
    struct VNode
    {
        T data; // 顶点数据 
        ENode* firstEdge = nullptr; // 第一条出边的指针
    };
    
private:
    int mVexNum; // 节点数量
    int mEdgeNum; // 边数量
    VNode mVexs[MAX]; // 邻接表
    
public:
    ListUDG(T vexs[] , int vNum , T edges[][2] , int eNum);
    ListUDG(T vexs[] , int vNum , EData<T>* edges[] , int eNum);
    ~ListUDG() {}
    
    void print();
    void DFS();
    void DFS_NoRecursivl();
    void BFS();

private:
    int getPosition(T ch); // 返回节点在邻接表中的位置
    void LinkLast(ENode *list , ENode *node); // 将节点的出边增加
    void DFS(int i , int *visited); 
};

template<typename T>
ListUDG<T>::ListUDG(T vexs[] , int vNum , T edges[][2] , int eNum)
{
    if(vNum > MAX || eNum > MAX)
        return;
    T c1 , c2;
    int p1 , p2;
    ENode *node1 , *node2;
    mVexNum = vNum;
    mEdgeNum = eNum;
    // 将节点存入邻接表
    for(int i = 0 ; i < mVexNum ; i++)
    {
        mVexs[i].data = vexs[i];
    }
    for(int j = 0 ; j < mEdgeNum ; j++)
    {
        // 拿到两个顶点
        c1 = edges[j][0];
        c2 = edges[j][1];

        // 得到两个顶点的位置
        p1 = getPosition(c1);
        p2 = getPosition(c2);
        
        if(p1 == -1 || p2 == -1)
        {
            cout << "顶点不合法" << endl;
            return;
        }
        // 创建一条新边 由c1指向c2节点所在的位置p2
        node1 = new ENode();
        node1 -> iVex = p2;
        
        if(mVexs[p1].firstEdge == nullptr)
            mVexs[p1].firstEdge = node1; // 设为邻接表p1节点的第一条出边
        else
            LinkLast(mVexs[p1].firstEdge, node1);

        // 因为是无向图 对c2也做同样的操作
        node2 = new ENode();
        node2 -> iVex = p1;
        
        if(mVexs[p2].firstEdge == nullptr)
            mVexs[p2].firstEdge = node2;
        else
            LinkLast(mVexs[p2].firstEdge, node2);
        

    }
}

template<typename T>
ListUDG<T>::ListUDG(T vexs[] , int vNum , EData<T>* edges[] , int eNum)
{
    if (vNum > MAX || eNum > MAX)
        return;
    char c1, c2;
    int p1, p2;
    ENode *node1, *node2;
    int weight;
    //初始化顶点数和边数
    mVexNum = vNum;
    mEdgeNum = eNum;
    //初始化邻接表的顶点
    for (int i = 0; i < mVexNum; ++i)
    {
        mVexs[i].data = vexs[i];
        mVexs[i].firstEdge = NULL;
    }
    //初始化邻接表的边
    for (int j = 0; j < mEdgeNum; ++j)
    {
        //读取边的起始顶点和结束顶点
        c1 = edges[j]->start;
        c2 = edges[j]->end;
        weight = edges[j]->weight;
        p1 = getPosition(c1);
        p2 = getPosition(c2);
        if (p1 == -1 || p2 == -1)
        {
            cout << "输入的边有错误！" << endl;
            return;
        }
        //初始化node1
        node1 = new ENode();
        node1->iVex = p2;
        node1->weight = weight;
        //将node1链接到p1所在的链表末尾
        if (mVexs[p1].firstEdge == NULL)
            mVexs[p1].firstEdge = node1;
        else
            linkLast(mVexs[p1].firstEdge, node1);
        //初始化node2
        node2 = new ENode();
        node2->iVex = p1;
        node2->weight = weight;
        //将node2链接到p2所在链表末尾
        if (mVexs[p2].firstEdge == NULL)
            mVexs[p2].firstEdge = node2;
        else
            linkLast(mVexs[p2].firstEdge, node2);
    }
}

template<typename T>
int ListUDG<T>::getPosition(T data)
{
    for(int i = 0 ; i < mVexNum ; i++)
    {
        if(mVexs[i].data == data)
            return i;
    }
    return -1;
}

template<typename T>
void ListUDG<T>::LinkLast(ENode *list , ENode *node)
{
    ENode *p = list;
    while(p -> nextEdge!= nullptr)
        p = p -> nextEdge;
    p -> nextEdge = node;
}

template<typename T>
void ListUDG<T>::print()
{
    ENode *node;
    for(int i = 0 ; i < mVexNum ; i++)
    {
        cout << i << "(" << mVexs[i].data << "):";
        node = mVexs[i].firstEdge;
        while(node != nullptr)
        {
            cout << node -> iVex << "(" << mVexs[node -> iVex].data << ")";
            node = node -> nextEdge;
        }
        cout << endl;
    }
}

template<typename T>
void ListUDG<T>::DFS()
{
    int i = 0;
    int visited[MAX] = {0,}; // 数组记录访问过的节点
    cout << "DFS:" << endl; 
    for(int i = 0 ; i < mVexNum ; i++)
    {
        if(!visited[i])
            DFS(i , visited);
    }
    cout << endl;
}

template<typename T>
void ListUDG<T>::DFS(int i , int* visited)
{
    visited[i] = 1; // 访问了这个节点
    cout << mVexs[i].data << " ";
    ENode *node = mVexs[i].firstEdge; // 如果这个节点有出边 则沿着出边访问
    while(node != nullptr)
    {
        if(!visited[node -> iVex]) // 保证该节点之前没有访问过
            DFS(node -> iVex , visited); // 总是沿着节点第一条出边访问
        node = node -> nextEdge; // 在函数退栈时 如果有其他边 访问其他边
    }
}

template<typename T>
void ListUDG<T>::BFS()
{
    queue<int> q;
    int visited[mVexNum] = {0,}; // 访问矩阵
    
    // 初始化队列 将0号元素作为访问入口
    q.push(0);
    visited[0] = 1;

    ENode* e;
    while(!q.empty())
    {
        // 访问队头元素可以访问的所有节点 并将它们全部入队
        e = mVexs[q.front()].firstEdge;
        cout << mVexs[q.front()].data << " ";
        q.pop();
        while(e != nullptr)
        {
            if(!visited[e -> iVex])
            {
                visited[e -> iVex] = 1;
                q.push(e -> iVex);
            }
            e = e -> nextEdge;
        }
        
        // 因为图不一定是连通的 如果队列空了 说明该子图已经全部访问完毕
        // 试着寻找下一个元素作为访问的入口
        if(q.empty())
        {
            for(int i = 0 ; i < mVexNum ; i++)
            {
                if(!visited[i])
                {
                    q.push(i);
                    visited[i] = 1;
                    break;
                }
            }
        }
    }
    cout << endl;
}

template<typename T>
void ListUDG<T>::DFS_NoRecursivl()
{
    int visited[mVexNum] = {0}; // 访问标记数组
    
    //初始化栈 将0号元素作为访问入口
    stack<int> s;
    s.push(0);
    visited[0] = 1;

    int t;
    ENode* e;
    

    while(!s.empty())
    {
        // 访问栈顶并弹出 并且将它可以访问的所有元素压栈
        t = s.top(); s.pop();
        cout << mVexs[t].data << " ";
        e = mVexs[t].firstEdge;
        while(e != nullptr)
        {
            if(!visited[e -> iVex])
            {
                s.push(e -> iVex);
                visited[e -> iVex] = 1;
            }
            e = e -> nextEdge;
        }
        // 因为图不一定是连同的 如果栈空了 说明该子图已经全部访问完毕
        // 试着寻找下一个元素作为访问的入口
        if(s.empty())
        {
            for(int i = 0 ; i < mVexNum ; i++)
            {
                if(!visited[i])
                {
                    s.push(i);
                    visited[i] = 1;
                    break;
                }
            }
        }
    }


    cout << endl;
}

int main()
{
    char vexs[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G' , 'I' , 'R'};
    char edges[][2] = {
        {'A', 'C'},
        {'A', 'D'},
        {'A', 'F'},
        {'B', 'C'},
        {'C', 'D'},
        {'E', 'G'},
        {'F', 'G'},
        {'I', 'R'}
    };
    int vNum = sizeof(vexs) / sizeof(vexs[0]);
    int eNum = sizeof(edges) / sizeof(edges[0]);

    ListUDG<char> ludg(vexs, vNum, edges, eNum);
    ludg.print();

    ludg.DFS();
    ludg.BFS();
    ludg.DFS_NoRecursivl();
}
