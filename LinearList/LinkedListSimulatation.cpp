#include<iostream>
using namespace std;

const int N = 1e5; // 规定了链表可用的空间数量
// head 表示一个链表的头结点在 e数组中的位置 
// e[head] 是 head的值 对应结构体中的 head -> data
// ne[head] 是 head -> next 在 e中的位置。
// 可以类推 e 数组存储了 每个节点的数据 而 ne数组存储了 下一节点的位置
// head = -1 意味着 head -> next = nullptr 当 ne[i] = -1 代表访问到了链表最后一个位置。
int e[N] , ne[N] , head = -1 , idx = 1; 

// 头插法
void insert_head(int x)
{
    e[idx] = x;
    ne[idx] = head;
    head = idx++;
}

void insert_tail(int x)
{
    int p = head;
    while(ne[p] != -1)
        p = ne[p];
    e[idx] = x;
    ne[idx] = ne[p];
    ne[p] = idx++;
}

void print_linked_list()
{
    int p = head;
    while(p != -1)
    {
        cout << e[p] << " ";
        p = ne[p];
    }
    cout << endl;
}

int main()
{
    insert_head(1);
    insert_head(2);
    insert_tail(100);
    insert_tail(200);
    print_linked_list();
}