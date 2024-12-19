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
        car_park.push(carParking(car));
    return res;
}

state park::out(Car &car)
{
    state res = state::OK;
    if(car_park.isEmpty())
        res = state::park_empty;
    else
    {
        car = car_park.pop().value();
        if(!car_queue.isEmpty())
            car_park.push(car_queue.pop().value());
        else
            res = state::queue_empty;
    }
    return res;
}


