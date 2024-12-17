#include "log.h"

log::log() {}

void log::log_in(Car data)
{
    QVariantList tempVarRow;
    tempVarRow << data.toString();
    _data << QVariant(tempVarRow);
}

QVariantList &log::log_out()
{
    return _data;
}
