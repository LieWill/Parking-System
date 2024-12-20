#include "my_stack.hpp"

template<typename T>
stack<T>::stack(size_t cap)
{
    data = new T[cap];
    capacity = cap;
}

template <typename T>
bool stack<T>::push(T value)
{
    if (top == capacity)
        return false;
    else
        data[top++] = value;
    return true;
}

template <typename T>
std::optional<size_t> stack<T>::find(T &value) const
{
    for (size_t i = 0; i < top; i++)
    {
        if (data[i] == value)
            return i;
    }
    return std::nullopt; // 未找到，返回空值
}

template <typename T>
std::optional<T> stack<T>::pop()
{
    if (top == 0)
        return std::nullopt; // 栈为空，返回空值
    else
        return data[--top];
}
