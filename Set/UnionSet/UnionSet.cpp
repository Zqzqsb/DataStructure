#include <iostream>
#include <vector>
#include <stdexcept>

template<typename T>
class UnionSet {
private:
    std::vector<int> parent;  // Parent array
    std::vector<int> rank;    // Rank array for union by rank
    std::vector<T> data;      // Data array
    int size;                 // Size of the set

public:
    // Constructor
    UnionSet(int n) {
        if (n <= 0) {
            throw std::invalid_argument("Size must be positive");
        }
        size = n;
        parent.resize(n);
        rank.resize(n, 1);
        data.resize(n);
        
        // Initialize each element as its own set
        for (int i = 0; i < n; ++i) {
            parent[i] = i;
        }
    }

    // Initialize element data
    void setData(int index, const T& value) {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Index out of range");
        }
        data[index] = value;
    }

    // Get element data
    T getData(int index) const {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    // Find operation with path compression
    int find(int x) {
        if (x < 0 || x >= size) {
            throw std::out_of_range("Index out of range");
        }
        return x == parent[x] ? x : (parent[x] = find(parent[x]));
    }

    // Union operation with rank
    void merge(int x, int y) {
        if (x < 0 || x >= size || y < 0 || y >= size) {
            throw std::out_of_range("Index out of range");
        }
        
        int rootX = find(x);
        int rootY = find(y);

        if (rootX == rootY) return;  // Already in same set

        // Union by rank
        if (rank[rootX] <= rank[rootY]) {
            parent[rootX] = rootY;
            if (rank[rootX] == rank[rootY]) {
                rank[rootY]++;
            }
        } else {
            parent[rootY] = rootX;
        }
    }

    // Check if two elements are in the same set
    bool isConnected(int x, int y) {
        if (x < 0 || x >= size || y < 0 || y >= size) {
            throw std::out_of_range("Index out of range");
        }
        return find(x) == find(y);
    }

    // Get the size of the set
    int getSize() const {
        return size;
    }

    // Get number of distinct sets
    int getSetCount() {
        int count = 0;
        for (int i = 0; i < size; i++) {
            if (parent[i] == i) {
                count++;
            }
        }
        return count;
    }
};
