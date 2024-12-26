#include "my_queue.hpp"
#include "QDebug"

// 模板类 queue 的拷贝构造函数
// 创建一个新的队列并复制另一个队列的内容
template<typename T>
queue<T>::queue(size_t cap)
{
    data = new T[cap];
    capacity = cap;
}

template<typename T>
queue<T>::queue(const queue &copy)
    :   capacity(copy.capacity)    // 动态分配与被拷贝队列相同容量的数组
    ,   data(new T[copy.buf_num])
    ,   rear(copy.buf_num)               // 设置队列尾部部指针
    ,   buf_num(copy.buf_num)         // 设置队列当前元素数量
{
    for(int i = 0; i < buf_num; i++)  // 复制数据
    {
        data[i] = copy.data[i + copy.front];
        qDebug() << copy.data[i].toString() << data[i].toString();
    }
}

// 从队列中提取指定索引的元素
// 如果索引有效，移除元素并返回它；否则返回空值
template<typename T>
std::optional<T> queue<T>::extract(size_t index)
{
    if(index >= buf_num) // 检查索引是否超出范围
        return std::nullopt;
    T res = at(index); // 获取指定索引的元素
    // 将后续元素向前移动一位
    for(int i = index; i < buf_num; i++)
    {
        at(i) = at(i + 1);
    }
    buf_num--; // 减少队列中元素的数量
    if(rear == 0) // 如果尾部指针在数组的开始，将其移到末尾
        rear = capacity - 1;
    else
        rear--; // 否则，将尾部指针向前移动一位
    return res; // 返回被提取的元素
}

// 向队列中添加一个元素
// 如果队列已满，返回 false；否则返回 true
template <typename T>
bool queue<T>::push(T value)
{
    if (buf_num == capacity) // 检查队列是否已满
        return false;
    data[rear] = value; // 在尾部添加元素
    rear++; // 尾部指针后移
    if (rear == capacity) // 如果尾部指针超出数组范围，将其移到开始
        rear = 0;
    buf_num++; // 增加队列中元素的数量
    return true;
}

// 从队列中移除并返回队首元素
// 如果队列为空，返回空值；否则返回队首元素
template <typename T>
std::optional<T> queue<T>::pop()
{
    if (buf_num == 0) // 检查队列是否为空
        return std::nullopt;
    size_t temp = front++; // 保存当前队首元素的索引并移动队首指针
    if (front == capacity) // 如果队首指针超出数组范围，将其移到开始
        front = 0;
    buf_num--; // 减少队列中元素的数量
    return data[temp]; // 返回原队首元素
}

// 在队列中查找元素
// 如果找到，返回元素的索引；否则返回空值
template<typename T>
std::optional<size_t> queue<T>::find(T &target) const
{
    for(size_t i = 0; i < capacity; i++) // 遍历队列中的元素
    {
        // 检查当前元素是否等于要查找的元素
        if(target == data[((i % capacity) + front) % capacity])
            return i; // 如果找到，返回索引
    }
    return std::nullopt; // 如果未找到，返回空值
}
