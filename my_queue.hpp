#ifndef QUEUE_H
#define QUEUE_H

#include<optional>

template <typename T>
class queue
{
private:
    T *data;            // 数据
    size_t front = 0;   // 队首指针
    size_t rear = 0;    // 队尾指针
    size_t capacity;    // 缓冲区容量
    size_t buf_num = 0; // 缓冲区中元素个数

public:
    queue(size_t cap = 10)      // 构造函数
    {
        data = new T[cap];
        capacity = cap;
    }
    queue(const queue &copy);   // 实现深拷贝
    ~queue() { delete[] data; } // 析构函数
    std::optional<T> extract(size_t index);
    bool push(T value);         // 入队
    std::optional<T> pop();     // 出队
    std::optional<size_t> find(T &target) const;
    inline size_t num() const   // 获取缓冲区中元素个数
    {
        return buf_num;
    }
    inline bool isEmpty() const // 判断缓冲区是否为空
    {
        return buf_num == 0;
    }
    inline bool isFull() const  // 判断缓冲区是否已满
    {
        return buf_num == capacity;
    }
    inline T& at(size_t index)
    {
        return data[((index % capacity) + front) % capacity]; // 防止越界访问
    }
};

#endif // QUEUE_H
