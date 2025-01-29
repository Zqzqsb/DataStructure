#include <iostream>
#include <cassert>
#include <string>
#include "HeapSim.hpp"

void testEmptyHeap() {
    std::cout << "测试空堆..." << std::endl;
    HeapSim<int> heap;
    assert(heap.empty() == true);
    assert(heap.size() == 0);
    
    int value;
    assert(heap.getMin(value) == false);
    std::cout << "空堆测试通过！" << std::endl;
}

void testPushAndGetMin() {
    std::cout << "测试插入和获取最小值操作..." << std::endl;
    HeapSim<int> heap;
    
    // 测试插入
    assert(heap.push(1, 5) == true);
    assert(heap.push(2, 3) == true);
    assert(heap.push(3, 7) == true);
    assert(heap.push(4, 1) == true);
    assert(heap.size() == 4);
    
    // 测试获取最小值
    int value;
    assert(heap.getMin(value) == true);
    assert(value == 1);  // 最小值应该是1
    
    // 测试无效的键值
    assert(heap.push(-1, 10) == false);
    std::cout << "插入和获取最小值测试通过！" << std::endl;
}

void testModify() {
    std::cout << "测试修改操作..." << std::endl;
    HeapSim<int> heap;
    
    heap.push(1, 5);
    heap.push(2, 3);
    heap.push(3, 7);
    
    // 测试修改
    assert(heap.modify(2, 1) == true);  // 将键值2的元素修改为1
    
    int value;
    assert(heap.getMin(value) == true);
    assert(value == 1);
    
    // 测试无效的修改
    assert(heap.modify(10, 1) == false);
    std::cout << "修改操作测试通过！" << std::endl;
}

void testRemove() {
    std::cout << "测试删除操作..." << std::endl;
    HeapSim<int> heap;
    
    heap.push(1, 5);
    heap.push(2, 3);
    heap.push(3, 7);
    heap.push(4, 1);
    
    // 测试删除
    assert(heap.remove(4) == true);  // 删除键值为4的元素（值为1）
    
    int value;
    assert(heap.getMin(value) == true);
    assert(value == 3);  // 新的最小值应该是3
    
    // 测试无效的删除
    assert(heap.remove(10) == false);
    std::cout << "删除操作测试通过！" << std::endl;
}

void testDifferentTypes() {
    std::cout << "测试不同数据类型..." << std::endl;
    HeapSim<double> doubleHeap;
    
    assert(doubleHeap.push(1, 5.5) == true);
    assert(doubleHeap.push(2, 3.3) == true);
    assert(doubleHeap.push(3, 7.7) == true);
    
    double value;
    assert(doubleHeap.getMin(value) == true);
    assert(value == 3.3);
    std::cout << "不同数据类型测试通过！" << std::endl;
}

int main() {
    std::cout << "开始堆测试..." << std::endl;
    
    testEmptyHeap();
    testPushAndGetMin();
    testModify();
    testRemove();
    testDifferentTypes();
    
    std::cout << "所有测试通过！" << std::endl;
    return 0;
}
