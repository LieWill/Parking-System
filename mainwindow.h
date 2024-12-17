#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QDebug"
#include "QPushButton"
#include "QPropertyAnimation"
#include "QAction"
#include "log.h"
#include "excel.h"
#include <QPropertyAnimation>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void signal1();
    void signal2();
    void come1(QString& str);
    void come2(QString& str);
    void come3(QString& str);


private slots:
    void slot();
    void come(QString& str);
    void saveLog();    // 保存数据
    void importLog();    // 导入数据

private:
    Ui::MainWindow *ui;
    QAction *saveAction;
    QAction *importAction;
    QString filePath;
    class log Log;
    excel *Excel = nullptr;
    bool exit = false;
};
#endif // MAINWINDOW_H
