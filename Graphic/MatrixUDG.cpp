#include <iostream>
#include <queue>
#include <stack>
using namespace std;

#define MAX 100
#define INF INT32_MAX
const int VEXNUM = 7;
// 邻接矩阵实现的无向图
class MatrixUDG
{
private:
    char mVexs[MAX]; // 顶点集合
    int mVexNum;     // 顶点数量
    int mEdgNum;     // 边数
    int mMatrix[MAX][MAX]; //邻接矩阵
public:
    // 使用点集合和边集来创建图
    MatrixUDG(char *vexs , int vNum , char (*edges)[2] , int eNum);
    // 使用已知矩阵来创建图
    MatrixUDG(char *vexs , int vNum , int matrix[][VEXNUM]);
    ~MatrixUDG() {}

    void print();
    void DFS();
    void DFS_NoRecursivl();
    void BFS();
    void Prim(int starter);
private:
    int getPosition(char ch);
    int firstVertex(int v); // 返回节点v的第一个邻接节点
    int nextVertex(int v , int w); // 返回节点v相对w的下一个邻接节点
    void DFS(int i , int *visited);
};

MatrixUDG::MatrixUDG(char *vexs , int vNum , char (*edges)[2] , int eNum)
{
    if(vNum > MAX)
        return;
    mVexNum = vNum;
    mEdgNum = eNum;
    
    // 初始化顶点
    for(int i = 0 ; i < mVexNum ; i++)
        mVexs[i] = vexs[i];
    
    int p1 , p2;
    for(int j = 0 ; j < mEdgNum ; j++)
    {
        // 从二元组中获得起始点和结束点
        p1 = getPosition(edges[j][0]);
        p2 = getPosition(edges[j][1]);
        
        if(p1 == -1 || p2 == -1)
        {
            cout << "无效的顶点" << endl;
            return;
        }
        mMatrix[p1][p2] = 1;
        mMatrix[p2][p1] = 1;
    }
}

MatrixUDG::MatrixUDG(char *vexs , int vNum , int matrix[][VEXNUM])
{
      
    if(!vexs || !*matrix) return;
   
    int i , j;
    mVexNum = vNum;
    mEdgNum = 0;
    for(i = 0 ; i < mVexNum ; i++)
        mVexs[i] = vexs[i];

    // 复制矩阵并且统计边数
    for(i = 0 ; i < mVexNum ; i++)
    {
        for(j = 0 ; j < mVexNum ; j++)
        {
            mMatrix[i][j] = matrix[i][j];
            if(mMatrix[i][j] && i != j)
                mEdgNum++;
        }   
    }
    mEdgNum /= 2;
    cout << "Graphic created!" << endl;
  
}

void MatrixUDG::Prim(int starter)
{
    int min , min_index , sum = 0 ,weights[mVexNum];
    vector<char> prim_res;
    prim_res.push_back(mVexs[starter]);
    cout << mVexs[starter];
    // 初始化权值数组
    for(int i = 0 ; i < mVexNum ; i++)
    {
        weights[i] = mMatrix[starter][i];
    }

    weights[starter] = 0;
    // 整个过程要进行 mVexNum-1次 因为有nVexNum个待连接的节点
    for(int i = 0 ; i <= mVexNum-2 ; i++)
    {
        min_index = 0;
        min = INF;
        for(int j = 0 ; j < mVexNum ; j++)
        {
            // 寻找不在生成树中且一步可达的距离最短节点
            if(weights[j] != 0 && weights[j] < min)
            {
                min = weights[j];
                min_index = j;
            }
        }
        // 将找到的最小节点加入生成树
        prim_res.push_back(mVexs[min_index]);
        sum += min;
        cout << " " << min << " " << mVexs[min_index]  << ",";
        //更新权重
        weights[min_index] = 0;
        for(int i = 0 ; i < mVexNum ; i++)
        {
            // 新节点的加入有可能带来更小的权重 
            // 对于已经在生成树中的节点(权重为零) 则不更新
            if(weights[i] && weights[i] > mMatrix[min_index][i])
                weights[i] = mMatrix[min_index][i];
        } 
    }
    cout << "Prim:(" << mVexs[starter] << ")=" << sum << endl; 
    for(auto i : prim_res)
        cout << i << " ";
    cout << endl;

}

int MatrixUDG::getPosition(char ch)
{
    // 返回某个顶点在存储数组中的位置
    for(int i = 0 ; i < mVexNum ; i++)
    {
        if(mVexs[i] == ch)
            return i;
    }
    return -1;
}

void MatrixUDG::print()
{
    for(int i = 0 ; i < mVexNum ; i++)
    {
        for(int j = 0 ; j < mVexNum ; j++)
        {
            cout << mMatrix[i][j] << " ";
        }
        cout << endl;
    }
}

int MatrixUDG::firstVertex(int v)
{
    if(v < 0 || v >= mVexNum)
        return -1;
    // 遍历v所在的这一行
    for(int i = 0 ; i < mVexNum ; i++)
    {
        if(mMatrix[v][i] == 1)
            return i;
    }
    return -1;
}

int MatrixUDG::nextVertex(int v , int w)
{
    if(v < 0 || v >= mVexNum || w < 0 || w >= mVexNum)
        return -1;
    for(int i = w+1 ; i < mVexNum ; i++)
    {
        if(mMatrix[v][i] == 1)
            return i;
    }
    return -1;
}

void MatrixUDG::DFS()
{
    int visited[mVexNum] = {0,};
    // 由于该图不一定是连通的 所以需要在矩阵中遍历所有节点
    for(int i = 0 ; i < mVexNum ; i++)
    {
        if(!visited[i])
            DFS(i , visited);
    }
    cout << endl;
}

void MatrixUDG::DFS(int v , int* visited)
{
    cout << mVexs[v] << " ";
    visited[v] = 1;
    for(int i = 0 ; i < mVexNum ; i++)
    {
        if(mMatrix[v][i] == 1 && visited[i] == 0)
        {
            DFS(i , visited);
        }
    }
    // for(int i = firstVertex(i) ; w >= 0 ; w= nextVertex(i , w))
    // {
    //     if(!visited[w])
    //         DFS(w , visited);
    // }
}

void MatrixUDG::DFS_NoRecursivl()
{
    stack<int> s;
    int visited[mVexNum] = {0,};
    s.push(0);
    
    int t;
    while(!s.empty())
    {
        // 访问并弹出栈顶节点 并且将该节点能访问所有元素进栈
        t = s.top(); s.pop();
        cout << mVexs[t] << " ";
        visited[t] = 1;
        for(int i = 0 ; i < mVexNum ; i++)
        {
            if(mMatrix[t][i] == 1 && visited[i] == 0)
            {
                visited[i] = 1;
                s.push(i);
            }
        }
        // 如果栈空了 寻找下一子图的入口
        if(s.empty())
        {
            for(int i = 0 ; i < mVexNum ; i++)
            {
                if(visited[i] == 0)
                {
                    visited[i] = 1;
                    s.push(i);
                }
            }
        }
    }
    cout << endl;
}

void MatrixUDG::BFS()
{
    queue<int> q;
    int visited[mVexNum] = {0,};
    // 将0号元素作为访问入口
    q.push(0);
    visited[0] = 1;
    while(!q.empty())
    {
        // 访问队头元素 并将其能访问的所有元素入队
        cout << mVexs[q.front()] << " ";
        for(int w = firstVertex(q.front()) ; w >= 0 ; w = nextVertex(q.front() , w))
        {
            if(!visited[w])
            {
                q.push(w);
                visited[w] = 1;
            }
        }
        q.pop();

        // 如果队列空了 寻找下一子图的入口
        if(q.empty())
        {
            for(int i = 0 ; i < mVexNum ; i++)
            {
                if(visited[i] == 0)
                {
                    q.push(i);
                    visited[i] = 1;
                    break;
                }
            }
        }
    }
}

void traverse_test()
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

    MatrixUDG mudg(vexs, vNum, edges, eNum);
    mudg.print();

    mudg.DFS();
    mudg.DFS_NoRecursivl();
    mudg.BFS();
}


void prim_test()
{
    char vexs[VEXNUM] = {'A', 'B', 'C', 'D', 'E', 'F', 'G'};
    int vNum = sizeof(vexs) / sizeof(vexs[0]);
    int matrix[][VEXNUM] = {
        {0, 12, INF, INF, INF, 16, 14},
        {12, 0, 10, INF, INF, 7, INF},
        {INF, 10, 0, 3, 5, 6, INF},
        {INF, INF, 3, 0, 4, INF, INF},
        {INF, INF, 5, 4, 0, 2, 8},
        {16, 7, 6, INF, 2, 0, 9},
        {14, INF, INF, INF, 8, 9, 0}};
    MatrixUDG mudg(vexs, vNum, matrix);
    // mudg.print();
    mudg.Prim(0);
}

int main()
{
    // traverse_test();
    prim_test();
    
}