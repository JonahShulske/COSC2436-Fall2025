#include "stack.h"
#include "queue.h"
#include <iostream>
using namespace std;

// Printing the elements in the Stack to show what it contains
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

// Printing the elements in the queue to show what it contains
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

    // Adding elements to Stack and Queue
    std::cout << "Testing Stack Operations:" << std::endl;
    for (int index = 1; index <= 5; ++index)
    {
        stack.Push(index);
        queue.Enqueue(index);
    }

    // Printing elements
    PrintStack(stack);
    cout << endl;
    PrintQueue(queue);
    cout << endl;

    // Checking and printing to user both whether the Stack/Queue is empty and its length at runtime
    std::cout << "Is the Stack empty? " << (stack.IsEmpty() ? "Yes" : "No") << std::endl;
    std::cout << "Stack Length: " << stack.GetLength() << endl;
    std::cout << "Is the Queue empty? " << (queue.IsEmpty() ? "Yes" : "No") << std::endl;
    std::cout << "Queue Length: " << queue.GetLength() << "\n" << endl;

    // Popping and Dequeueing Elements
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

    // Checking to prevent a crash if the stack is popped while empty
    try
    {
        stack.Pop();
        std::cout << "Pop on Empty didn't return an error" << endl;
    }
    catch (const exception& ex)
    {
        std::cout << "Exception caught error on Stack Pop" << endl;
    }

    // Checking to prevent a crash if the queue is dequeued while empty
    try
    {
        queue.Dequeue();
        std::cout << "Dequeue on Empty didn't return an error" << endl;
    }
    catch (const exception& ex)
    {
        std::cout << "Exception caught error on Queue Dequeue" << endl;
    }

    return 0;
}