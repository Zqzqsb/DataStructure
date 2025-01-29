#ifndef TRIE_HPP
#define TRIE_HPP

#include <iostream>
#include <unordered_map>
#include <string>

/**
 * @brief Trie树节点结构
 * @details 
 * 每个节点包含：
 * 1. 指向子节点的哈希映射表
 * 2. 以该节点结尾的字符串计数
 */
struct TreeNode {
    std::unordered_map<char, TreeNode*> children; // 子节点映射表
    int count;                                    // 字符串计数
    
    TreeNode() : count(0) {}                      // 构造函数初始化计数为0
};

/**
 * @brief Trie树（前缀树/字典树）的实现
 * @details
 * Trie是一种用于高效存储和查询字符串的树形数据结构。
 * 主要特点：
 * 1. 利用字符串的公共前缀来节省存储空间
 * 2. 支持快速查询和前缀匹配
 * 3. 支持重复字符串的计数
 */
class Trie {
private:
    TreeNode* root;  // 根节点指针

public:
    /**
     * @brief 构造函数
     * @details 创建Trie树的根节点
     */
    Trie() {
        root = new TreeNode();
    }

    /**
     * @brief 插入字符串
     * @param str 待插入的字符串
     * @details
     * 1. 从根节点开始，逐个处理字符串中的字符
     * 2. 对每个字符，如果对应的子节点不存在，则创建新节点
     * 3. 在字符串的最后一个字符对应的节点增加计数
     * @time O(m)，m为字符串长度
     * @space O(m)，最坏情况下需要创建m个新节点
     */
    void insert(const std::string& str) {
        TreeNode* node = root;
        for (char c : str) {
            if (node->children.find(c) == node->children.end()) {
                node->children[c] = new TreeNode();
            }
            node = node->children[c];
        }
        node->count++;
    }

    /**
     * @brief 查询字符串出现次数
     * @param str 待查询的字符串
     * @return 字符串出现的次数
     * @details
     * 1. 从根节点开始，逐个匹配字符
     * 2. 如果任何字符未找到匹配的子节点，返回0
     * 3. 返回最后一个节点的计数值
     * @time O(m)，m为字符串长度
     */
    int query(const std::string& str) {
        TreeNode* node = root;
        for (char c : str) {
            if (node->children.find(c) == node->children.end()) {
                return 0;
            }
            node = node->children[c];
        }
        return node->count;
    }

    /**
     * @brief 析构函数
     * @details 递归删除所有节点，防止内存泄漏
     */
    ~Trie() {
        destroy(root);
    }

private:
    /**
     * @brief 递归删除节点
     * @param node 当前要删除的节点
     * @details
     * 1. 递归删除所有子节点
     * 2. 删除当前节点
     */
    void destroy(TreeNode* node) {
        for (auto& child : node->children) {
            destroy(child.second);
        }
        delete node;
    }
};

#endif // TRIE_HPP