#include <iostream>
using namespace std;

template<typename T>
class SeqStack
{
    int* data , maxSize , top = -1;
public:
    SeqStack(int size = 10)
    {
        data = new int[size];
        maxSize = size;
    }
    ~SeqStack()
    {
        delete[] data;
    }
    
    bool empty()
    {
        return !(top +1);
    }
    
    bool push(const T& x)
    {
        if(top == maxSize - 1)
            return false;
        *(data + (++top)) = x;
        return true;
    }

    bool pop(T& e)
    {
        if(top == -1)
            return false;
        e = *(data + (top--));
        return true;
    }

    bool getTop(T& e)
    {
        if(top == -1)
            return false;
        e = data[top];
        return true;
    }
}; 


int main()
{
    SeqStack<int> stack(10);

    for(int i = 1 ; i <= 5 ; i++)
    {
        stack.push(i);
    }
    for(int i = 1 ; i <= 5 ; i++)
    {
        int e;
        if(stack.pop(e))
            cout << e << " ";
    }
}