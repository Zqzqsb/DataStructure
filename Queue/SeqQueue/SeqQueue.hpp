#ifndef SEQQUEUE_HPP
#define SEQQUEUE_HPP

template<typename T>
class SeqQueue {
private:
    T* data;
    int maxLen;
    int front;
    int rear;

public:
    // 构造函数
    explicit SeqQueue(int len) : maxLen(len), front(0), rear(0) {
        if (len <= 0) {
            throw std::invalid_argument("Queue size must be positive");
        }
        data = new T[len];
    }

    // 析构函数
    ~SeqQueue() {
        delete[] data;
    }

    // 拷贝构造函数
    SeqQueue(const SeqQueue& other) : maxLen(other.maxLen), front(other.front), rear(other.rear) {
        data = new T[maxLen];
        int count = len();
        for (int i = 0; i < count; ++i) {
            int pos = (other.front + i) % maxLen;
            data[pos] = other.data[pos];
        }
    }

    // 赋值运算符
    SeqQueue& operator=(const SeqQueue& other) {
        if (this != &other) {
            T* newData = new T[other.maxLen];
            int count = other.len();
            for (int i = 0; i < count; ++i) {
                int pos = (other.front + i) % other.maxLen;
                newData[pos] = other.data[pos];
            }
            
            delete[] data;
            data = newData;
            maxLen = other.maxLen;
            front = other.front;
            rear = other.rear;
        }
        return *this;
    }

    // 检查队列是否为空
    bool empty() const {
        return front == rear;
    }

    // 获取队列长度
    int len() const {
        return (rear - front + maxLen) % maxLen;
    }

    // 入队操作
    bool enQueue(const T& e) {
        // 检查队列是否已满
        if ((rear + 1) % maxLen == front) {
            return false;
        }
        data[rear] = e;
        rear = (rear + 1) % maxLen;
        return true;
    }

    // 出队操作
    bool deQueue(T& e) {
        if (empty()) {
            return false;
        }
        e = data[front];
        front = (front + 1) % maxLen;
        return true;
    }

    // 获取队首元素
    bool getFront(T& e) const {
        if (empty()) {
            return false;
        }
        e = data[front];
        return true;
    }

    // 获取队列容量
    int capacity() const {
        return maxLen - 1;  // 实际可用容量比maxLen小1
    }
};

#endif // SEQQUEUE_HPP
