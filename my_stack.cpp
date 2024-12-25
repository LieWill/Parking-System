#include "my_stack.hpp"

#include "QDebug"

template<typename T>
stack<T>::stack(size_t cap)
{
    data = new T[cap];
    capacity = cap;
}

template<typename T>
stack<T>::stack(const stack &copy)
    :   data(new T[copy.capacity])
    ,   top(copy.top)
    ,   capacity(copy.capacity)
{
    qDebug() << "执行拷贝函数，拷贝容量为" << copy.capacity << "所有数量为" << copy.top;
    for(int i = 0; i < top; i++)
        data[i] = copy.data[i];
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
