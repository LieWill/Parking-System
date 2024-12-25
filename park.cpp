#include "park.h"

// 构造函数，初始化停车场、等待队列和临时道路的大小
park::park(size_t size)
    :   car_park(10)    // 初始化停车场栈，默认大小为10
    ,   car_queue(10)   // 初始化等待队列，默认大小为10
    ,   road_way(10)    // 初始化临时道路栈，默认大小为10
{}

// 设置停车场和等待队列
void park::setPark(stack<carParking> park, queue<carParking> queue)
{
    car_park = park;    // 将传入的停车场栈赋值给成员变量 car_park
    // car_queue = queue; // 此行被注释，因此不设置等待队列
}

// 车辆进入停车场
state park::in(const Car &car)
{
    state res = state::OK; // 初始化返回状态为 OK
    if(car_park.isFull()) // 检查停车场是否已满
    {
        res = state::park_full; // 设置返回状态为停车场已满
        if(car_queue.isFull())  // 检查等待队列是否已满
            res = state::queue_full; // 设置返回状态为等待队列已满
        else
        {
            auto temp = carParking(car); // 创建一个临时 carParking 对象
            temp.parkIn(); // 记录车辆进入时间
            car_queue.push(temp); // 将临时对象加入等待队列
        }
    }
    else
    {
        auto temp = carParking(car); // 创建一个临时 carParking 对象
        temp.parkIn(); // 记录车辆进入时间
        car_park.push(temp); // 将临时对象加入停车场
    }
    return res; // 返回操作状态
}

// 车辆离开停车场
state park::out(carParking &outCar)
{
    if (car_park.isEmpty()) // 检查停车场是否为空
        return state::park_empty; // 返回停车场为空状态
    auto index = car_park.find(outCar); // 查找车辆在停车场中的位置
    if (index.has_value()) // 如果车辆存在于停车场
    {
        // 将车辆后的所有车辆移动到临时道路
        for (size_t i = car_park.Top() - 1; i > index.value(); i--)
            road_way.push(car_park.pop().value());
        outCar = car_park.pop().value(); // 移除并获取目标车辆
        // 将临时道路上的车辆移回停车场
        for (size_t i = car_park.Top(); !road_way.isEmpty(); i--)
            car_park.push(road_way.pop().value());
        outCar.parkOut(); // 记录车辆离开时间
        if (!car_queue.isEmpty()) // 检查等待队列是否有车辆
        {
            auto temp = carParking(car_queue.pop().value()); // 获取等待队列中的第一个车辆
            temp.parkIn(); // 记录车辆进入时间
            car_park.push(temp); // 将其加入停车场
            return state::OK; // 返回操作成功状态
        }
        else
            return state::queue_empty; // 返回等待队列为空状态
    }
    else if((index = car_queue.find(outCar)).has_value()) // 如果车辆存在于等待队列
    {
        auto car = car_queue.extract(index.value()); // 从等待队列中移除车辆
        if(car.has_value())
            outCar = carParking(car.value()); // 设置输出车辆
        else
            return state::no_find; // 返回未找到车辆状态
        return state::OK; // 返回操作成功状态
    }
    else
        return state::no_find; // 返回未找到车辆状态
}

// 查找车辆
bool park::find(Car &target) const
{
    auto temp = carParking(target); // 创建一个临时的 carParking 对象
    if(car_park.find(temp).has_value()) // 在停车场中查找
        return true;
    return car_queue.find(temp).has_value(); // 在等待队列中查找
}



