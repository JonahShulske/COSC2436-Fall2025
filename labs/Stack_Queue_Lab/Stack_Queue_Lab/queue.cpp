#include "queue.h"
#include <iostream>
using namespace std;

void DequeQueue::Enqueue(int value)
{
    data.push_back(value);
}

void DequeQueue::Dequeue()
{
    if (IsEmpty())
        throw runtime_error("Error: Queue is empty. Cannot Dequeue");
    data.pop_front();
}

int DequeQueue::Peek() const
{
    if (IsEmpty())
        throw runtime_error("Error: Queue is empty. Cannot Peek");
    return data.front();
}

bool DequeQueue::IsEmpty() const
{
    return data.empty();
}

int DequeQueue::GetLength() const
{
    return static_cast<int>(data.size());
}


