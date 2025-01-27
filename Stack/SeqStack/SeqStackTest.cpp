#include <iostream>
#include <cassert>
#include <string>
#include "SeqStack.hpp"

void testEmptyStack() {
    std::cout << "Testing empty stack..." << std::endl;
    SeqStack<int> stack;
    assert(stack.empty() == true);
    assert(stack.size() == 0);
    assert(stack.capacity() == 10); // Default size
    std::cout << "Empty stack test passed!" << std::endl;
}

void testPushPop() {
    std::cout << "Testing push and pop operations..." << std::endl;
    SeqStack<int> stack(5);
    assert(stack.capacity() == 5);
    
    // Test push
    for (int i = 1; i <= 5; i++) {
        assert(stack.push(i) == true);
        assert(stack.size() == i);
    }
    // Test stack full
    assert(stack.full() == true);
    assert(stack.push(6) == false);
    
    // Test pop and values
    int value;
    for (int i = 5; i >= 1; i--) {
        assert(stack.pop(value) == true);
        assert(value == i);
        assert(stack.size() == i - 1);
    }
    // Test empty after pop
    assert(stack.empty() == true);
    assert(stack.pop(value) == false);
    std::cout << "Push and pop tests passed!" << std::endl;
}

void testGetTop() {
    std::cout << "Testing getTop operation..." << std::endl;
    SeqStack<int> stack;
    int value;
    
    // Test getTop on empty stack
    assert(stack.getTop(value) == false);
    
    // Test getTop after push
    stack.push(42);
    assert(stack.getTop(value) == true);
    assert(value == 42);
    assert(stack.size() == 1);
    
    // Verify getTop doesn't remove element
    assert(stack.getTop(value) == true);
    assert(value == 42);
    assert(stack.size() == 1);
    std::cout << "GetTop tests passed!" << std::endl;
}

void testCopyConstructor() {
    std::cout << "Testing copy constructor..." << std::endl;
    SeqStack<int> stack1(3);
    stack1.push(1);
    stack1.push(2);
    stack1.push(3);
    
    // Create a copy
    SeqStack<int> stack2(stack1);
    
    // Verify contents are the same
    int val1, val2;
    while (!stack1.empty() && !stack2.empty()) {
        stack1.pop(val1);
        stack2.pop(val2);
        assert(val1 == val2);
    }
    assert(stack1.empty() == stack2.empty());
    std::cout << "Copy constructor test passed!" << std::endl;
}

void testAssignmentOperator() {
    std::cout << "Testing assignment operator..." << std::endl;
    SeqStack<int> stack1(3);
    stack1.push(1);
    stack1.push(2);
    stack1.push(3);
    
    // Create another stack and assign
    SeqStack<int> stack2(5); // Different size
    stack2 = stack1;
    
    // Verify contents are the same
    int val1, val2;
    while (!stack1.empty() && !stack2.empty()) {
        stack1.pop(val1);
        stack2.pop(val2);
        assert(val1 == val2);
    }
    assert(stack1.empty() == stack2.empty());
    std::cout << "Assignment operator test passed!" << std::endl;
}

void testDifferentTypes() {
    std::cout << "Testing stack with different types..." << std::endl;
    
    // Test with double
    SeqStack<double> doubleStack;
    assert(doubleStack.push(3.14) == true);
    double dValue;
    assert(doubleStack.getTop(dValue) == true);
    assert(dValue == 3.14);
    
    // Test with string
    SeqStack<std::string> stringStack;
    assert(stringStack.push("Hello") == true);
    std::string sValue;
    assert(stringStack.getTop(sValue) == true);
    assert(sValue == "Hello");
    
    // Test with char
    SeqStack<char> charStack;
    assert(charStack.push('A') == true);
    char cValue;
    assert(charStack.getTop(cValue) == true);
    assert(cValue == 'A');
    std::cout << "Different types tests passed!" << std::endl;
}

int main() {
    std::cout << "Starting SeqStack tests..." << std::endl;
    
    testEmptyStack();
    testPushPop();
    testGetTop();
    testCopyConstructor();
    testAssignmentOperator();
    testDifferentTypes();
    
    std::cout << "All tests passed successfully!" << std::endl;
    return 0;
}
