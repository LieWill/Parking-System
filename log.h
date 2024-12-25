#ifndef LOG_H
#define LOG_H

#include<QVariant>
#include"park.h"

class log
{
private:
    QVariantList _parkStates; // 停车场状态
    QVariantList _records;    // 记录结果
public:
    log();
    void record(carParking Car);
    void logParkStates(park &state);
    QVariantList &getRecords();
    QVariantList &getParkStates();
    bool setRecords(const QVariantList &record);
    const park setParkStates(const QVariantList &state);
};

#endif // LOG_H
