#if !defined (STACK_CPP)
#define STACK_CPP

#include "stack.h"

#include <utility>
#include <new>

namespace { // helpers

template <typename T, typename ValT>
void construct(T* p, const ValT& val)
{
    new (p) T(val);
}

template <typename T>
void destroy(T* p)
{
    p->~T();
}

template <typename FwdIt>
void destroy(FwdIt first, FwdIt last)
{
    while (first != last) {
        destroy(&*first);
        ++first;
    }
}

}

// StackImpl

template <typename T>
StackImpl<T>::StackImpl(size_t size)
    : v_(static_cast<T*>
            (
                (size == 0
                 ? 0
                 : ::operator new(sizeof(T) * size))
            )
        )
    , vsize_(size)
    , vused_(0)
{}

template <typename T>
StackImpl<T>::~StackImpl()
{
    destroy(v_, v_ + vused_);
    ::operator delete(v_);
}

template <typename T>
void StackImpl<T>::Swap(StackImpl& other) throw()
{
    std::swap(v_, other.v_);
    std::swap(vsize_, other.vsize_);
    std::swap(vused_, other.vused_);
}

// Stack

template <typename T>
Stack<T>::Stack(size_t size)
    : StackImpl<T>(size)
{}

template <typename T> Stack<T>::~Stack() {}

template <typename T>
Stack<T>::Stack(const Stack& other)
    : StackImpl<T>(other.vused_)
{
    while (vused_ < other.vused_) {
        Push(other.v_[vused_]);
    }
}

template <typename T>
Stack<T>& Stack<T>::operator=(const Stack& other)
{   
    Stack tmp(other);
    Swap(tmp);
    return *this;
}

template <typename T>
size_t Stack<T>::Count() const
{
    return vused_;
}

template <typename T>
void Stack<T>::Push(const T& val)
{
    if (vused_ == vsize_) {
        Stack tmp(2 * vsize_);
        for (size_t i = 0; i < vused_; ++i) {
            tmp.Push(v_[i]);
        }
        tmp.Push(val);
        Swap(tmp);
    } else {
        construct(v_ + vused_, val);
        ++vused_;
    }
}

template <typename T>
T& Stack<T>::Top()
{
    if (vused_ == 0) {
        throw Underflow();
    }
    return v_[vused_ - 1];
}

template <typename T>
const T& Stack<T>::Top() const
{
    if (vused_ == 0) {
        throw Underflow();
    }
    return v_[vused_ - 1];
}

template <typename T>
void Stack<T>::Pop()
{
    if (vused_ == 0) {
        throw Underflow();
    }
    --vused_;
    destroy(v_ + vused_);
}

#endif
