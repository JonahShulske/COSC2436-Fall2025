#ifndef _STACK_H_
#define _STACK_H_

#include <deque>
#include <stdexcept>

// Class to construct a Stack using a Deque
template<typename T>
class DequeStack
{
    private:
        std::deque<T> data;
    public:
        void Push(const T& value) { data.push_back(value); }
        void Pop() { if (!data.empty()) data.pop_front(); }
        T Peek() const { return data.front(); }
        bool IsEmpty() const { return data.empty(); }
        int GetLength() const { return static_cast<int>(data.size()); }
};



#endif  _STACK_H_
