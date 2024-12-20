#include "park.h"

park::park(size_t size)
    :   car_park(10)
    ,   car_queue(10)
    ,   road_way(10)
{}

state park::in(Car &car)
{
    state res = state::OK;
    if(car_park.isFull())
    {
        res = state::park_full;
        if(car_queue.isFull())
            res = state::queue_full;
        else
            car_queue.push(car);
    }
    else
    {
        auto temp = carParking(car);
        temp.parkIn();
        car_park.push(temp);
    }
    return res;
}

state park::out(carParking &outCar)
{
    // state res = state::OK;
    // if(car_park.isEmpty())
    //     return state::park_empty;
    // else
    // {
    //     auto index = car_park.find(outCar);
    //     if(!index.has_value())
    //         return state::no_find;
    //     outCar = car_park.pop().value();
    //     if(!car_queue.isEmpty())
    //         car_park.push(car_queue.pop().value());
    //     else
    //         res = state::queue_empty;
    // }
    if (car_park.isEmpty()) // 判断停车场为空
        return state::park_empty;
    auto state = car_park.find(outCar); // 查找车辆
    if (state == std::nullopt)       // 判断车辆不存在
        return state::no_find;
    for (size_t i = car_park.Top() - 1; i > state.value(); i--)
        road_way.push(car_park.pop().value()); // 将车辆后边的车辆移到便道
    outCar = car_park.pop().value();
    for (size_t i = car_park.Top(); !road_way.isEmpty(); i--)
        car_park.push(road_way.pop().value()); // 将便道的车辆移回停车场
    outCar.parkOut();
    if (!car_queue.isEmpty()) // 判断等待区是否有车辆
    {
        auto temp = carParking(car_queue.pop().value());
        temp.parkIn(); // 记录进入时间
        car_park.push(temp);
    }
    return state::OK;
}

bool park::find(Car &target) const
{
    auto temp = carParking(target);
    if(car_park.find(temp).has_value())
        return true;
    return car_queue.find(target).has_value();
}


