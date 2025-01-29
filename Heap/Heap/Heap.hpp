#ifndef HEAP_HPP
#define HEAP_HPP

#include <vector>
#include <stdexcept>
#include <functional>

template<typename T, typename Compare = std::less<T>>
class Heap {
private:
    std::vector<T> data;     // 存储堆元素的数组
    Compare comp;            // 比较函数对象，默认为最小堆

    /**
     * @brief 获取父节点的索引
     * @param index 当前节点的索引
     * @return 父节点的索引
     */
    size_t parent(size_t index) const {
        return (index - 1) / 2;
    }

    /**
     * @brief 获取左子节点的索引
     * @param index 当前节点的索引
     * @return 左子节点的索引
     */
    size_t left_child(size_t index) const {
        return 2 * index + 1;
    }

    /**
     * @brief 获取右子节点的索引
     * @param index 当前节点的索引
     * @return 右子节点的索引
     */
    size_t right_child(size_t index) const {
        return 2 * index + 2;
    }

    /**
     * @brief 向上调整堆
     * @param index 需要向上调整的节点索引
     * @details
     * 1. 比较当前节点与其父节点
     * 2. 如果违反堆的性质，则交换它们
     * 3. 重复此过程直到满足堆的性质
     * @time O(log n)
     */
    void sift_up(size_t index) {
        while (index > 0 && comp(data[index], data[parent(index)])) {
            std::swap(data[index], data[parent(index)]);
            index = parent(index);
        }
    }

    /**
     * @brief 向下调整堆
     * @param index 需要向下调整的节点索引
     * @details
     * 1. 找出当前节点和其两个子节点中的最小值（最大堆则找最大值）
     * 2. 如果当前节点不是最小值，则与最小值交换
     * 3. 重复此过程直到满足堆的性质
     * @time O(log n)
     */
    void sift_down(size_t index) {
        size_t min_index = index;
        size_t l = left_child(index);
        size_t r = right_child(index);

        if (l < data.size() && comp(data[l], data[min_index])) {
            min_index = l;
        }
        if (r < data.size() && comp(data[r], data[min_index])) {
            min_index = r;
        }

        if (min_index != index) {
            std::swap(data[index], data[min_index]);
            sift_down(min_index);
        }
    }

public:
    /**
     * @brief 默认构造函数
     * @param compare 比较函数对象，默认使用std::less<T>
     */
    explicit Heap(const Compare& compare = Compare()) : comp(compare) {}

    /**
     * @brief 使用初始数据构造堆
     * @param init_data 初始数据
     * @param compare 比较函数对象
     * @time O(n)，其中n为初始数据的大小
     */
    Heap(const std::vector<T>& init_data, const Compare& compare = Compare())
        : data(init_data), comp(compare) {
        // 从最后一个非叶子节点开始向下调整
        for (int i = (data.size() - 2) / 2; i >= 0; --i) {
            sift_down(i);
        }
    }

    /**
     * @brief 插入新元素
     * @param value 要插入的值
     * @time O(log n)
     */
    void push(const T& value) {
        data.push_back(value);
        sift_up(data.size() - 1);
    }

    /**
     * @brief 删除堆顶元素
     * @throw std::runtime_error 如果堆为空
     * @time O(log n)
     */
    void pop() {
        if (empty()) {
            throw std::runtime_error("堆为空");
        }
        data[0] = data.back();
        data.pop_back();
        if (!empty()) {
            sift_down(0);
        }
    }

    /**
     * @brief 获取堆顶元素
     * @return 堆顶元素的常引用
     * @throw std::runtime_error 如果堆为空
     * @time O(1)
     */
    const T& top() const {
        if (empty()) {
            throw std::runtime_error("堆为空");
        }
        return data[0];
    }

    /**
     * @brief 检查堆是否为空
     * @return 如果堆为空返回true，否则返回false
     * @time O(1)
     */
    bool empty() const {
        return data.empty();
    }

    /**
     * @brief 获取堆中元素个数
     * @return 堆中元素的个数
     * @time O(1)
     */
    size_t size() const {
        return data.size();
    }

    /**
     * @brief 清空堆
     * @time O(1)
     */
    void clear() {
        data.clear();
    }

    /**
     * @brief 获取底层存储的常引用
     * @return 存储堆元素的vector的常引用
     * @note 主要用于测试
     */
    const std::vector<T>& get_data() const {
        return data;
    }
};

#endif // HEAP_HPP
