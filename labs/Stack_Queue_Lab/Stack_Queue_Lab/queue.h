#ifndef _QUEUE_H_
#define _QUEUE_H_

#include <deque>
#include <stdexcept>

// Class to construct a Queue using a Deque
class DequeQueue
{
    private:
        std::deque<int> data;
    public:
        void Enqueue(int value);
        void Dequeue();
        int Peek() const;
        bool IsEmpty() const;
        int GetLength() const;
};

#endif _QUEUE_H_
