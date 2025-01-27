# 数据结构实现集合

这是一个使用C++实现的数据结构集合，是我学习数据结构和算法的过程中实现的仓库，每个实现都包含核心数据结构和相应的测试文件。

## 项目结构

```
├── BinTree（二叉树）
│   ├── AVL.cpp          # AVL平衡二叉树
│   ├── BinTree.cpp      # 基本二叉树
│   └── BST.cpp          # 二叉搜索树
├── Graphic（图）
│   ├── ListGD.cpp       # 邻接表实现的有向图
│   ├── ListUDG.cpp      # 邻接表实现的无向图
│   ├── MatrixDG.cpp     # 邻接矩阵实现的有向图
│   ├── MatrixUDG.cpp    # 邻接矩阵实现的无向图
│   └── Prim输入.png      # Prim算法输入示例
├── LinearList（线性表）
│   ├── LinkedListSimulatation.cpp  # 链表模拟实现
│   ├── SequentialList.cpp          # 顺序表
│   └── SingleLinkedList.cpp        # 单链表
├── Queue（队列）
│   ├── LinkedQueue.cpp   # 链式队列
│   └── SeqQueue.cpp      # 顺序队列
├── Set（集合）
│   └── UnionSet.cpp      # 并查集
├── Stack（栈）
│   └── SeqStack
│       ├── SeqStack.hpp       # 顺序栈实现
│       └── SeqStackTest.cpp   # 顺序栈测试
├── clean.sh              # 清理可执行文件的工具脚本
├── README.md             # 本文件
└── update_readme.sh      # 更新README结构的脚本
```

## 特性

- 基于模板的实现，支持多种数据类型
- 每个数据结构都经过完整测试
- 包含详细的单元测试用例
- 清晰的代码结构和注释
- 完整的文档说明

## 实现状态

| 数据结构 | 状态 | 说明 |
|---------|------|------|
| 栈 | ✅ | 顺序栈，支持基本操作 |
| 队列 | ✅ | 顺序队列和链式队列 |
| 线性表 | ✅ | 顺序表、单链表和模拟实现 |
| 二叉树 | ✅ | 包含AVL树和二叉搜索树 |
| 图 | ✅ | 邻接矩阵和邻接表表示 |
| 集合 | ✅ | 并查集（Union-Find）实现 |

## 使用方法

每个数据结构都有对应的测试文件，可以按以下方式编译和运行：

```bash
# 进入特定数据结构目录
cd Stack/SeqStack

# 编译测试文件
g++ -std=c++11 -o test SeqStackTest.cpp

# 运行测试
./test
```


## 开发环境

- 编译器：g++ (GCC) 
- C++标准：C++11
- 操作系统：Linux
- 构建工具：Make（可选）

## 项目维护

### 清理构建文件

使用提供的清理脚本删除所有生成的可执行文件：
```bash
./clean.sh
```

### 更新文档

更新README结构（在添加新文件后运行）：
```bash
./update_readme.sh
```

