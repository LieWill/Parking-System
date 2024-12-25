#include "log.h"

log::log() {}

void log::record(carParking Car)
{
    QVariantList tempVarRow;
    tempVarRow << Car.toString() << Car.getInTime().toString() << Car.getInDate().toString("yyyy/MM/dd")\
               << Car.getOutTime().toString() << Car.getInDate().toString("yyyy/MM/dd") << Car.getCost();
    _records << QVariant(tempVarRow);
}

void log::logParkStates(park &state)
{
    _parkStates.clear(); // 清空当前的状态

    for(size_t i = 0; i < state.parkNums(); i++)
    {   QVariantList tempVarRow;
        auto temp = state.getStack(i);
        tempVarRow << temp.toString() << temp.getInTime().toString() << temp.getInDate().toString("yyyy/MM/dd");
        if(i < state.queueNum())
        {
            temp = state.getQueue(i);
            tempVarRow << temp.toString() << temp.getInTime().toString() << temp.getInDate().toString("yyyy/MM/dd");
        }
        _parkStates << QVariant(tempVarRow);
    }
}

QVariantList &log::getRecords()
{
    return _records;
}

QVariantList &log::getParkStates()
{
    return _parkStates;
}

bool log::setRecords(const QVariantList &record)
{
    _parkStates = record;
    return true;
}

const park log::setParkStates(const QVariantList &state)
{
    _parkStates = state;
    park temp(10);
    stack<carParking> stack(10);
    queue<carParking> queue(10);

    //temp.setPark(10);

    return temp;
}

