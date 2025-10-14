#ifndef _QUEUE_H_
#define _QUEUE_H_

#include <deque>
#include <stdexcept>

// Class to construct a Queue using a Deque
template<typename T>
class DequeQueue
{
    private:
        std::deque<T> data;
    public:
        void Enqueue(const T& value) { data.push_back(value); }
        void Dequeue() { if (!data.empty()) data.pop_front(); }
        T Peek() const { return data.front(); }
        bool IsEmpty() const { return data.empty(); }
        int GetLength() const { return static_cast<int>(data.size()); }
};

#endif _QUEUE_H_
