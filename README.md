# DataStructure

This repository contains implementations of various data structures in C++. Each implementation includes both the core data structure and corresponding test files to verify functionality.

## Project Structure

```
├── BinTree
│   ├── AVL.cpp
│   ├── BinTree.cpp
│   └── BST.cpp
├── Graphic
│   ├── ListGD.cpp
│   ├── ListUDG.cpp
│   ├── MatrixDG.cpp
│   ├── MatrixUDG.cpp
│   └── Prim输入.png
├── LinearList
│   ├── LinkedListSimulatation.cpp
│   ├── SequentialList.cpp
│   └── SingleLinkedList.cpp
├── Queue
│   ├── LinkedQueue.cpp
│   └── SeqQueue.cpp
├── Set
│   └── UnionSet.cpp
├── Stack
│   └── SeqStack
│       ├── SeqStack.cpp
│       └── SeqStackTest.cpp
├── clean.sh                  # Utility script to remove executable files
├── README.md                 # This file
├── README.temp.md
└── update_readme.sh             # Script to update README structure
```


## Features

- Each data structure implementation is thoroughly tested
- Template-based implementations for type flexibility
- Comprehensive test cases included
- Clean and maintainable code structure

## Usage

1. Navigate to the specific data structure directory
2. Compile the implementation with its test file:
   ```bash
   g++ -o test StructureNameTest.cpp
   ```
3. Run the test:
   ```bash
   ./test
   ```

## Cleaning Build Files

To remove all generated executable files, run:
```bash
./clean.sh
```

## Implementation Status

- [x] Stack (Sequential)
- [x] Queue (Sequential and Linked)
- [x] Linear Lists
- [x] Binary Trees (including AVL and BST)
- [x] Graphs (Matrix and List representations)
- [x] Sets (Union-Find)
