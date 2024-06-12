#include <iostream>
#include <queue>
#include <stack>
#include <vector>
using namespace std;

#define MAX 100


template<typename T>
class ListDG
{
private:
    struct ENode
    {
        int iVex;  // 该边指向顶点的位置
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
    ListDG(T vexs[] , int vNum , T edges[][2] , int eNum);
    ~ListDG() {}
    
    void print();
    void DFS();
    void DFS_NoRecursivl();
    void BFS();
    bool TopoLogicalSort();

private:
    int getPosition(T ch); // 返回节点在邻接表中的位置
    void LinkLast(ENode *list , ENode *node); // 将节点的出边增加
    void DFS(int i , int *visited);
    vector<int> getIndegrees(); // 返回所有节点的入度
};

template<typename T>
ListDG<T>::ListDG(T vexs[] , int vNum , T edges[][2] , int eNum)
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

        // 在有向图中 此部分直接注释
        // node2 = new ENode();
        // node2 -> iVex = p1;
        
        // if(mVexs[p2].firstEdge == nullptr)
        //     mVexs[p2].firstEdge = node2;
        // else
        //     LinkLast(mVexs[p2].firstEdge, node2);
        

    }
}

template<typename T>
int ListDG<T>::getPosition(T data)
{
    for(int i = 0 ; i < mVexNum ; i++)
    {
        if(mVexs[i].data == data)
            return i;
    }
    return -1;
}

template<typename T>
void ListDG<T>::LinkLast(ENode *list , ENode *node)
{
    ENode *p = list;
    while(p -> nextEdge!= nullptr)
        p = p -> nextEdge;
    p -> nextEdge = node;
}

template<typename T>
void ListDG<T>::print()
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
void ListDG<T>::DFS()
{
    int i = 0;
    int visited[MAX] = {0,}; // 数组记录访问过的节点
    vector<int> inDegrees = getIndegrees();
    for(int i = 0 ; i < mVexNum ; i++)
    {
        if(inDegrees[i] == 0 && !visited[i])
            DFS(i , visited);
    }
    cout << endl;
}

template<typename T>
void ListDG<T>::DFS(int i , int* visited)
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
void ListDG<T>::BFS()
{
    queue<int> q;
    int visited[MAX] = {0,}; // 访问矩阵
    
    // 访问头节点
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
        
        // 如果队列空了 寻找下一子图的入口
        if(q.empty())
        {
            vector<int> inDegrees = getIndegrees(); 
            for(int i = 0  ; i < mVexNum ; i++)
            {
                if(inDegrees[i] == 0 && !visited[i])
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
void ListDG<T>::DFS_NoRecursivl()
{
    int visited[MAX] = {0}; // 访问标记数组
    
    //初始化栈
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
        
        // 如果栈空了 则在入度为零的节点中找下一个子图的入口
        if(s.empty())
        {
            vector<int> inDegrees = getIndegrees(); 
            for(int i = 0  ; i < mVexNum ; i++)
            {
                if(inDegrees[i] == 0 && !visited[i])
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

template<typename T>
vector<int> ListDG<T>::getIndegrees()
{
    int inDegree[mVexNum] = {0,};
    // 遍历邻接表
    ENode* e; 
    for(int i = 0 ; i < mVexNum ; i++)
    {
        e = mVexs[i].firstEdge;
        while(e != nullptr)
        {
            inDegree[e -> iVex]++;
            e = e -> nextEdge;
        }
    }; 
    vector<int> res(inDegree , inDegree+mVexNum);
    return res; 
}

template<typename T>
bool ListDG<T>::TopoLogicalSort()
{
    queue<int> q; 
    vector<int> inDegrees = getIndegrees();
    vector<T> res;
    ENode *node;
    // 将所有入度为零的节点入队
    for(int i = 0 ; i < mVexNum ; i++)
    {
        if(inDegrees[i] == 0)
            q.push(i);
    }
    while(!q.empty())
    {
        // 将队首加入拓扑排序序列
        res.push_back(mVexs[q.front()].data);
        // 将该节点指向的所有节点的入度减一 若得到度为零的节点 则加入队列
        node = mVexs[q.front()].firstEdge;
        while(node != nullptr)
        {
            if(--inDegrees[node -> iVex] == 0)
                q.push(node -> iVex);
            node = node -> nextEdge;
        }
        q.pop(); // 弹出队首
    }
    // 如果有元素没有进入拓扑序列则失败
    if(res.size() < mVexNum)
    {
        cout << "图中有环,拓扑排序失败!" << endl;
        return false;
    }
    cout << "拓扑排序结果:";
    for(auto i : res)
        cout << i << " ";
    cout << endl;
}


int main()
{
    char vexs[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G' , 'R' , 'I'};
    char edges[][2] = {
        {'A', 'B'},
        {'B', 'C'},
        {'B', 'E'},
        {'B', 'F'},
        {'C', 'E'},
        {'D', 'I'},
        {'E', 'I'},
        {'E', 'D'},
        {'F', 'G'},
        {'I', 'R'}
    };
    int vNum = sizeof(vexs) / sizeof(vexs[0]);
    int eNum = sizeof(edges) / sizeof(edges[0]);

    ListDG<char> ldg(vexs, vNum, edges, eNum);
    ldg.print();

    ldg.BFS();
    ldg.DFS();
    ldg.DFS_NoRecursivl();
    ldg.TopoLogicalSort();

}
