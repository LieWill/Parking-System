#include "my_queue.hpp"


template <typename T>
bool queue<T>::push(T value)
{
    if (buf_num == capacity)
        return false;
    data[rear] = value;
    rear++;
    if (rear == capacity)
        rear = 0;
    buf_num++;
    return true;
}

template <typename T>
std::optional<T> queue<T>::pop()
{
    if (buf_num == 0)
        return std::nullopt;
    size_t temp = front++;
    if (front == capacity)
        front = 0;
    buf_num--;
    return data[temp];
}

template<typename T>
std::optional<size_t> queue<T>::find(T &target) const
{
    for(size_t i = 0; i < capacity; i++)
    {
        if(target == data[((i % capacity) + front) % capacity])
            return i;
    }
    return std::nullopt;
}
