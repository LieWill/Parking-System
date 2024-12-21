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
    inline QTime getInTime() const
    {
        return _start.time();
    }
    inline QTime getOutTime() const
    {
        return _end.time();
    }
    inline QDate getInDate() const
    {
        return _start.date();
    }
    inline QDate getOutDate() const
    {
        return _end.date();
    }
    bool operator==(const carParking differ) const
    {
        return getPlate_num() == differ.getPlate_num() && getPlace() == differ.getPlace();
    }
    double getCost();
};

#endif // CARPARKING_H
