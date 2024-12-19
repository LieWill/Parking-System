#include "car.h"
#include "QRandomGenerator"
#include <QDebug>
#include <QTimeZone>

Car::Car(carPlace place, QString plate_num)
    :   _place(place)
    ,   _plate_num(plate_num)
{

}

Car::Car()
{
    int plateLength = QRandomGenerator::global()->bounded(6,8); //生成一个6或7的随机数
    _place = (carPlace)QRandomGenerator::global()->bounded(0,34); //生成一个0到33的随机数
    for(int i = 0; i < plateLength; i++)
    {
        char rand = QRandomGenerator::global()->bounded(48, 58 + 26);
        if(rand > 57)
            rand += 7;
        _plate_num += (QChar)rand;
    }
}

void Car::show()
{
    qDebug() << setStatusTip[(int)_place] << _plate_num << '\n';
}

QString Car::toString()
{
    return QString(setStatusTip[(int)_place]+_plate_num);
}

