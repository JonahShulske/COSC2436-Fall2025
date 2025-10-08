#include "stack.h"
#include <iostream>
using namespace std;

void DequeStack::Push(int value)
{
    data.push_back(value);
}

void DequeStack::Pop()
{
    if (IsEmpty())
        throw runtime_error("Error: Stack is empty. Cannot Pop");

    data.pop_back();
}

int DequeStack::Peek() const
{
    if (IsEmpty())
        throw runtime_error("Error: Stack is empty. Cannot Peek");
    return data.back();
}

bool DequeStack::IsEmpty() const
{
    return data.empty();
}

int DequeStack::GetLength() const
{
    return static_cast<int>(data.size());
}

