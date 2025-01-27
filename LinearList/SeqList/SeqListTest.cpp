#include "SeqList.hpp"
#include <iostream>
#include <cassert>
#include <string>

void testBasicOperations() {
    std::cout << "Testing basic operations..." << std::endl;
    
    SeqList<int> list(10);
    assert(list.empty() && "New list should be empty");
    assert(list.size() == 0 && "New list should have size 0");
    assert(list.capacity() == 10 && "List capacity should be 10");

    // Test append
    for (int i = 1; i <= 5; ++i) {
        assert(list.append(i) && "Append should succeed");
    }
    assert(list.size() == 5 && "List size should be 5 after appending");

    // Test insert
    assert(list.insert(3, 0) && "Insert should succeed");
    int value;
    assert(list.get(3, value) && "Get should succeed");
    assert(value == 0 && "Inserted value should be 0");

    // Test remove
    assert(list.remove(3, value) && "Remove should succeed");
    assert(value == 0 && "Removed value should be 0");
    assert(list.size() == 5 && "List size should be 5 after remove");

    // Test locate
    assert(list.locate(4) == 4 && "Element 4 should be at position 4");

    std::cout << "Basic operations tests passed!" << std::endl;
}

void testStringList() {
    std::cout << "Testing string list..." << std::endl;
    
    SeqList<std::string> list(5);
    
    // Test append
    assert(list.append("Hello") && "Append should succeed");
    assert(list.append("World") && "Append should succeed");
    assert(list.size() == 2 && "List size should be 2");

    // Test get
    std::string value;
    assert(list.get(1, value) && "Get should succeed");
    assert(value == "Hello" && "First element should be 'Hello'");

    // Test set
    assert(list.set(1, "Hi") && "Set should succeed");
    assert(list.get(1, value) && "Get should succeed");
    assert(value == "Hi" && "First element should now be 'Hi'");

    std::cout << "String list tests passed!" << std::endl;
}

void testCopyAndAssignment() {
    std::cout << "Testing copy constructor and assignment operator..." << std::endl;
    
    SeqList<int> original(5);
    for (int i = 1; i <= 3; ++i) {
        original.append(i);
    }
    
    // Test copy constructor
    SeqList<int> copied(original);
    assert(copied.size() == original.size() && "Copied list should have same size");
    
    int value1, value2;
    for (int i = 1; i <= 3; ++i) {
        assert(copied.get(i, value1) && original.get(i, value2) && "Get should succeed");
        assert(value1 == value2 && "Values should be the same in both lists");
    }

    // Test assignment operator
    SeqList<int> assigned(3);  // Different size
    assigned = original;
    assert(assigned.size() == original.size() && "Assigned list should have same size");
    
    for (int i = 1; i <= 3; ++i) {
        assert(assigned.get(i, value1) && original.get(i, value2) && "Get should succeed");
        assert(value1 == value2 && "Values should be the same in both lists");
    }

    std::cout << "Copy constructor and assignment operator tests passed!" << std::endl;
}

void testExtendedOperations() {
    std::cout << "Testing extended operations..." << std::endl;
    
    SeqList<int> list(10);
    for (int i = 1; i <= 5; ++i) {
        list.append(i);
    }

    // Test deleteMin
    int minValue;
    assert(list.deleteMin(minValue) && "DeleteMin should succeed");
    assert(minValue == 1 && "Minimum value should be 1");
    assert(list.size() == 4 && "List size should decrease after deleteMin");

    // Test reverse
    list.reverse();
    int value;
    assert(list.get(1, value) && value == 5 && "First element should be 5 after reverse");
    assert(list.get(4, value) && value == 2 && "Last element should be 2 after reverse");

    // Test clear
    list.clear();
    assert(list.empty() && "List should be empty after clear");
    assert(list.size() == 0 && "List size should be 0 after clear");

    std::cout << "Extended operations tests passed!" << std::endl;
}

void testBoundaryConditions() {
    std::cout << "Testing boundary conditions..." << std::endl;
    
    SeqList<int> list(3);
    
    // Test empty list operations
    int value;
    assert(!list.remove(1, value) && "Remove from empty list should fail");
    assert(!list.get(1, value) && "Get from empty list should fail");
    assert(!list.set(1, 100) && "Set in empty list should fail");
    assert(!list.deleteMin(value) && "DeleteMin from empty list should fail");

    // Test full list operations
    list.append(1);
    list.append(2);
    list.append(3);
    assert(!list.append(4) && "Append to full list should fail");
    assert(!list.insert(2, 4) && "Insert to full list should fail");

    // Test invalid indices
    assert(!list.get(0, value) && "Get with index 0 should fail");
    assert(!list.get(4, value) && "Get with index > size should fail");
    assert(!list.set(0, 100) && "Set with index 0 should fail");
    assert(!list.set(4, 100) && "Set with index > size should fail");
    assert(!list.remove(0, value) && "Remove with index 0 should fail");
    assert(!list.remove(4, value) && "Remove with index > size should fail");

    std::cout << "Boundary conditions tests passed!" << std::endl;
}

int main() {
    try {
        testBasicOperations();
        testStringList();
        testCopyAndAssignment();
        testExtendedOperations();
        testBoundaryConditions();
        
        std::cout << "\nAll tests passed successfully!" << std::endl;
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Test failed with exception: " << e.what() << std::endl;
        return 1;
    }
}
