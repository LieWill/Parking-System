#ifndef PARK_H
#define PARK_H

#include "carParking.h"
#include "my_stack.cpp"
#include "my_queue.cpp"
#include "car.h"

enum class state
{
    OK,          // 操作成功
    park_empty,  // 停车场为空
    park_full,   // 停车场已满
    no_find,     // 车辆不存在
    queue_empty, // 队列为空
    queue_full,  // 队列已满
};

class park
{
    stack<carParking> car_park;
    stack<carParking> road_way;
    queue<Car> car_queue;
public:
    park(size_t size);
    state in(Car &car);
    state out(carParking &outCar);
    bool find(Car &target) const;
    inline Car &getQueue(size_t index)
    {
        return car_queue.at(index);
    }
    inline carParking &getStack(size_t index)
    {
        return car_park.at(index);
    }
    inline carParking &getRoad(size_t index)
    {
        return road_way.at(index);
    }
    inline size_t parkNums() const
    {
        return car_park.Top();
    }
    inline size_t roadWayNums() const
    {
        return road_way.Top();
    }
    inline size_t queueNum() const
    {
        return car_queue.num();
    }
};

#endif // PARK_H
