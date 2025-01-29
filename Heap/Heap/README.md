# Heap - 通用堆实现

这是一个模板类实现的通用堆数据结构。支持最小堆和最大堆，可以处理任何可比较的数据类型。

## 特性

- 模板实现，支持任意可比较类型
- 支持自定义比较函数，可以实现最小堆或最大堆
- 支持高效的插入和删除操作
- 支持使用已有数据快速建堆
- 完整的异常处理和边界检查
- 所有操作的时间复杂度最优

## 主要接口

### 构造函数
```cpp
explicit Heap(const Compare& compare = Compare());  // 创建空堆
Heap(const std::vector<T>& init_data,              // 使用初始数据创建堆
     const Compare& compare = Compare());
```

### 基本操作
```cpp
void push(const T& value);      // 插入元素
void pop();                     // 删除堆顶元素
const T& top() const;           // 获取堆顶元素
bool empty() const;             // 检查堆是否为空
size_t size() const;           // 获取堆大小
void clear();                  // 清空堆
```

## 使用示例

### 1. 基本使用（最小堆）
```cpp
#include "Heap.hpp"

Heap<int> min_heap;
min_heap.push(5);
min_heap.push(3);
min_heap.push(7);

std::cout << min_heap.top();  // 输出：3
min_heap.pop();
std::cout << min_heap.top();  // 输出：5
```

### 2. 创建最大堆
```cpp
Heap<int, std::greater<int>> max_heap;
max_heap.push(5);
max_heap.push(3);
max_heap.push(7);

std::cout << max_heap.top();  // 输出：7
```

### 3. 使用初始数据建堆
```cpp
std::vector<int> data = {4, 1, 3, 2, 16, 9, 10, 14, 8, 7};
Heap<int> heap(data);
std::cout << heap.top();  // 输出：1
```

### 4. 自定义类型
```cpp
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
std::cout << heap.top().name;  // 输出：Bob（最小年龄）
```

## 实现细节

### 存储结构
- 使用 std::vector 作为底层存储
- 对于索引为 i 的节点：
  - 父节点索引：(i-1)/2
  - 左子节点索引：2*i + 1
  - 右子节点索引：2*i + 2

### 主要算法

1. **向上调整（sift_up）**
   - 新元素插入到数组末尾
   - 与父节点比较并交换，直到满足堆的性质
   - 时间复杂度：O(log n)

2. **向下调整（sift_down）**
   - 删除堆顶后，将最后一个元素移到堆顶
   - 与子节点中的最小值比较并交换，直到满足堆的性质
   - 时间复杂度：O(log n)

3. **建堆（heapify）**
   - 从最后一个非叶子节点开始向下调整
   - 时间复杂度：O(n)

## 性能分析

- 插入（push）：O(log n)
- 删除堆顶（pop）：O(log n)
- 获取堆顶（top）：O(1)
- 建堆（heapify）：O(n)
- 空间复杂度：O(n)

## 应用场景

1. 优先队列实现
2. 堆排序
3. 任务调度
4. 事件处理
5. Top-K 问题

## 注意事项

1. 使用自定义类型时需要实现比较运算符或提供比较函数
2. 空堆操作会抛出异常
3. 建堆时会修改原始数据的顺序
4. 默认为最小堆，需要最大堆时使用 std::greater 作为比较函数
