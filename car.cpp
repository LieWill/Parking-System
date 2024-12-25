#include "car.h"
#include "QRandomGenerator"
#include <QDebug>
#include <QTimeZone>
#include <QByteArray>

// 构造函数，初始化车辆位置和车牌号
Car::Car(carPlace place, QString plate_num)
    :   _place(place)
    ,   _plate_num(plate_num)
{}

Car::Car(const QString plate)
    :   _plate_num(plate)
{
    _place = (carPlace)1;//index;
}

// 默认构造函数，随机生成车辆位置和车牌号
Car::Car()
{
    int plateLength = QRandomGenerator::global()->bounded(6,8); // 生成一个6或7的随机数作为车牌号长度
    _place = (carPlace)QRandomGenerator::global()->bounded(0,34); // 生成一个0到33的随机数作为车辆位置
    for(int i = 0; i < plateLength; i++)
    {
        char rand = QRandomGenerator::global()->bounded(48, 58 + 26); // 生成一个48到83的随机数
        if(rand > 57) // 如果生成的随机数大于57（即生成了字母）
            rand += 7; // 调整ASCII码值以获取字母
        _plate_num += (QChar)rand; // 将生成的字符添加到车牌号字符串
    }
}

// Car::~Car()
// {
//     // delete _plate_num;
// }

// 使用qDeBug打印车辆信息
void Car::show()
{
    qDebug() << setStatusTip[(int)_place] << _plate_num << '\n'; // 输出车辆位置和车牌号
}

// 将车辆信息转换为字符串
QString Car::toString()
{
    return QString(setStatusTip[(int)_place]+_plate_num); // 返回车辆位置和车牌号的字符串
}


