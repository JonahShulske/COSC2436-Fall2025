#ifndef _STACK_H_
#define _STACK_H_

#include <deque>
#include <stdexcept>

// Class to construct a Stack using a Deque
class DequeStack
{
    private:
        std::deque<int> data;
    public:
        void Push(int value);
        void Pop();
        int Peek() const;
        bool IsEmpty() const;
        int GetLength() const;
};



#endif  _STACK_H_
