#ifndef HEAP_SIM_HPP
#define HEAP_SIM_HPP

#include <vector>
#include <stdexcept>
#include <algorithm>

template<typename T>
class HeapSim {
private:
    std::vector<T> h;        // 堆数组
    std::vector<int> ph;     // 位置到堆的映射
    std::vector<int> hp;     // 堆到位置的映射
    int cnt;                 // 当前堆大小

    // 交换堆中两个元素的位置
    void heap_swap(int a, int b) {
        std::swap(ph[hp[a]], ph[hp[b]]);
        std::swap(hp[a], hp[b]);
        std::swap(h[a], h[b]);
    }

    /**
     * @brief 向下调整函数，用于维护最小堆性质
     * @param u 需要向下调整的节点索引
     * @details
     * 1. 比较当前节点与其左右子节点的值
     * 2. 如果子节点中存在比当前节点小的值：
     *    - 找出左右子节点中较小的那个
     *    - 将当前节点与较小的子节点交换
     *    - 递归处理被交换的子节点
     * 3. 时间复杂度：O(log n)，其中n为堆的大小
     * @note
     * - 左子节点索引：u * 2
     * - 右子节点索引：u * 2 + 1
     * - 如果没有子节点比当前节点小，说明已满足堆性质，停止调整
     */
    void down(int u) {
        int t = u;
        if (u * 2 <= cnt && h[u * 2] < h[t]) t = u * 2;
        if (u * 2 + 1 <= cnt && h[u * 2 + 1] < h[t]) t = u * 2 + 1;
        if (u != t) {
            heap_swap(u, t);
            down(t);
        }
    }

    /**
     * @brief 向上调整函数，用于维护最小堆性质
     * @param u 需要向上调整的节点索引
     * @details
     * 1. 比较当前节点与其父节点的值
     * 2. 如果父节点的值大于当前节点：
     *    - 将当前节点与父节点交换
     *    - 继续向上比较和调整
     * 3. 时间复杂度：O(log n)，其中n为堆的大小
     * @note
     * - 父节点索引：u / 2
     * - 当到达根节点(u=1)或父节点值小于当前节点时停止调整
     * - 使用位运算 u >>= 1 代替 u = u / 2 以提高效率
     */
    void up(int u) {
        while (u / 2 && h[u] < h[u / 2]) {
            heap_swap(u, u / 2);
            u >>= 1;
        }
    }

public:
    // 构造函数
    explicit HeapSim(size_t capacity = 100010) : cnt(0) {
        h.resize(capacity);
        ph.resize(capacity);
        hp.resize(capacity);
    }

    // 插入元素
    bool push(int k, const T& x) {
        if (k < 0 || k >= static_cast<int>(ph.size())) {
            return false;
        }
        cnt++;
        ph[k] = cnt;
        hp[cnt] = k;
        h[cnt] = x;
        up(cnt);
        return true;
    }

    // 删除元素
    bool remove(int k) {
        if (k < 0 || k >= static_cast<int>(ph.size()) || ph[k] == 0) {
            return false;
        }
        int j = ph[k];
        heap_swap(j, cnt);
        cnt--;
        up(j);
        down(j);
        return true;
    }

    // 修改元素
    bool modify(int k, const T& x) {
        if (k < 0 || k >= static_cast<int>(ph.size()) || ph[k] == 0) {
            return false;
        }
        h[ph[k]] = x;
        up(ph[k]);
        down(ph[k]);
        return true;
    }

    // 获取最小值
    bool getMin(T& x) const {
        if (empty()) {
            return false;
        }
        x = h[1];
        return true;
    }

    // 判断堆是否为空
    bool empty() const {
        return cnt == 0;
    }

    // 获取堆的大小
    size_t size() const {
        return cnt;
    }

    // 获取堆的容量
    size_t capacity() const {
        return h.size() - 1;  // 索引0不使用
    }
};

#endif // HEAP_SIM_HPP
