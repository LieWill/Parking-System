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
    void setParkStates(park &state);
    QVariantList &getRecords();
    QVariantList &getParkStates();
};

#endif // LOG_H
