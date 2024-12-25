#include "my_stack.hpp"
#include "QDebug"

// 模板类 stack 的构造函数
// 初始化栈的数据存储数组和容量
template<typename T>
stack<T>::stack(size_t cap)
{
    data = new T[cap]; // 动态分配一个大小为 cap 的数组
    capacity = cap;    // 设置栈的容量
}

// 模板类 stack 的拷贝构造函数
// 创建一个新的栈并复制另一个栈的内容
template<typename T>
stack<T>::stack(const stack &copy)
    :   data(new T[copy.capacity])    // 动态分配与被拷贝栈相同容量的数组
    ,   top(copy.top)                 // 设置栈顶指针
    ,   capacity(copy.capacity)        // 设置栈的容量
{
    qDebug() << "执行拷贝函数，拷贝容量为" << copy.capacity << "所有数量为" << copy.top;
    for(int i = 0; i < top; i++)      // 复制数据
        data[i] = copy.data[i];
}

// 向栈中压入一个元素
// 如果栈已满，返回 false；否则返回 true
template <typename T>
bool stack<T>::push(T value)
{
    if (top == capacity) // 检查栈是否已满
        return false;
    else
        data[top++] = value; // 将元素添加到栈顶并递增栈顶指针
    return true;
}

// 在栈中查找元素
// 如果找到，返回元素的索引；否则返回空值
template <typename T>
std::optional<size_t> stack<T>::find(T &value) const
{
    for (size_t i = 0; i < top; i++) // 遍历栈中的元素
    {
        if (data[i] == value) // 检查当前元素是否等于要查找的元素
            return i; // 如果找到，返回索引
    }
    return std::nullopt; // 如果未找到，返回空值
}

// 从栈中弹出一个元素
// 如果栈为空，返回空值；否则返回栈顶元素
template <typename T>
std::optional<T> stack<T>::pop()
{
    if (top == 0) // 检查栈是否为空
        return std::nullopt; // 如果为空，返回空值
    else
        return data[--top]; // 如果不为空，递减栈顶指针并返回原栈顶元素
}

