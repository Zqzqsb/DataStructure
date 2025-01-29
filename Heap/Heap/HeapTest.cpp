#include <iostream>
#include <cassert>
#include <string>
#include <functional>
#include "Heap.hpp"

void testEmptyHeap() {
    std::cout << "测试空堆..." << std::endl;
    Heap<int> heap;
    
    assert(heap.empty() == true);
    assert(heap.size() == 0);
    
    try {
        heap.top();
        assert(false);  // 不应该到达这里
    } catch (const std::runtime_error& e) {
        // 期望抛出异常
    }
    
    try {
        heap.pop();
        assert(false);  // 不应该到达这里
    } catch (const std::runtime_error& e) {
        // 期望抛出异常
    }
    
    std::cout << "空堆测试通过！" << std::endl;
}

void testPushAndPop() {
    std::cout << "测试插入和删除操作..." << std::endl;
    Heap<int> min_heap;  // 最小堆
    
    // 测试插入
    min_heap.push(5);
    assert(min_heap.top() == 5);
    min_heap.push(3);
    assert(min_heap.top() == 3);
    min_heap.push(7);
    assert(min_heap.top() == 3);
    min_heap.push(1);
    assert(min_heap.top() == 1);
    
    // 测试删除
    min_heap.pop();
    assert(min_heap.top() == 3);
    min_heap.pop();
    assert(min_heap.top() == 5);
    min_heap.pop();
    assert(min_heap.top() == 7);
    
    std::cout << "插入和删除测试通过！" << std::endl;
}

void testMaxHeap() {
    std::cout << "测试最大堆..." << std::endl;
    Heap<int, std::greater<int>> max_heap;
    
    max_heap.push(5);
    max_heap.push(3);
    max_heap.push(7);
    max_heap.push(1);
    
    assert(max_heap.top() == 7);
    max_heap.pop();
    assert(max_heap.top() == 5);
    max_heap.pop();
    assert(max_heap.top() == 3);
    
    std::cout << "最大堆测试通过！" << std::endl;
}

void testHeapify() {
    std::cout << "测试堆化..." << std::endl;
    std::vector<int> data = {4, 1, 3, 2, 16, 9, 10, 14, 8, 7};
    Heap<int> heap(data);
    
    // 验证最小堆性质
    std::vector<int> expected = {1, 2, 3, 4, 7, 9, 10, 14, 8, 16};
    assert(heap.get_data() == expected);
    
    // 验证删除操作后仍保持堆的性质
    heap.pop();
    assert(heap.top() == 2);
    
    std::cout << "堆化测试通过！" << std::endl;
}

void testCustomType() {
    std::cout << "测试自定义类型..." << std::endl;
    
    struct Person {
        std::string name;
        int age;
        
        bool operator<(const Person& other) const {
            return age < other.age;
        }
    };
    
    Heap<Person> heap;
    heap.push({"Alice", 25});
    heap.push({"Bob", 20});
    heap.push({"Charlie", 30});
    
    assert(heap.top().name == "Bob");  // 最小年龄
    heap.pop();
    assert(heap.top().name == "Alice");
    
    std::cout << "自定义类型测试通过！" << std::endl;
}

void testClear() {
    std::cout << "测试清空操作..." << std::endl;
    Heap<int> heap;
    
    heap.push(1);
    heap.push(2);
    heap.push(3);
    
    assert(!heap.empty());
    heap.clear();
    assert(heap.empty());
    assert(heap.size() == 0);
    
    // 清空后可以继续使用
    heap.push(4);
    assert(heap.top() == 4);
    
    std::cout << "清空操作测试通过！" << std::endl;
}

int main() {
    std::cout << "开始堆测试..." << std::endl;
    
    testEmptyHeap();
    testPushAndPop();
    testMaxHeap();
    testHeapify();
    testCustomType();
    testClear();
    
    std::cout << "所有测试通过！" << std::endl;
    return 0;
}
