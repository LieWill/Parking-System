#ifndef STACK_H
#define STACK_H

#include<optional>

template<typename T>
class stack
{
private:
    T *data;         // 数据
    size_t top = 0;  // 栈顶指针
    size_t capacity; // 栈容量

public:
    stack(size_t cap = 10);              // 构造函数
    ~stack() { delete[] data; }          // 析构函数
    bool push(T value);                  // 入栈
    std::optional<T> pop();              // 出栈
    std::optional<size_t> find(T value); // 查找
    inline bool isEmpty() const          // 判断是否为空
    {
        return top == 0;                 // 栈空
    }
    inline bool isFull() const           // 判断是否已满
    {
        return top == capacity;          // 栈满
    }
    inline size_t Top() const            // 获取栈顶指针
    {
        return top;
    }
    inline T &at(size_t index)
    {
        return data[index % capacity];  // 防止越界访问
    }
};

#endif // STACK_H
