#include "excel.h"
#include "QDebug"
#include "QFileInfo"
#include <QtAxContainer/QAxObject>
#include <QFileDialog>

excel::excel(QString filename)
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
    // if(info.isFile())
    // {
    //     qDebug() << "文件存在";
    //     _workbooks->dynamicCall("Open(const QString&)", filename); //打开打开已存在的工作簿
    // }
    // else
    // {
        _workbooks->dynamicCall("Add");
    qDebug() << "成功ADD";
    //}
    // _workbook = _excel->querySubObject("ActiveWorkBook");    // 获取当前活动工作簿
    // if(_workbook == nullptr)
    // {
    //     qDebug() << "活动薄获取失败！";
    //     _excel->dynamicCall("Quit()");
    //     return;
    // }
    // _worksheets = _workbook->querySubObject("Sheets");
        _worksheet = _excel->querySubObject("ActiveSheet");
    qDebug() << "成功ACTIVE";
    // if(_worksheets == nullptr)
    // {
    //     qDebug() << "表集获取失败！";
    //     _excel->dynamicCall("Quit()");
    //     return;
    // }
    //_worksheet = _workbook->querySubObject("WorkSheets(int)", 1); //获取第一个表
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

bool excel::Read(QVariantList &mList)
{
    _useRange = _worksheet->querySubObject("UsedRange"); // 读取写入过的区域
    mList = _useRange->dynamicCall("Value").toList();    // 将读入信息转化为链表
    for(int i = 0; i < _rowCount; i++)
    {
        qDebug() << mList.at(i).toList() << '\n';
    }
    return true;
}

bool excel::setFormat()
{
    // _useRange = _worksheet->querySubObject("Range(QString)", "A1");

    // _useRange = _useRange->querySubObject("Resize(int,int)", 1, width); // 设置写入区域的大小
    _rowCount = 1;
    _columnCount = 11;
    _useRange = _worksheet->querySubObject ("Range(QString)", "A1"); // 设置写入的位置
    _useRange = _useRange->querySubObject("Resize(int,int)", _rowCount, _columnCount); // 设置写入区域的大小
    _useRange->querySubObject("Font")->setProperty("Size", 28);//对字体进行设置
    _useRange->setProperty("RowHeight", 40);    // 设置标题行高度
    _useRange->setProperty("ColWeith", 10);
    _useRange->setProperty("MergeCells", true); // 合并单元格
    _useRange->setProperty("Value", "停车场状态");     // 设置标题
    QAxObject *cells = _useRange->querySubObject("Columns");
    QAxObject *interior = cells->querySubObject("Interior");
    interior->setProperty("Color", QColor(255,255,0));
    _useRange->setProperty("HorizontalAlignment", -4108);
    //左对齐（xlLeft）：-4131  居中（xlCenter）：-4108  右对齐（xlRight）：-4152
    _useRange->setProperty("VerticalAlignment", -4108);
    //上对齐（xlTop）-4160 居中（xlCenter）：-4108  下对齐（xlBottom）：-4107

    _rowCount = 1;
    _columnCount = 4;
    _useRange = _worksheet->querySubObject ("Range(QString)", "A4"); // 设置写入的位置
    _useRange = _useRange->querySubObject("Resize(int,int)", _rowCount, _columnCount); // 设置写入区域的大小
    _useRange->querySubObject("Font")->setProperty("Size", 28);//对字体进行设置
    _useRange->setProperty("RowHeight", 40);    // 设置标题行高度
    _useRange->setProperty("ColWeith", 10);
    _useRange->setProperty("MergeCells", true); // 合并单元格
    _useRange->setProperty("Value", "停车历史记录");// 设置标题
    cells = _useRange->querySubObject("Columns");
    interior = cells->querySubObject("Interior");
    interior->setProperty("Color", QColor(173,216,230));
    _useRange->setProperty("HorizontalAlignment", -4108);
    //左对齐（xlLeft）：-4131  居中（xlCenter）：-4108  右对齐（xlRight）：-4152
    _useRange->setProperty("VerticalAlignment", -4108);
    //上对齐（xlTop）-4160 居中（xlCenter）：-4108  下对齐（xlBottom）：-4107

    _useRange = _worksheet->querySubObject("Range(QString)", "A2");
    _useRange->setProperty("Value", "停车场");// 设置标题
    cells = _useRange->querySubObject("Columns");
    interior = cells->querySubObject("Interior");
    interior->setProperty("Color", QColor(144,238,144));
    _useRange->setProperty("HorizontalAlignment", -4108);
    //左对齐（xlLeft）：-4131  居中（xlCenter）：-4108  右对齐（xlRight）：-4152
    _useRange->setProperty("VerticalAlignment", -4108);
    //上对齐（xlTop）-4160 居中（xlCenter）：-4108  下对齐（xlBottom）：-4107

    _useRange = _worksheet->querySubObject("Range(QString)", "A3");
    _useRange->setProperty("Value", "等候区");// 设置标题
    cells = _useRange->querySubObject("Columns");
    interior = cells->querySubObject("Interior");
    interior->setProperty("Color", QColor(255,0,255));
    _useRange->setProperty("HorizontalAlignment", -4108);
    //左对齐（xlLeft）：-4131  居中（xlCenter）：-4108  右对齐（xlRight）：-4152
    _useRange->setProperty("VerticalAlignment", -4108);
    //上对齐（xlTop）-4160 居中（xlCenter）：-4108  下对齐（xlBottom）：-4107

    _useRange = _worksheet->querySubObject("Range(QString)", "A5");
    _useRange->setProperty("Value", "车牌");// 设置标题
    cells = _useRange->querySubObject("Columns");
    interior = cells->querySubObject("Interior");
    interior->setProperty("Color", QColor(255,165,0));
    _useRange->setProperty("HorizontalAlignment", -4108);
    //左对齐（xlLeft）：-4131  居中（xlCenter）：-4108  右对齐（xlRight）：-4152
    _useRange->setProperty("VerticalAlignment", -4108);
    //上对齐（xlTop）-4160 居中（xlCenter）：-4108  下对齐（xlBottom）：-4107

    _useRange = _worksheet->querySubObject("Range(QString)", "B5");
    _useRange->setProperty("Value", "停车时间");// 设置标题
    cells = _useRange->querySubObject("Columns");
    interior = cells->querySubObject("Interior");
    interior->setProperty("Color", QColor(255,0,0));
    _useRange->setProperty("HorizontalAlignment", -4108);
    //左对齐（xlLeft）：-4131  居中（xlCenter）：-4108  右对齐（xlRight）：-4152
    _useRange->setProperty("VerticalAlignment", -4108);
    //上对齐（xlTop）-4160 居中（xlCenter）：-4108  下对齐（xlBottom）：-4107

    _useRange = _worksheet->querySubObject("Range(QString)", "C5");
    _useRange->setProperty("Value", "出车时间");// 设置标题
    cells = _useRange->querySubObject("Columns");
    interior = cells->querySubObject("Interior");
    interior->setProperty("Color", QColor(124,252,0));
    _useRange->setProperty("HorizontalAlignment", -4108);
    //左对齐（xlLeft）：-4131  居中（xlCenter）：-4108  右对齐（xlRight）：-4152
    _useRange->setProperty("VerticalAlignment", -4108);
    //上对齐（xlTop）-4160 居中（xlCenter）：-4108  下对齐（xlBottom）：-4107

    _useRange = _worksheet->querySubObject("Range(QString)", "D5");
    _useRange->setProperty("Value", "花费");// 设置标题
    cells = _useRange->querySubObject("Columns");
    interior = cells->querySubObject("Interior");
    interior->setProperty("Color", QColor(138,43,226));
    _useRange->setProperty("HorizontalAlignment", -4108);
    //左对齐（xlLeft）：-4131  居中（xlCenter）：-4108  右对齐（xlRight）：-4152
    _useRange->setProperty("VerticalAlignment", -4108);
    //上对齐（xlTop）-4160 居中（xlCenter）：-4108  下对齐（xlBottom）：-4107
    return true;
}

bool excel::save()
{
    qDebug() << "开始保存";
    // QFileInfo info(_filename);
    // if(info.isFile())
    // {
    //     _workbook->dynamicCall("Save()"); // 保存工作薄
    // }
    // else
    // {
        _worksheet->dynamicCall("SaveAs(const QString&)", QDir::toNativeSeparators(_filename));
    //}
    return true;
}

bool excel::Write(class log data)
{
    _rowCount = data.getParkStates().size();
    if(_rowCount == 0)
        return false;
    _columnCount = data.getParkStates().at(0).toList().size();
    if(_columnCount == 0)
        return false;

    _useRange = _worksheet->querySubObject ("Range(QString)", "B2"); // 设置写入的位置
    _useRange = _useRange->querySubObject("Resize(int,int)", _rowCount, _columnCount); // 设置写入区域的大小
    _useRange->setProperty("HorizontalAlignment", -4108);
    //左对齐（xlLeft）：-4131  居中（xlCenter）：-4108  右对齐（xlRight）：-4152
    _useRange->setProperty("VerticalAlignment", -4108);
    //上对齐（xlTop）-4160 居中（xlCenter）：-4108  下对齐（xlBottom）：-4107
    _useRange->setProperty("Weight", 8);
    _useRange->setProperty ("Value", data.getParkStates());       // 可以设置属性的方法写入

    _rowCount = data.getRecords().size();
    if(_rowCount == 0)
        return false;
    _columnCount = data.getRecords().at(0).toList().size();
    if(_columnCount == 0)
        return false;

    _useRange = _worksheet->querySubObject ("Range(QString)", "A6"); // 设置写入的位置
    _useRange = _useRange->querySubObject("Resize(int,int)", _rowCount, _columnCount); // 设置写入区域的大小
    _useRange->setProperty("HorizontalAlignment", -4108);
    //左对齐（xlLeft）：-4131  居中（xlCenter）：-4108  右对齐（xlRight）：-4152
    _useRange->setProperty("VerticalAlignment", -4108);
    //上对齐（xlTop）-4160 居中（xlCenter）：-4108  下对齐（xlBottom）：-4107
    _useRange->setProperty ("Value", data.getRecords());       // 可以设置属性的方法写入
    return true;
}
