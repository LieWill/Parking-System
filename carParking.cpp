#include "carParking.h"
#include "qtimezone.h"

#define cost 5 // 每小时收费多少钱

// 默认构造函数，初始化停车信息
carParking::carParking()
    : Car()
{
    _start.toTimeZone(QTimeZone("China/Bei_Jing")); // 设置开始时间为北京时区
    _end.toTimeZone(QTimeZone("China/Bei_Jing"));
}

// 使用已有Car对象初始化停车信息（随机）
carParking::carParking(Car car)
    : Car(car)
{
}

// 使用位置和车牌号初始化停车信息
carParking::carParking(carPlace place, QString plate_num)
    : Car(place, plate_num)
{
    _start.toTimeZone(QTimeZone("China/Bei_Jing")); // 设置开始时间为北京时区
    _end.toTimeZone(QTimeZone("China/Bei_Jing"));
}

// 记录车辆进入停车场的时间
void carParking::parkIn()
{
    _end.setTime(QTime(24, 0, 0));         // 设置结束时间为当天的24点（无效时间，现实不存在24时）
    _start = QDateTime::currentDateTime(); // 设置开始时间为当前时间
    qDebug() << _start;
}

// 记录车辆离开停车场的时间
void carParking::parkOut()
{
    /*if (!_end.isValid()) // 如果结束时间无效，输出错误信息
        qDebug() << "时间无效";
    else
        qDebug() << _end; */               // 输出结束时间
    _end = QDateTime::currentDateTime(); // 更新结束时间为当前时间
    qDebug() << _end;
}

// 计算停车费用
double carParking::getCost()
{
    if (_end.isValid() && _end > _start)
    {
        quint64 differ = _end.toSecsSinceEpoch() - _start.toSecsSinceEpoch(); // 计算停车时长（秒）
        return differ * (cost / 3600);                                        // 根据时长和每小时费用计算总费用
    }
    return -1; // 返回负数，说明错误
}
