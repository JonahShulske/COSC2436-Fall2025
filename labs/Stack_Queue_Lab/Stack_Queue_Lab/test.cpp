#include "stack.h"
#include "queue.h"
#include <iostream>
using namespace std;

void PrintStack(DequeStack& stack)
{
    DequeStack tempStack;
    while (!stack.IsEmpty())
    {
        int value = stack.Peek();
        std::cout << value << " ";
        tempStack.Push(value);
        stack.Pop();
    }

    while (!tempStack.IsEmpty())
    {
        stack.Push(tempStack.Peek());
        tempStack.Pop();
    }
    cout << endl;
}

void PrintQueue(DequeQueue& queue)
{
    DequeQueue tempQueue;
    while (!queue.IsEmpty())
    {
        int value = queue.Peek();
        std::cout << value << " ";
        tempQueue.Enqueue(value);
        queue.Dequeue();
    }

    while (!tempQueue.IsEmpty())
    {
        queue.Enqueue(tempQueue.Peek());
        tempQueue.Dequeue();
    }
    cout << endl;
}

int main()
{
    DequeStack stack;
    DequeQueue queue;

    std::cout << "Testing Stack Operations:" << std::endl;
    for (int index = 1; index <= 5; ++index)
    {
        stack.Push(index);
        queue.Enqueue(index);
    }

    PrintStack(stack);
    PrintQueue(queue);

    std::cout << "Is the Stack empty? " << (stack.IsEmpty() ? "Yes" : "No") << std::endl;
    std::cout << "Stack Length: " << stack.GetLength() << endl;
    std::cout << "Is the Queue empty? " << (queue.IsEmpty() ? "Yes" : "No") << std::endl;
    std::cout << "Queue Length: " << queue.GetLength() << endl;

    std::cout << "Stack and Queue Value Removals (Popping and Dequeuing):" << std::endl;

    while (!stack.IsEmpty() || !queue.IsEmpty())
    {
        if (!stack.IsEmpty())
        {
            stack.Pop();
            PrintStack(stack);
        }

        if (!queue.IsEmpty())
        {
            queue.Dequeue();
            PrintQueue(queue);
        }
    }

    try
    {

    }

    return 0;
}