#include "excel.h"
#include "QDebug"
#include "QFileInfo"
#include <QtAxContainer/QAxObject>
#include <QFileDialog>

excel::excel(QString filename, bool ADD)
    : _filename(filename)
{
    _excel = new QAxObject("Excel.Application");
    if(_excel->isNull())
    {
        qDebug() << "excel内存申请错误";
        return;
    }
    if(_excel->isNull())
    {
        _excel->setControl("KET.Application");
        if(_excel->isNull())
        {
            qDebug() << "excel文件加载失败，请检查电脑是否有excel软件";
            return;
        }
    }

    _workbooks = _excel->querySubObject("WorkBooks");    // 获取工作簿集合
    if (nullptr == _workbooks)
    {
        qDebug() << "工作集获取失败！";
        _excel->dynamicCall("Quit()");
        return;
    }
    QFileInfo info(filename);
    if(ADD)
    {
        _workbooks->dynamicCall("Add");
        _worksheet = _excel->querySubObject("ActiveSheet");
    }
    else
    {
        qDebug() << "文件存在";
        _workbooks->dynamicCall("Open(const QString&)", filename); //打开打开已存在的工作簿
        _workbook = _excel->querySubObject("ActiveWorkBook");    // 获取当前活动工作簿
        if(_workbook == nullptr)
        {
            qDebug() << "活动薄获取失败！";
            _excel->dynamicCall("Quit()");
            return;
        }
        _worksheets = _workbook->querySubObject("Sheets");
        if(_worksheets == nullptr)
        {
            qDebug() << "表集获取失败！";
            _excel->dynamicCall("Quit()");
            return;
        }
        _worksheet = _workbook->querySubObject("WorkSheets(int)", 1); //获取第一个表
    }

    if(_worksheet == nullptr)
    {
        qDebug() << "表获取失败";
        _excel->dynamicCall("Quit()");
        return;
    }
    _excel->setProperty("Visible", false);      // 显示excel
    _excel->setProperty("DisolayAlerts",false); // 弹出警告
}

excel::~excel()
{
    //_workbook->dynamicCall("SaveAs(const QString&)", QDir::toNativeSeparators(_filename)); //保存到fileName的文件
    _worksheet->dynamicCall("Close()"); //关闭工作簿
    _excel->dynamicCall("Quit()");
    qDebug() << "EXCEL进程已关闭";
    delete _excel;
}

bool excel::Read(class log &data, park &Park)
{
    QVariantList temp;
    multipRead("A5", temp, 10, 6);
    data.setRecords(temp);
    stack<carParking> stack(10);
    queue<carParking> queue(10);
    int size = temp.size();
    qDebug() << "Size = " << size;
    for(int i = 0; i < size; i++)
    {
        auto temp2 = temp.at(i).toList();
        qDebug() << i << ":" << temp2;
        if(temp2.at(0).isValid())
        {
            carParking carTemp(temp2.at(0).toString());
            carTemp.setInTime(QTime::fromString(temp2.at(1).toString()));
            carTemp.setInDate(QDate::fromString(temp2.at(2).toString(),"yyyy/MM/dd"));
            stack.push(carTemp);
            if(temp2.at(3).isValid())
            {
                carParking queueTemp(temp2.at(3).toString());
                queueTemp.setInTime(QTime::fromString(temp2.at(4).toString()));
                queueTemp.setInDate(QDate::fromString(temp2.at(5).toString(),"yyyy/MM/dd"));
                queue.push(queueTemp);
            }
        }
    }
    Park.setPark(stack,queue);
    return true;
}

bool excel::setFormat()
{
    for(char i = 'A'; i < 'L'; i++)
        _worksheet->querySubObject("Columns(const QString)", QString(i))\
                  ->setProperty("ColumnWidth", 10); // 设置A~K列宽度为10
    setBlock("停车场状态","A1", QColor(255,255,0), 2, 6, 27);

    setBlock("停车场", "A3", QColor(144,238,144), 1, 3);
    setBlock("等候区", "D3", QColor(142,229,238), 1, 3);

    setBlock("车牌", "A4", QColor(255,165,0));
    setBlock("停车时间", "B4", QColor(255,192,203), 1, 2);
    setColor("A5", QColor(240,255,240), 10, 3);

    setBlock("车牌", "D4", QColor(255,165,0));
    setBlock("入队时间", "E4", QColor(255,192,203), 1, 2);
    setColor("D5", QColor(240,255,255), 10, 3);

    setBlock("停车场历史记录", "A15", QColor(173,216,230), 2, 6, 27);

    setBlock("车牌", "A17", QColor(255,165,0));
    setBlock("停车时间", "B17", QColor(255,192,203), 1, 2);
    setBlock("出车时间", "D17", QColor(124,252,0), 1, 2);
    setBlock("花费/元", "F17", QColor(238,224,229));
    return true;
    // _useRange->setProperty("RowHeight", 40);    // 设置标题行高度
}

bool excel::save()
{
    _worksheet->dynamicCall("SaveAs(const QString&)", QDir::toNativeSeparators(_filename));
    return true;
}

void excel::setBlock(QString title, QString pos, QColor color, int xSize, int ySize, int wordSize)
{
    _useRange = _worksheet->querySubObject("Range(QString)", pos);
    _useRange = _useRange->querySubObject("Resize(int,int)", xSize, ySize); // 设置写入区域的大小
    _useRange->setProperty("MergeCells", true); // 合并单元格
    _useRange->setProperty("Value", title);// 设置标题
    _useRange->querySubObject("Columns")->querySubObject("Interior")->setProperty("Color", color);
    _useRange->setProperty("HorizontalAlignment", -4108);
    //左对齐（xlLeft）：-4131  居中（xlCenter）：-4108  右对齐（xlRight）：-4152
    _useRange->setProperty("VerticalAlignment", -4108);
    //上对齐（xlTop）-4160 居中（xlCenter）：-4108  下对齐（xlBottom）：-4107
    if(wordSize > 0)
        _useRange->querySubObject("Font")->setProperty("Size", wordSize);//对字体进行设置
}

void excel::setColor(QString pos, QColor color, int xSize, int ySize)
{
    _useRange = _worksheet->querySubObject("Range(QString)", pos);
    _useRange = _useRange->querySubObject("Resize(int,int)", xSize, ySize); // 设置写入区域的大小
    _useRange->querySubObject("Columns")->querySubObject("Interior")->setProperty("Color", color);
}

bool excel::multipWrite(QString pos, const QVariantList &var)
{
    _rowCount = var.size();
    if(_rowCount == 0)
        return false;
    _columnCount = var.at(0).toList().size();
    if(_columnCount == 0)
        return false;
    _useRange = _worksheet->querySubObject ("Range(QString)", pos); // 设置写入的位置
    _useRange = _useRange->querySubObject("Resize(int,int)", _rowCount, _columnCount); // 设置写入区域的大小
    _useRange->setProperty("HorizontalAlignment", -4108);
    //左对齐（xlLeft）：-4131  居中（xlCenter）：-4108  右对齐（xlRight）：-4152
    _useRange->setProperty("VerticalAlignment", -4108);
    //上对齐（xlTop）-4160 居中（xlCenter）：-4108  下对齐（xlBottom）：-4107
    _useRange->setProperty("Weight", 8);
    _useRange->setProperty ("Value", var);       // 可以设置属性的方法写入
    return true;
}

bool excel::multipRead(QString pos, QVariantList &res, int xSize, int ySize)
{
    _useRange = _worksheet->querySubObject ("Range(QString)", pos); // 设置写入的位置
    _useRange = _useRange->querySubObject("Resize(int,int)", xSize, ySize); // 设置写入区域的大小
    res = _useRange->dynamicCall("Value").toList();    // 将读入信息转化为链表
    return true;
}

bool excel::Write(class log data)
{
    bool state = multipWrite("A5",data.getParkStates());
    state |= multipWrite("A18",data.getRecords());
    return state;
}
