#include "log.h"

log::log() {}

void log::record(carParking Car)
{
    QVariantList tempVarRow;
    tempVarRow << Car.toString() << Car.getInTime().toString() << Car.getOutTime().toString() << Car.getCost();
    _records << QVariant(tempVarRow);
}

void log::setParkStates(park &state)
{
    QVariantList tempVarRow;
    for(size_t i = 0; i < state.parkNums(); i++)
    {
        tempVarRow << state.getStack(i).toString();
    }
    _parkStates << QVariant(tempVarRow);
    tempVarRow.clear();
    for(size_t i =0; i < state.queueNum(); i++)
    {
        tempVarRow << state.getQueue(i).toString();
    }
    _parkStates << QVariant(tempVarRow);
}

// void log::park_log_in(carParking data)
// {
//     // _ParkState << ++park_num <<data.toString();
//     // length++;
// }

QVariantList &log::getRecords()
{
    return _records;
}

QVariantList &log::getParkStates()
{
    return _parkStates;
}
