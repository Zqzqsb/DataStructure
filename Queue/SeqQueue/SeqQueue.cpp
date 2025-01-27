#include <iostream>
using namespace std;

template<typename T>
class SeqQueue
{
    int *data , maxLen , front = 0 , rear = 0;

public:
    SeqQueue(int len)
    {
        data = new T[len];
        maxLen = len;
    }
    ~SeqQueue()
    {
        delete[] data;
    }
    
    bool empty()
    {
        return (front == rear);
    }

    int len()
    {
        return (rear-front+maxLen) % maxLen;
    }

    bool enQueue(const T& e)
    {
        // in case of rear = maxsize - 1 and 
        // front = 0 
        if((rear + 1) % maxLen == front)
            return false;
        *(data + rear) = e;
        rear = (rear+1)%maxLen;
        return true;
    }
    
    bool deQueue(T& e)
    {
        if(empty()) return false;
        e = *(data + front);
        front = (front + 1) % maxLen;
        return true;
    }
};

int main()
{
    SeqQueue<int> queue(10);
    cout << boolalpha << queue.empty() << endl;
    
    for(int i = 1 ; i <= 5 ; i++)
    {
        queue.enQueue(i);
    }

    for(int i = 1 ; i <= 5 ; i++)
    {
        int e;
        if (queue.deQueue(e))
            cout << e << " ";
    }
}