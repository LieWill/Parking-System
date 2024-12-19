#include "carParking.h"
#include "qtimezone.h"

#define cost 5 // 每小时收费多少钱

carParking::carParking()
    :   Car()
{
    _start.toTimeZone(QTimeZone("China/Bei_Jing")); // 设置为北京时区
    _end.toTimeZone(QTimeZone("China/Bei_Jing"));
}

carParking::carParking(Car car)
    :   Car(car)
{}

carParking::carParking(carPlace place, QString plate_num)
    :   Car(place,plate_num)
{
    _start.toTimeZone(QTimeZone("China/Bei_Jing")); // 设置为北京时区
    _end.toTimeZone(QTimeZone("China/Bei_Jing"));
}

void carParking::parkIn()
{
    _end.setTime(QTime(24,0,0));
    _start = QDateTime::currentDateTime();
}

void carParking::parkOut()
{
    if(!_end.isValid())
        qDebug() << "时间无效";
    else
        qDebug() << _end;
    _end = QDateTime::currentDateTime();
}

double carParking::getCost()
{
    if(_end.isValid() && _end > _start)
    {
        quint64 differ = _end.toSecsSinceEpoch() - _start.toSecsSinceEpoch();
        return differ * (cost / 3600);
    }
    return -1; // 返回负数，说明错误
}
