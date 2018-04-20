#if !defined (STACK_H)
#define STACK_H

#include <cstddef>

template <typename T>
class StackImpl {
protected:
    StackImpl(size_t size = 0);
    ~StackImpl();
    void Swap(StackImpl& other) throw();
    
    T* v_;
    size_t vsize_;
    size_t vused_;   
private:
    StackImpl(const StackImpl&);
    StackImpl& operator=(const StackImpl&);
};

template <typename T>
class Stack : private StackImpl<T> {
    using StackImpl<T>::v_;
    using StackImpl<T>::vsize_;
    using StackImpl<T>::vused_;
    using StackImpl<T>::Swap;
public:
    class Underflow {}; // exception class

    Stack(size_t size = 0);
    ~Stack();

    Stack(const Stack&);
    Stack& operator=(const Stack&);

    size_t   Count() const;
    void     Push(const T&);
    T&       Top();   // if empty, throws exception
    const T& Top() const;
    void     Pop();   // if empty, throws exception
};

#include "stack.cpp"
#endif
