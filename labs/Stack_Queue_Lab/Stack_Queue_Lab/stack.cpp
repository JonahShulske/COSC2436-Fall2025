#include "stack.h"
#include <iostream>
using namespace std;

// Adding elements into the stack
//@param Value to be pushed into the stack
void DequeStack::Push(int value)
{
    data.push_back(value);
}

// Popping to remove elements and return value
//@throw Throws an exception if the stack is empty to prevent crash
void DequeStack::Pop()
{
    if (IsEmpty())
        throw runtime_error("Error: Stack is empty. Cannot Pop");

    data.pop_back();
}

// Checking the top of the stack for an element
//@throw Throws an exception if the stack is empty to prevent crash
//@return The data that was peeked, but not removed from the stack
int DequeStack::Peek() const
{
    if (IsEmpty())
        throw runtime_error("Error: Stack is empty. Cannot Peek");
    return data.back();
}

// Checking if the stack has elements or not
//@return Whether the Stack is empty or not
bool DequeStack::IsEmpty() const
{
    return data.empty();
}

// Checking how many elements are in the stack
//@return Statically cast to an int, the size of the stack
int DequeStack::GetLength() const
{
    return static_cast<int>(data.size());
}

