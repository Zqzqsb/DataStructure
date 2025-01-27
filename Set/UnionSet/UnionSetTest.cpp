#include <iostream>
#include <cassert>
#include <string>
#include "UnionSet.hpp"

void testBasicOperations() {
    std::cout << "Testing basic operations..." << std::endl;
    
    UnionSet<int> set(5);
    assert(set.getSize() == 5);
    assert(set.getSetCount() == 5);  // Initially all elements are in their own sets
    
    // Test setting and getting data
    for (int i = 0; i < 5; i++) {
        set.setData(i, i * 10);
        assert(set.getData(i) == i * 10);
        assert(set.getRank(i) == 1);  // Initial rank should be 1
    }
    
    std::cout << "Basic operations test passed!" << std::endl;
}

void testUnionFind() {
    std::cout << "Testing union and find operations..." << std::endl;
    
    UnionSet<int> set(6);
    
    // Initially all elements should be in different sets
    for (int i = 0; i < 6; i++) {
        for (int j = i + 1; j < 6; j++) {
            assert(!set.isConnected(i, j));
        }
    }
    
    // Test merging sets
    set.merge(0, 1);  // {0,1} {2} {3} {4} {5}
    assert(set.isConnected(0, 1));
    assert(set.getSetCount() == 5);
    
    set.merge(2, 3);  // {0,1} {2,3} {4} {5}
    assert(set.isConnected(2, 3));
    assert(set.getSetCount() == 4);
    
    set.merge(0, 2);  // {0,1,2,3} {4} {5}
    assert(set.isConnected(1, 3));  // Transitive connection
    assert(set.getSetCount() == 3);
    
    // Test rank changes
    assert(set.getRank(0) >= 1);
    assert(set.getRank(1) >= 1);
    
    std::cout << "Union and find operations test passed!" << std::endl;
}

void testCopyAndAssignment() {
    std::cout << "Testing copy constructor and assignment operator..." << std::endl;
    
    UnionSet<int> set1(4);
    for (int i = 0; i < 4; i++) {
        set1.setData(i, i);
    }
    set1.merge(0, 1);
    set1.merge(2, 3);
    
    // Test copy constructor
    UnionSet<int> set2(set1);
    assert(set2.getSize() == set1.getSize());
    assert(set2.getSetCount() == set1.getSetCount());
    assert(set2.isConnected(0, 1));
    assert(set2.isConnected(2, 3));
    assert(!set2.isConnected(0, 2));
    
    // Test assignment operator
    UnionSet<int> set3(2);  // Different size
    set3 = set1;
    assert(set3.getSize() == set1.getSize());
    assert(set3.getSetCount() == set1.getSetCount());
    assert(set3.isConnected(0, 1));
    assert(set3.isConnected(2, 3));
    assert(!set3.isConnected(0, 2));
    
    std::cout << "Copy and assignment tests passed!" << std::endl;
}

void testEdgeCases() {
    std::cout << "Testing edge cases..." << std::endl;
    
    // Test invalid size
    try {
        UnionSet<int> set(0);
        assert(false);  // Should not reach here
    } catch (const std::invalid_argument& e) {
        // Expected exception
    }
    
    UnionSet<int> set(3);
    
    // Test out of range access
    try {
        set.find(-1);
        assert(false);  // Should not reach here
    } catch (const std::out_of_range& e) {
        // Expected exception
    }
    
    try {
        set.find(3);
        assert(false);  // Should not reach here
    } catch (const std::out_of_range& e) {
        // Expected exception
    }
    
    // Test getRank out of range
    try {
        set.getRank(-1);
        assert(false);
    } catch (const std::out_of_range& e) {
        // Expected exception
    }
    
    std::cout << "Edge cases test passed!" << std::endl;
}

void testWithCustomType() {
    std::cout << "Testing with custom type (string)..." << std::endl;
    
    UnionSet<std::string> set(4);
    
    // Set data
    set.setData(0, "Apple");
    set.setData(1, "Banana");
    set.setData(2, "Cherry");
    set.setData(3, "Date");
    
    // Test data retrieval
    assert(set.getData(0) == "Apple");
    assert(set.getData(1) == "Banana");
    
    // Test merging with string data
    set.merge(0, 1);
    set.merge(2, 3);
    
    assert(set.isConnected(0, 1));
    assert(set.isConnected(2, 3));
    assert(!set.isConnected(0, 2));
    
    std::cout << "Custom type test passed!" << std::endl;
}

int main() {
    std::cout << "Starting UnionSet tests..." << std::endl;
    
    testBasicOperations();
    testUnionFind();
    testCopyAndAssignment();
    testEdgeCases();
    testWithCustomType();
    
    std::cout << "All tests passed successfully!" << std::endl;
    return 0;
}
