#include <iostream>
#include <cassert>
#include "SeqStack.cpp"

void testEmptyStack() {
    std::cout << "Testing empty stack..." << std::endl;
    SeqStack<int> stack;
    assert(stack.empty() == true);
    std::cout << "Empty stack test passed!" << std::endl;
}

void testPushPop() {
    std::cout << "Testing push and pop operations..." << std::endl;
    SeqStack<int> stack(5);
    
    // Test push
    for (int i = 1; i <= 5; i++) {
        assert(stack.push(i) == true);
    }
    // Test stack full
    assert(stack.push(6) == false);
    
    // Test pop and values
    int value;
    for (int i = 5; i >= 1; i--) {
        assert(stack.pop(value) == true);
        assert(value == i);
    }
    // Test empty after pop
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
    
    // Verify getTop doesn't remove element
    assert(stack.getTop(value) == true);
    assert(value == 42);
    std::cout << "GetTop tests passed!" << std::endl;
}

void testDifferentTypes() {
    std::cout << "Testing stack with different types..." << std::endl;
    
    // Test with double
    SeqStack<double> doubleStack;
    assert(doubleStack.push(3.14) == true);
    double dValue;
    assert(doubleStack.getTop(dValue) == true);
    assert(dValue == 3.14);
    
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
    testDifferentTypes();
    
    std::cout << "All tests passed successfully!" << std::endl;
    return 0;
}
