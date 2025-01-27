#include <iostream>
#include <cassert>
#include <string>
#include "SeqQueue.hpp"

void testIntegerQueue() {
    std::cout << "Testing integer queue..." << std::endl;
    
    // 测试构造函数和基本操作
    SeqQueue<int> queue(5);
    assert(queue.empty());
    assert(queue.len() == 0);
    assert(queue.capacity() == 4);  // 实际容量是size-1

    // 测试入队操作
    assert(queue.enQueue(1));
    assert(queue.enQueue(2));
    assert(queue.enQueue(3));
    assert(queue.enQueue(4));
    assert(!queue.enQueue(5));  // 队列已满，应该返回false
    assert(queue.len() == 4);
    assert(!queue.empty());

    // 测试出队操作
    int value;
    assert(queue.getFront(value));
    assert(value == 1);
    
    assert(queue.deQueue(value));
    assert(value == 1);
    assert(queue.deQueue(value));
    assert(value == 2);
    assert(queue.len() == 2);

    // 测试循环队列特性
    assert(queue.enQueue(5));
    assert(queue.enQueue(6));
    assert(!queue.enQueue(7));  // 队列已满

    // 测试完全清空
    assert(queue.deQueue(value));
    assert(value == 3);
    assert(queue.deQueue(value));
    assert(value == 4);
    assert(queue.deQueue(value));
    assert(value == 5);
    assert(queue.deQueue(value));
    assert(value == 6);
    assert(!queue.deQueue(value));  // 队列为空
    assert(queue.empty());

    std::cout << "Integer queue tests passed!" << std::endl;
}

void testStringQueue() {
    std::cout << "Testing string queue..." << std::endl;
    
    // 测试构造函数和基本操作
    SeqQueue<std::string> queue(4);
    assert(queue.empty());

    // 测试入队操作
    assert(queue.enQueue("Hello"));
    assert(queue.enQueue("World"));
    assert(queue.enQueue("!"));
    assert(!queue.enQueue("Full"));  // 队列已满

    // 测试出队操作
    std::string value;
    assert(queue.deQueue(value));
    assert(value == "Hello");
    assert(queue.deQueue(value));
    assert(value == "World");
    assert(queue.deQueue(value));
    assert(value == "!");
    assert(!queue.deQueue(value));  // 队列为空

    std::cout << "String queue tests passed!" << std::endl;
}

void testCopyConstructorAndAssignment() {
    std::cout << "Testing copy constructor and assignment operator..." << std::endl;
    
    // 准备原始队列
    SeqQueue<int> original(5);
    original.enQueue(1);
    original.enQueue(2);
    original.enQueue(3);

    // 测试拷贝构造
    SeqQueue<int> copied(original);
    assert(!copied.empty());
    assert(copied.len() == original.len());
    
    int value1, value2;
    assert(copied.deQueue(value1));
    assert(original.deQueue(value2));
    assert(value1 == value2);

    // 测试赋值运算符
    SeqQueue<int> assigned(3);  // 不同大小的队列
    assigned = original;
    assert(assigned.len() == original.len());
    
    assert(assigned.deQueue(value1));
    assert(original.deQueue(value2));
    assert(value1 == value2);

    std::cout << "Copy constructor and assignment operator tests passed!" << std::endl;
}

int main() {
    try {
        testIntegerQueue();
        testStringQueue();
        testCopyConstructorAndAssignment();
        
        std::cout << "\nAll tests passed successfully!" << std::endl;
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Test failed with exception: " << e.what() << std::endl;
        return 1;
    }
}
