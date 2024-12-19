#ifndef CARPARKING_H
#define CARPARKING_H

#include<QDateTime>
#include"car.h"

class carParking : public Car
{
    QDateTime _start;
    QDateTime _end;
public:
    carParking();
    carParking(Car car);
    carParking(carPlace place, QString plate_num);
    void parkIn();
    void parkOut();
    inline QDateTime getInTime()
    {
        return _start;
    }
    inline QDateTime getOutTime()
    {
        return _end;
    }
    double getCost();
};

#endif // CARPARKING_H
