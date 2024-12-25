#ifndef EXCEL_H
#define EXCEL_H

#include <QtAxContainer/QAxObject>
#include <QFile>
#include "log.h"

class excel
{
    QAxObject *_excel;
    QAxObject *_workbooks;  // 薄合集
    QAxObject *_workbook;   // 薄
    QAxObject *_worksheets; // 表合集
    QAxObject *_worksheet;  // 表
    QAxObject *_useRange;   // 使用的范围
    QAxObject *_cell;       // 选择的方格
    QString _filename;
    int _rowCount = 0;
    int _columnCount = 0;

public:
    excel(QString filename, bool ADD);
    ~excel();
    bool Write(class log data);
    bool Read(class log &data, park &Park);
    bool setFormat();
    bool save();

private:
    void setBlock(QString title, QString pos, QColor color, int xSize = 1, int ySize = 1, int wordSize = 0);
    void setColor(QString pos, QColor color, int xSize = 1, int ySize = 1);
    bool multipWrite(QString pos, const QVariantList &var);
    bool multipRead(QString pos, QVariantList &res, int xSize = 1, int ySize = 1);
};

#endif // EXCEL_H
