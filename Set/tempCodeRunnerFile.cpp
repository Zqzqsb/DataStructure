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