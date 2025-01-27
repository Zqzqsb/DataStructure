#include "SingleLinkedList.hpp"
#include <cassert>
#include <string>
#include <vector>

void testBasicOperations() {
    std::cout << "Testing basic operations..." << std::endl;
    
    SingleLinkedList<int> list;
    assert(list.empty() && "New list should be empty");
    assert(list.size() == 0 && "New list size should be 0");

    // Test append
    list.append(1);
    list.append(2);
    list.append(3);
    assert(list.size() == 3 && "List size should be 3 after appending");

    // Test insert
    assert(list.insert(2, 4) && "Insert should succeed");
    int value;
    assert(list.get(2, value) && value == 4 && "Get should return inserted value");

    // Test remove
    assert(list.remove(2, value) && "Remove should succeed");
    assert(value == 4 && "Removed value should be 4");
    assert(list.size() == 3 && "List size should be 3 after remove");

    // Test locate
    assert(list.locate(2) == 2 && "Element 2 should be at position 2");

    std::cout << "Basic operations tests passed!" << std::endl;
}

void testStringList() {
    std::cout << "Testing string list..." << std::endl;
    
    SingleLinkedList<std::string> list;
    
    // Test append
    list.append("Hello");
    list.append("World");
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

void testVectorConstruction() {
    std::cout << "Testing vector construction..." << std::endl;
    
    std::vector<int> v = {1, 2, 3, 4, 5};
    
    // Test reverse order (head insertion)
    SingleLinkedList<int> list1(v, true);
    int value;
    assert(list1.get(1, value) && value == 5 && "First element should be 5");
    assert(list1.get(5, value) && value == 1 && "Last element should be 1");

    // Test forward order (tail insertion)
    SingleLinkedList<int> list2(v, false);
    assert(list2.get(1, value) && value == 1 && "First element should be 1");
    assert(list2.get(5, value) && value == 5 && "Last element should be 5");

    std::cout << "Vector construction tests passed!" << std::endl;
}

void testCopyAndAssignment() {
    std::cout << "Testing copy constructor and assignment operator..." << std::endl;
    
    SingleLinkedList<int> original;
    for (int i = 1; i <= 3; ++i) {
        original.append(i);
    }
    
    // Test copy constructor
    SingleLinkedList<int> copied(original);
    assert(copied.size() == original.size() && "Copied list should have same size");
    
    int value1, value2;
    for (int i = 1; i <= 3; ++i) {
        assert(copied.get(i, value1) && original.get(i, value2) && "Get should succeed");
        assert(value1 == value2 && "Values should be the same in both lists");
    }

    // Test assignment operator
    SingleLinkedList<int> assigned;
    assigned = original;
    assert(assigned.size() == original.size() && "Assigned list should have same size");
    
    for (int i = 1; i <= 3; ++i) {
        assert(assigned.get(i, value1) && original.get(i, value2) && "Get should succeed");
        assert(value1 == value2 && "Values should be the same in both lists");
    }

    std::cout << "Copy constructor and assignment operator tests passed!" << std::endl;
}

void testReverse() {
    std::cout << "Testing reverse operation..." << std::endl;
    
    SingleLinkedList<int> list;
    for (int i = 1; i <= 5; ++i) {
        list.append(i);
    }

    list.reverse();
    
    int value;
    assert(list.get(1, value) && value == 5 && "First element should be 5 after reverse");
    assert(list.get(5, value) && value == 1 && "Last element should be 1 after reverse");

    // Test reverse with single element
    SingleLinkedList<int> singleList;
    singleList.append(1);
    singleList.reverse();
    assert(singleList.get(1, value) && value == 1 && "Single element list should remain unchanged after reverse");

    // Test reverse with empty list
    SingleLinkedList<int> emptyList;
    emptyList.reverse();
    assert(emptyList.empty() && "Empty list should remain empty after reverse");

    std::cout << "Reverse operation tests passed!" << std::endl;
}

void testBoundaryConditions() {
    std::cout << "Testing boundary conditions..." << std::endl;
    
    SingleLinkedList<int> list;
    
    // Test empty list operations
    int value;
    assert(!list.remove(1, value) && "Remove from empty list should fail");
    assert(!list.get(1, value) && "Get from empty list should fail");
    assert(!list.set(1, 100) && "Set in empty list should fail");
    assert(list.locate(100) == 0 && "Locate in empty list should return 0");

    // Test invalid indices
    list.append(1);
    assert(!list.get(0, value) && "Get with index 0 should fail");
    assert(!list.get(2, value) && "Get with index > size should fail");
    assert(!list.set(0, 100) && "Set with index 0 should fail");
    assert(!list.set(2, 100) && "Set with index > size should fail");
    assert(!list.remove(0, value) && "Remove with index 0 should fail");
    assert(!list.remove(2, value) && "Remove with index > size should fail");
    assert(!list.insert(0, 100) && "Insert at index 0 should fail");
    assert(!list.insert(3, 100) && "Insert at index > size+1 should fail");

    std::cout << "Boundary conditions tests passed!" << std::endl;
}

int main() {
    try {
        testBasicOperations();
        testStringList();
        testVectorConstruction();
        testCopyAndAssignment();
        testReverse();
        testBoundaryConditions();
        
        std::cout << "\nAll tests passed successfully!" << std::endl;
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Test failed with exception: " << e.what() << std::endl;
        return 1;
    }
}
