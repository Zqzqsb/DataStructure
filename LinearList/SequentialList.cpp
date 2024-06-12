# include <iostream>
using namespace std;

template<typename T>
class Sqlist
{
public:
    T* data , maxSize , len = 0;

    Sqlist(const int len)
    {
        this -> data = new T[len];
        maxSize = len;
        cout << "Sqlist created!" << endl;
    }
    ~Sqlist()
    {
        delete[] data;
    }

    bool append(const T& element)
    {
        *(data + len++) = element;
    }
    
    bool insert(int index , const T &element)
    {
        if(index < 1 || index > len + 1)
        {
            cout << "insert failed!" << endl;
            return false;
        }
        
        if(len >= maxSize)
        {
            cout << "full!" << endl;
            return false;
        }
        
        // 腾出插入位置
        for(int i = len ; i >= index ; i--)
        {
            *(data+i) = *(data+i-1);
        }
        *(data+index-1) = element;
        (len)++;
        return true;
    }
    
    bool Delete(int index , T &element)
    {
        if(index < 1 || index > len)
            return false;
        element = *(data+index-1);
        for(int i = index - 1 ; i <= (this->len)-2; i++)
            *(data+i) = *(data+i+1);
        (this -> len)--;
        return true;
        
    }

    int locateElement(const T &element)
    {
        for(int i = 0 ; i < len ; i++)
        {
            if(*(data+i) == element)
                return i+1;
        }
        return 0;    
    }

    void print()
    {
        for(int i = 0 ; i < this -> len ; i++)
            cout << *(data+i) << " ";
        cout << endl;
    }


    //------------------------------------------------------
    // 2.01
    bool deleteMin()
    {
        if(len == 0)
        {
            cout << "list is empty" << endl;
            return false;
        }
        T last = *(data + len -1);
        int min_index = 0;
        for(int i = 1 ; i < len ; i++)
        {
            if(*(data+i) < *(data+min_index))
                min_index = i;
        }
        *(data+min_index) = last;
        len--;
        return true;
        
    }

    // 2.02
    void reverseSelf()
    {
        T temp;
        for(int i = 0 ; i < len / 2 ; i++)
        {
            temp = *(data + i);
            *(data + i) = *(data + len - i - 1);
            *(data + len - i - 1) = temp;
        }
        
    }
};

int main()
{
    Sqlist<int> mylist(10);
    for(int i = 1 ; i <= 5 ; i++)
    {
        mylist.append(i);
    }
    mylist.print();
    
    mylist.insert(3 , 0);
    mylist.print();

    int remove;
    mylist.Delete(3 , remove);
    mylist.print();
    cout << remove << endl;

    cout << mylist.locateElement(4) << endl;
    
    mylist.insert(3 , 0);
    mylist.deleteMin();
    mylist.print();

    mylist.reverseSelf();
    mylist.print();
}