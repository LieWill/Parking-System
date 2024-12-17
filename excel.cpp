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
    _workbook->dynamicCall("Close()"); //关闭工作簿
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

bool excel::setTitle(QString title, int width)
{
    _cell = _worksheet->querySubObject("Range(QString)", "A1");

    _cell = _useRange->querySubObject("Resize(int,int)", 1, width); // 设置写入区域的大小

    _cell->querySubObject("Font")->setProperty("Size", 15);//对字体进行设置
    _cell->setProperty("RowHeight", 40); //合并标题行

    _cell->setProperty("MergeCells", true);//合并单元格
    _cell->setProperty("Value",title);
    _cell->setProperty("HorizontalAlignment", -4108);
    //左对齐（xlLeft）：-4131  居中（xlCenter）：-4108  右对齐（xlRight）：-4152
    _cell->setProperty("VerticalAlignment", -4108);
    //上对齐（xlTop）-4160 居中（xlCenter）：-4108  下对齐（xlBottom）：-4107

    return true;
}

bool excel::save()
{
    _workbook->dynamicCall("Save()"); //关闭工作簿
    return true;
}

bool excel::Write(QVariantList &mList)
{
    _rowCount = mList.size();
    _columnCount = 1;//mList.at(0).toList().size();
    _useRange = _worksheet->querySubObject ("Range(QString)","A2"); // 设置写入的位置
    _useRange = _useRange->querySubObject("Resize(int,int)", _rowCount,_columnCount); // 设置写入区域的大小
    _useRange->setProperty ("Value", mList);       // 可以设置属性的方法写入
    return true;
}
