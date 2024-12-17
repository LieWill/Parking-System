#ifndef LOG_H
#define LOG_H

#include<QVariant>
// #include<vector>
#include"car.h"

class log
{
private:
    QVariantList _data;
public:
    log();
    void log_in(Car data);
    QVariantList &log_out();
};

#endif // LOG_H
