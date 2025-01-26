# Sequential Stack Implementation

A template-based sequential stack implementation in C++ that provides basic stack operations with dynamic memory allocation.

## Features

- Template-based implementation supporting any data type
- Dynamic memory allocation with customizable initial size
- Basic stack operations (push, pop, peek)
- Boundary checking for stack operations
- Memory management with proper destructor

## API Reference

### Constructor
```cpp
SeqStack(int size = 10)
```
- Creates a new stack with specified capacity (default: 10)
- Parameters:
  - `size`: Initial capacity of the stack

### Destructor
```cpp
~SeqStack()
```
- Automatically frees allocated memory when stack goes out of scope

### Operations

#### empty()
```cpp
bool empty()
```
- Checks if the stack is empty
- Returns: `true` if stack is empty, `false` otherwise

#### push()
```cpp
bool push(const T& x)
```
- Pushes an element onto the top of the stack
- Parameters:
  - `x`: Element to push (passed by const reference)
- Returns: `true` if successful, `false` if stack is full

#### pop()
```cpp
bool pop(T& e)
```
- Removes and returns the top element from the stack
- Parameters:
  - `e`: Reference to store the popped element
- Returns: `true` if successful, `false` if stack is empty

#### getTop()
```cpp
bool getTop(T& e)
```
- Returns the top element without removing it
- Parameters:
  - `e`: Reference to store the top element
- Returns: `true` if successful, `false` if stack is empty

## Usage Example

```cpp
// Create a stack of integers with capacity 5
SeqStack<int> stack(5);

// Push elements
stack.push(1);
stack.push(2);
stack.push(3);

// Check top element
int top;
if (stack.getTop(top)) {
    std::cout << "Top element: " << top << std::endl;  // Output: 3
}

// Pop elements
int value;
while (stack.pop(value)) {
    std::cout << value << " ";  // Output: 3 2 1
}
```

## Implementation Details

- Uses dynamic array allocation for storage
- Maintains a top pointer to track the stack top
- Implements boundary checking for push and pop operations
- Template-based for type flexibility
- Time Complexity:
  - Push: O(1)
  - Pop: O(1)
  - Top: O(1)
  - Empty check: O(1)

## Testing

The implementation includes a comprehensive test file (`SeqStackTest.cpp`) that verifies:
- Basic stack operations
- Boundary conditions
- Memory management
- Template functionality with different data types

Run the tests using:
```bash
g++ -o test SeqStackTest.cpp && ./test
```
