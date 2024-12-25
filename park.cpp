#include "park.h"

park::park(size_t size)
    :   car_park(10)
    ,   car_queue(10)
    ,   road_way(10)
{}

void park::setPark(stack<carParking> park, queue<carParking> queue)
{
    car_park = park;
    //car_queue = queue;
}

state park::in(const Car &car)
{
    state res = state::OK;
    if(car_park.isFull())
    {
        res = state::park_full;
        if(car_queue.isFull())
            res = state::queue_full;
        else
        {
            auto temp = carParking(car);
            temp.parkIn();
            car_queue.push(temp);
        }
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
    if (car_park.isEmpty()) // 判断停车场为空
        return state::park_empty; // 停车场空
    auto index = car_park.find(outCar);
    if (index.has_value())       // 判断车辆存在
    {
        for (size_t i = car_park.Top() - 1; i > index.value(); i--)
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
            return state::OK;
        }
        else
            return state::queue_empty;
    }
    else if((index = car_queue.find(outCar)).has_value())
    {
        auto car = car_queue.extract(index.value());
        if(car.has_value())
            outCar = carParking(car.value());
        else
            return state::no_find; // 没找着
        return state::OK;
    }
    else
        return state::no_find;
}

bool park::find(Car &target) const
{
    auto temp = carParking(target);
    if(car_park.find(temp).has_value())
        return true;
    return car_queue.find(temp).has_value();
}


