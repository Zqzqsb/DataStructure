#include <iostream>
#include <cassert>
#include <string>
#include "Trie.hpp"

void testEmptyTrie() {
    std::cout << "测试空Trie..." << std::endl;
    Trie trie;
    
    // 测试空字符串
    assert(trie.query("") == 0);
    // 测试不存在的字符串
    assert(trie.query("hello") == 0);
    
    std::cout << "空Trie测试通过！" << std::endl;
}

void testInsertAndQuery() {
    std::cout << "测试插入和查询操作..." << std::endl;
    Trie trie;
    
    // 测试基本插入
    trie.insert("hello");
    assert(trie.query("hello") == 1);
    
    // 测试重复插入
    trie.insert("hello");
    assert(trie.query("hello") == 2);
    
    // 测试不同字符串
    trie.insert("world");
    assert(trie.query("world") == 1);
    assert(trie.query("hello") == 2);
    
    // 测试前缀
    assert(trie.query("hel") == 0);  // 前缀不算完整匹配
    assert(trie.query("worl") == 0);
    
    std::cout << "插入和查询测试通过！" << std::endl;
}

void testSpecialCases() {
    std::cout << "测试特殊情况..." << std::endl;
    Trie trie;
    
    // 测试空字符串
    trie.insert("");
    assert(trie.query("") == 1);
    
    // 测试包含特殊字符的字符串
    trie.insert("hello!");
    trie.insert("hello?");
    assert(trie.query("hello!") == 1);
    assert(trie.query("hello?") == 1);
    
    // 测试长字符串
    std::string longStr(1000, 'a');  // 1000个'a'
    trie.insert(longStr);
    assert(trie.query(longStr) == 1);
    
    std::cout << "特殊情况测试通过！" << std::endl;
}

void testCaseSensitivity() {
    std::cout << "测试大小写敏感性..." << std::endl;
    Trie trie;
    
    trie.insert("Hello");
    trie.insert("hello");
    trie.insert("HELLO");
    
    assert(trie.query("Hello") == 1);
    assert(trie.query("hello") == 1);
    assert(trie.query("HELLO") == 1);
    
    std::cout << "大小写敏感性测试通过！" << std::endl;
}

void testChineseCharacters() {
    std::cout << "测试中文字符..." << std::endl;
    Trie trie;
    
    trie.insert("你好");
    trie.insert("世界");
    trie.insert("你好世界");
    
    assert(trie.query("你好") == 1);
    assert(trie.query("世界") == 1);
    assert(trie.query("你好世界") == 1);
    assert(trie.query("你") == 0);
    
    std::cout << "中文字符测试通过！" << std::endl;
}

int main() {
    std::cout << "开始Trie树测试..." << std::endl;
    
    testEmptyTrie();
    testInsertAndQuery();
    testSpecialCases();
    testCaseSensitivity();
    testChineseCharacters();
    
    std::cout << "所有测试通过！" << std::endl;
    return 0;
}
