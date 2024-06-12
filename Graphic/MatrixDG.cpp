#include <iostream>
using namespace std;

#define MAX 100
#define INF INT32_MAX
// 邻接矩阵实现的无向图

const int VEXNUM = 7;
class MatrixDG
{
private:
    char mVexs[MAX]; // 顶点集合
    int mVexNum;     // 顶点数量
    int mEdgNum;     // 边数
    int mMatrix[MAX][MAX]; //邻接矩阵
public:
    // 使用点集合和边集来创建图
    MatrixDG(char *vexs , int vNum , char (*edges)[2] , int eNum);
    ~MatrixDG() {}
    void print();

private:
    int getPosition(char ch);
    int firstVertex(int v); // 返回节点v的第一个邻接节点
    int nextVertex(int v , int w); // 返回节点v相对w的下一个邻接节点
    int DFS(int i , int *visited); 
};

MatrixDG::MatrixDG(char *vexs , int vNum , char (*edges)[2] , int eNum)
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
    
        // mMatrix[p2][p1] = 1;
    }
}

int MatrixDG::getPosition(char ch)
{
    // 返回某个顶点在存储数组中的位置
    for(int i = 0 ; i < mVexNum ; i++)
    {
        if(mVexs[i] == ch)
            return i;
    }
    return -1;
}

void MatrixDG::print()
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

int MatrixDG::firstVertex(int v)
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

int MatrixDG::nextVertex(int v , int w)
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



int main()
{
    char vexs[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G'};
    char edges[][2] = {
        {'A', 'B'},
        {'B', 'C'},
        {'B', 'E'},
        {'B', 'F'},
        {'C', 'E'},
        {'D', 'C'},
        {'E', 'B'},
        {'E', 'D'},
        {'F', 'G'}
    };
    int vNum = sizeof(vexs) / sizeof(vexs[0]);
    int eNum = sizeof(edges) / sizeof(edges[0]);

    MatrixDG mdg(vexs, vNum, edges, eNum);
    mdg.print();


}