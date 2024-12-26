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
#include "park.h"

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

private slots:
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
    park MyPark;
    Car carBuffer;
    QPushButton *car_park[10];
    QPushButton *car_queue[10];
    QPushButton *road_way[10];
    void connectUI();
    void parkIn();
    void parkOut();
    void showPark();
    void showQueue();
};
#endif // MAINWINDOW_H
