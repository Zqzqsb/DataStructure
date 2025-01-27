#include "LinkedQueue.hpp"
#include <cassert>
#include <string>
#include <iostream>

void testBasicOperations() {
    std::cout << "Testing basic operations..." << std::endl;
    
    LinkedQueue<int> queue;
    assert(queue.isEmpty() && "New queue should be empty");
    assert(queue.length() == 0 && "New queue should have length 0");
    
    // Test enQueue
    for(int i = 1; i <= 5; i++) {
        queue.enQueue(i);
        assert(queue.length() == i && "Queue length should increase after enQueue");
    }
    assert(!queue.isEmpty() && "Queue should not be empty after enQueue");

    // Test getFront and getRear
    int front, rear;
    assert(queue.getFront(front) && "getFront should succeed");
    assert(front == 1 && "Front element should be 1");
    assert(queue.getRear(rear) && "getRear should succeed");
    assert(rear == 5 && "Rear element should be 5");

    // Test deQueue
    int value;
    for(int i = 1; i <= 5; i++) {
        assert(queue.length() == 6-i && "Queue length should decrease after deQueue");
        bool success = queue.deQueue(value);
        assert(success && "deQueue should succeed");
        assert(value == i && "Values should be dequeued in FIFO order");
    }
    
    assert(queue.isEmpty() && "Queue should be empty after all deQueue operations");
    assert(queue.length() == 0 && "Empty queue should have length 0");
    
    // Test deQueue on empty queue
    bool success = queue.deQueue(value);
    assert(!success && "deQueue should fail on empty queue");
    
    std::cout << "Basic operations tests passed!" << std::endl;
}

void testStringQueue() {
    std::cout << "Testing string queue..." << std::endl;
    
    LinkedQueue<std::string> queue;
    assert(queue.isEmpty() && "New queue should be empty");
    
    // Test enQueue
    queue.enQueue("first");
    queue.enQueue("second");
    queue.enQueue("third");
    assert(queue.length() == 3 && "Queue should have 3 elements");
    
    // Test getFront and getRear
    std::string front, rear;
    assert(queue.getFront(front) && "getFront should succeed");
    assert(front == "first" && "Front element should be 'first'");
    assert(queue.getRear(rear) && "getRear should succeed");
    assert(rear == "third" && "Rear element should be 'third'");
    
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

void testCopyAndAssignment() {
    std::cout << "Testing copy constructor and assignment operator..." << std::endl;
    
    LinkedQueue<int> original;
    for (int i = 1; i <= 3; ++i) {
        original.enQueue(i);
    }
    
    // Test copy constructor
    LinkedQueue<int> copied(original);
    assert(copied.length() == original.length() && "Copied queue should have same length");
    
    int value1, value2;
    while (!original.isEmpty()) {
        original.deQueue(value1);
        copied.deQueue(value2);
        assert(value1 == value2 && "Values should be the same in both queues");
    }
    assert(copied.isEmpty() && "Copied queue should be empty");
    
    // Test assignment operator
    LinkedQueue<int> assigned;
    assigned = original;  // Assigning an empty queue
    assert(assigned.isEmpty() && "Assigned queue should be empty");
    
    // Fill original again and test assignment
    for (int i = 1; i <= 3; ++i) {
        original.enQueue(i);
    }
    assigned = original;
    assert(assigned.length() == original.length() && "Assigned queue should have same length");
    
    while (!original.isEmpty()) {
        original.deQueue(value1);
        assigned.deQueue(value2);
        assert(value1 == value2 && "Values should be the same in both queues");
    }
    
    std::cout << "Copy constructor and assignment operator tests passed!" << std::endl;
}

void testClearOperation() {
    std::cout << "Testing clear operation..." << std::endl;
    
    LinkedQueue<int> queue;
    for (int i = 1; i <= 5; ++i) {
        queue.enQueue(i);
    }
    assert(queue.length() == 5 && "Queue should have 5 elements before clear");
    
    queue.clear();
    assert(queue.isEmpty() && "Queue should be empty after clear");
    assert(queue.length() == 0 && "Queue length should be 0 after clear");
    
    // Test that we can still use the queue after clear
    queue.enQueue(1);
    assert(queue.length() == 1 && "Should be able to enQueue after clear");
    
    int value;
    assert(queue.deQueue(value) && "Should be able to deQueue after clear");
    assert(value == 1 && "Dequeued value should be correct after clear");
    
    std::cout << "Clear operation tests passed!" << std::endl;
}

int main() {
    try {
        testBasicOperations();
        testStringQueue();
        testCopyAndAssignment();
        testClearOperation();
        
        std::cout << "\nAll tests passed successfully!" << std::endl;
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Test failed with exception: " << e.what() << std::endl;
        return 1;
    }
}
