#include <iostream>
#include <vector>
using namespace std;

void insert_sort(vector<int>& v)
{
    int key;
    for(int i = 1 ; i <= v.size() ; i++)
    {
        key = v[i];
        // 折半搜索找插入位置 找第一个比v[i]小的元素
        // 或者说向前找最后一个比v[i]大的元素
        int high = i-1, low = 0 , mid;
        while(low <= high)
        {
            // mid为low + high向下取整
            mid = (low + high) / 2;
            if(v[i] < v[mid])
                high = mid - 1;
            else
                low = mid + 1;
        }
        // 最终high+1并且为第一个大于v[i]的元素
        // 所以插入位置是v[hig+1] 将从high开始的元素后移
        for(int j = i-1; j >= high+1 ; j--)
            v[j+1] = v[j];
        v[high+1] = key;
    }
}
void shell_sort(vector<int>& v)
{
    int temp , j;
    for(int k = v.size() / 2 ; k >= 1 ; k--)
    {
        // 对于插入排序而言 第一个分组0 - (k-1)的单个元素视为有序
        // 所以从k开始向后移动寻找元素 向前插入
        for(int i = k ; i <= v.size() - 1 ; i++)
        {
            j = 0 , temp = v[i];
            while(i - (j+1)*k >= 0 && v[i - (j+1)*k] >= v[i - j*k])
            {
                v[i - j*k] = v[i - (j+1)*k];
                j++;
            }
            if(j != 0)
                v[i - j*k] = temp;
        }
    }
}



int main()
{
    vector<int> v({37, 33, 42, 28, 46, 5, 6, 8, 81, 23, 28, 66, 47, 1, 58, 80, 29, 67, 95, 97});
    // shell_sort(v);
    insert_sort(v);
    
    for(auto i : v)
        cout << i << " ";
    cout << endl;
}