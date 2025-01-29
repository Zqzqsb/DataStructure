# HeapSim - 索引最小堆实现

HeapSim 是一个模板类实现的索引最小堆数据结构。它支持通过唯一的键来访问、修改和删除堆中的元素，同时保持堆的性质。

## 特性

- 模板实现，支持任何可比较的数据类型
- 支持通过唯一键快速访问和修改元素
- 所有操作（插入、删除、修改）的时间复杂度均为 O(log n)
- 获取最小元素的时间复杂度为 O(1)
- 提供完整的错误检查和安全访问机制

## 主要接口

### 构造函数
```cpp
explicit HeapSim(size_t capacity = 100010);
```
- 创建一个新的堆，可以指定容量，默认为100010

### 基本操作
```cpp
bool push(int k, const T& x);      // 插入键值为k的元素x
bool remove(int k);                // 删除键值为k的元素
bool modify(int k, const T& x);    // 修改键值为k的元素值为x
bool getMin(T& x) const;          // 获取最小值
bool empty() const;               // 判断堆是否为空
size_t size() const;             // 获取堆中元素个数
size_t capacity() const;         // 获取堆的容量
```

## 使用示例

```cpp
#include "HeapSim.hpp"

int main() {
    HeapSim<int> heap;
    
    // 插入元素
    heap.push(1, 5);  // 键值为1，元素值为5
    heap.push(2, 3);  // 键值为2，元素值为3
    
    // 修改元素
    heap.modify(1, 2);  // 将键值为1的元素值修改为2
    
    // 获取最小值
    int min_value;
    if (heap.getMin(min_value)) {
        std::cout << "最小值: " << min_value << std::endl;
    }
    
    // 删除元素
    heap.remove(2);  // 删除键值为2的元素
    
    return 0;
}
```

## 实现细节

该堆的实现使用了三个数组：
- `h`: 存储实际的元素值
- `ph`: 存储位置到堆的映射（position to heap）
- `hp`: 存储堆到位置的映射（heap to position）

这种实现方式使得我们可以在保持堆性质的同时，通过键值快速访问和修改元素。

## 编译和测试

编译测试程序：
```bash
g++ -std=c++11 HeapSimTest.cpp -o heap_test
```

运行测试：
```bash
./heap_test
```

## 注意事项

1. 键值必须是非负整数，且小于堆的容量
2. 不要使用已经存在的键值重复插入元素
3. 删除或修改不存在的键值将返回false
4. 堆是从索引1开始的，索引0不使用
