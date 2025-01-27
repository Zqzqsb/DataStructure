#include "LinkedListSim.hpp"
#include <cassert>
#include <string>

void testBasicOperations() {
    std::cout << "Testing basic operations..." << std::endl;
    
    LinkedListSim<int> list;
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
    
    LinkedListSim<std::string> list;
    
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

void testHeadInsertion() {
    std::cout << "Testing head insertion..." << std::endl;
    
    LinkedListSim<int> list;
    
    // Insert elements at head
    list.insertHead(3);
    list.insertHead(2);
    list.insertHead(1);
    
    // Verify order
    int value;
    assert(list.get(1, value) && value == 1 && "First element should be 1");
    assert(list.get(2, value) && value == 2 && "Second element should be 2");
    assert(list.get(3, value) && value == 3 && "Third element should be 3");

    std::cout << "Head insertion tests passed!" << std::endl;
}

void testBoundaryConditions() {
    std::cout << "Testing boundary conditions..." << std::endl;
    
    LinkedListSim<int> list;
    
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

void testClear() {
    std::cout << "Testing clear operation..." << std::endl;
    
    LinkedListSim<int> list;
    
    // Add some elements
    list.append(1);
    list.append(2);
    list.append(3);
    assert(list.size() == 3 && "List size should be 3");

    // Clear the list
    list.clear();
    assert(list.empty() && "List should be empty after clear");
    assert(list.size() == 0 && "List size should be 0 after clear");

    // Add elements after clear
    list.append(4);
    list.append(5);
    assert(list.size() == 2 && "List size should be 2 after adding elements post-clear");
    
    int value;
    assert(list.get(1, value) && value == 4 && "First element should be 4");
    assert(list.get(2, value) && value == 5 && "Second element should be 5");

    std::cout << "Clear operation tests passed!" << std::endl;
}

void testCapacity() {
    std::cout << "Testing capacity limits..." << std::endl;
    
    LinkedListSim<int, 5> smallList;  // List with capacity of 5
    
    // Fill the list
    for (int i = 1; i <= 4; ++i) {
        assert(smallList.append(i) && "Append should succeed within capacity");
    }
    
    assert(!smallList.full() && "List should not be full with 4 elements");
    assert(smallList.append(5) && "Append should succeed at capacity limit");
    assert(smallList.full() && "List should be full with 5 elements");
    
    // Try to exceed capacity
    try {
        smallList.append(6);
        assert(false && "Append should throw when exceeding capacity");
    } catch (const std::runtime_error&) {
        // Expected exception
    }

    std::cout << "Capacity limits tests passed!" << std::endl;
}

int main() {
    try {
        testBasicOperations();
        testStringList();
        testHeadInsertion();
        testBoundaryConditions();
        testClear();
        testCapacity();
        
        std::cout << "\nAll tests passed successfully!" << std::endl;
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Test failed with exception: " << e.what() << std::endl;
        return 1;
    }
}
