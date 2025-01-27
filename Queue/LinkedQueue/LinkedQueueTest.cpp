#include "LinkedQueue.hpp"
#include <cassert>
#include <string>

void testIntQueue() {
    std::cout << "Testing integer queue..." << std::endl;
    
    linkedQueue<int> queue;
    assert(queue.isEmpty() && "New queue should be empty");
    
    // Test enQueue
    for(int i = 1; i <= 5; i++) {
        queue.enQueue(i);
    }
    assert(!queue.isEmpty() && "Queue should not be empty after enQueue");

    // Test deQueue
    int value;
    for(int i = 1; i <= 5; i++) {
        bool success = queue.deQueue(value);
        assert(success && "deQueue should succeed");
        assert(value == i && "Values should be dequeued in FIFO order");
    }
    
    assert(queue.isEmpty() && "Queue should be empty after all deQueue operations");
    
    // Test deQueue on empty queue
    bool success = queue.deQueue(value);
    assert(!success && "deQueue should fail on empty queue");
    
    std::cout << "Integer queue tests passed!" << std::endl;
}

void testStringQueue() {
    std::cout << "Testing string queue..." << std::endl;
    
    linkedQueue<std::string> queue;
    assert(queue.isEmpty() && "New queue should be empty");
    
    // Test enQueue
    queue.enQueue("first");
    queue.enQueue("second");
    queue.enQueue("third");
    
    // Test deQueue
    std::string value;
    queue.deQueue(value);
    assert(value == "first" && "First string should be 'first'");
    queue.deQueue(value);
    assert(value == "second" && "Second string should be 'second'");
    queue.deQueue(value);
    assert(value == "third" && "Third string should be 'third'");
    
    assert(queue.isEmpty() && "Queue should be empty after all deQueue operations");
    
    std::cout << "String queue tests passed!" << std::endl;
}

int main() {
    testIntQueue();
    testStringQueue();
    std::cout << "All tests passed successfully!" << std::endl;
    return 0;
}
