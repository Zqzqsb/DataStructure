#include <iostream>
#include <vector>
using namespace std;

template<typename T>
struct Node
{
    T data;
    Node<T>* next;
};

// linked-list with virtual head
template<typename T>
class SingleLinkedList
{
    Node<T>* head;
public:
    // no parameter constructor create Head only
    SingleLinkedList()
    {
        this -> head = new Node<T>;
        this -> head -> next = nullptr;
    }
    
    // head inserter
    SingleLinkedList(const vector<T> &v , bool Reverse = true)
    {   
        head = new Node<T>;
        head -> next = nullptr;
        if(Reverse)
        {
            Node<T>* temp;
            for(auto i : v)
            {
                temp = new Node<T>;
                temp -> data = i;
                temp -> next = head -> next;
                head -> next = temp;
                
            }
        }
        else
        {
            Node<T> *temp , *work = head;
            for(auto i : v)
            {
                temp = new Node<T>;
                temp -> data = i;
                // keep work pointer at the end of the list
                work -> next = temp;
                work = work -> next;
            }
            work -> next = nullptr;
        }
    }
    
    // 析构函数
    ~SingleLinkedList()
    {
        cout << endl << "deleting whole linked list:" << endl;
        Node<T> *work = head -> next;
        while(head != nullptr)
        {
            cout << "delete " << head -> data << endl;
            delete head;
            head = work;
            if(head) work = head -> next;
        }
    }
    
    // 头插
    void insertHead(const T &data)
    {
        Node<T>* toInsert = new Node<T>;
        toInsert -> data = data;
        
        toInsert -> next = head -> next;
        head -> next = toInsert;
    }

    // 尾插
    void append(const T &data)
    {
        Node<T> *toAppend = new Node<T>;
        toAppend -> data = data;
        toAppend -> next = nullptr;
        
        Node<T> *p = this -> head;
        while(p -> next) p = p -> next;
        p -> next = toAppend;
    }
    
    // 删除一个特定位置的元素
    // k 属于 [1 , n] , n为链表的长度
    bool delete_k(int k)
    {
        Node<T>* p = head;

        // 定位到p的前一个为止
        while(p -> next && --k)
        {
            p = p -> next;
        }
        if(p -> next  == nullptr) return false;
        else
        {
            Node<T>* q = p -> next;
            p -> next = q -> next;
            delete q;
            return true;
        }
    }
    
    // 从下标获得元素
    Node<T>* getElement(int index)
    {
        if (index == 0)
            return head;
        if(index < 1)
            return NULL;

        int i = 1;
        Node<T>* work = head -> next;
        while(i < index && work != nullptr)
        {
            work = work -> next;
            i++;
        }
        return work; // if index > i , return nullptr
        
    }

    // 定位元素
    Node<T>* LocateElement(const T& e)
    {
        Node<T>* work = head -> next;
        while(work != nullptr && work -> data != e)
            work = work -> next;
        return work;
    }

    // 翻转
    void reverse()
    {
        Node<T>* work = head -> next;
        Node<T>* work_next;
        head -> next = nullptr;
        while(work != nullptr)
        {
            work_next = work -> next;
            work -> next = head -> next;
            head -> next = work;
            work = work_next;
        }
    } 
    
    // 打印
    void print()
    {
        Node<T>* work = head -> next;
        while(work != nullptr)
        {
            cout << work->data << " ";
            work = work -> next;
        }
        cout << endl;
        return;
    }
};

void print_separator()
{
    cout << "--------------------------------" << endl;
}

int main()
{
    // test constructor
    vector<int> v({1, 2, 3, 4, 5, 6, 7, 8, 9});
    SingleLinkedList<int> sll(v , true);
    cout << "linked list:";
    sll.print();

    // test getElement
    print_separator();
    cout << "get data index at 5: " << sll.getElement(5) -> data << endl;

    // test locaterElement
    print_separator();
    cout << "locate data 6 in list: " <<  sll.LocateElement(6) -> data << endl;   

    // test reverse
    print_separator();
    cout << "after reverse:" << endl;
    sll.reverse();
    sll.print();

    // test insert head
    print_separator();
    cout << "insert head 100:" << endl;
    sll.insertHead(100);
    sll.print();

    // test insert tail
    print_separator();
    cout << "insert tail 100:" << endl;
    sll.append(100);
    sll.print();
    
    // test delete_k
    print_separator();
    cout << "delete at position 5:" << endl;
    sll.delete_k(5);
    sll.print();
    
    print_separator();
}