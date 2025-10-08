#include "queue.h"
#include <iostream>
using namespace std;

// Adding an element to the queue
//@param The value to be enqueued into the queue
void DequeQueue::Enqueue(int value)
{
    data.push_back(value);
}

// Removing elements from the queue
//@throw Throws an exception if the stack is empty to prevent crash
void DequeQueue::Dequeue()
{
    if (IsEmpty())
        throw runtime_error("Error: Queue is empty. Cannot Dequeue");
    data.pop_front();
}

// Checking for an element on top of the queue
//@throw Throws an exception if the stack is empty to prevent crash
//@return Returns the front of the queue that was peeked
int DequeQueue::Peek() const
{
    if (IsEmpty())
        throw runtime_error("Error: Queue is empty. Cannot Peek");
    return data.front();
}

// Checks if the queue is empty or has elements
//@return Returns true or false on if the queue contains elements
bool DequeQueue::IsEmpty() const
{
    return data.empty();
}

// Checking how many elements are in the queue
//@return Statically cast to an int, the size of the queue
int DequeQueue::GetLength() const
{
    return static_cast<int>(data.size());
}


