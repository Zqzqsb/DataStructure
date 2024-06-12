#include <iostream>
using namespace std;

#define MAXN 100

int fa[MAXN] , rk[MAXN];
inline void init(int n)
{
    // 将每个人的父节点都初始化为自己
    for(int i = 1 ; i <= n ; ++i)
    {
        fa[i] = i;
        rk[i] = 1;
    }
}

int find(int x)
{
    // 如果父节点为自己 返回 否则继续向上查找
    return x == fa[x] ? x : (fa[x] = find(fa[x]));
}

inline void merge(int i , int j)
{
    // 将i的父节点 设为j的父节点
    int x = find(i) , y = find(j);
    // 秩大的合并秩小的
    if(rk[x] <= rk[y])
        fa[x] = y;
    else
        fa[y] = x;
        
    // 如果秩不等且父节点不相等
    // 因为在此情况下是y 合并 x 所以y(秩相对大的)秩增加
    if(rk[x] == rk[y] && x != y)
        rk[y]++;
}



int main()
{
    cout << "main" << endl;
}

