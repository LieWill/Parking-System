#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "QListView"
#include "QtAxContainer/QAxObject"
#include "car.h"
#include "excel.h"
#include "QFileDialog"
#include <thread>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , MyPark(10)
{
    new QAxObject("Word.Application");
    ui->setupUi(this);
    connectUI();
    connect(this, SIGNAL(signal1()),this,SLOT(slot()));
    signal1();

    saveAction = new QAction(ui->menuFile);
    importAction = new QAction(ui->menuFile);

    saveAction->setShortcut(QKeySequence("Ctrl+S"));
    saveAction->setStatusTip("保存数据");
    saveAction->setText("保存数据");

    importAction->setShortcut(QKeySequence("Ctrl+L"));
    importAction->setStatusTip("导入数据");
    importAction->setText("导入数据");

    ui->menuFile->addAction(saveAction);
    ui->menuFile->addAction(importAction);
    ui->filePathEditor->setPlaceholderText("请选择要保存的数据文件路径");
    ui->plateNumEdit->setPlaceholderText("输入车牌号");

    ui->filePathEditor->setValidator(new QRegularExpressionValidator(QRegularExpression \
    ("^(?:(?:[a-zA-Z]:|\\.{1,2})?[\\\\/](?:[^\\\\?/*|<>:\"]+[\\\\/])*)(?:(?:[^\\\\?/*|<>:\"]+?)(?:\\.[^.\\\\?/*|<>:\"]+)?)?$")));
    ui->plateNumEdit->setValidator(new QRegularExpressionValidator(QRegularExpression("^(?![0-9]+$)(?![A-Z]+$)[0-9A-Z]{6,7}$")));

    connect(saveAction, &QAction::triggered, this, &MainWindow::saveLog);
    connect(importAction, &QAction::triggered, this, &MainWindow::importLog);
    connect(ui->randomButton,&QPushButton::clicked,this,[this](){
        Car rand;
        rand.show();
        ui->comboBox->setCurrentIndex((int)rand.getPlace());
        ui->plateNumEdit->setText(rand.getPlate_num());
    });
    connect(ui->parkButton, &QPushButton::clicked,this, &MainWindow::parkIn);
    connect(ui->out,  &QPushButton::clicked,this, &MainWindow::parkOut);
    // static QPropertyAnimation *a1 = new QPropertyAnimation(ui->parkButton,"geometry");
    // // a1->setTargetObject(ui->parkButton);
    // // a1->setPropertyName("move");
    // a1->setStartValue(QRect(20,90, 251, 51));
    // a1->setEndValue(QRect(80,360, 251, 51));
    // // 4.设置动画的时间
    // a1->setDuration(1000);
    // // 5.设置动画的缓和曲线
    // a1->setEasingCurve(QEasingCurve::Linear);
    // // 6.设置动画的播放周期
    // a1->setLoopCount(1);
    // a1->start();
    extern const QString setStatusTip[34];
    for(int i = 0; i < 34; i++)
        ui->comboBox->addItem(' ' +setStatusTip[i]);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete saveAction;
    delete importAction;
    std::thread t{[this]{
        if(Excel != nullptr)
            delete Excel;
    }};
    t.join();
}

void MainWindow::slot()
{
    qDebug() << "你好";
}

void MainWindow::come(QString& str)
{
    qDebug()<<str;
}

void MainWindow::saveLog()
{
    if(filePath.isEmpty())
    {
        filePath = QFileDialog::getOpenFileName(this,tr("选择EXCLE文件"),"./",tr("Excel File(*.xls *.xlsx)"));
        if(!filePath.isEmpty())
        {
            ui->filePathEditor->setText(filePath);
            ui->statusbar->showMessage("正在保存数据");
            std::thread t{[this]{
                    Excel = new excel(filePath);
                    Excel->Write(Log.log_out());
                    Excel->save();
                    qDebug() << "数据保存成功";
                    ui->statusbar->showMessage("数据保存成功");
            }};
            t.detach();
        }
        else
            ui->statusbar->showMessage("请正确选择文件夹");
    }
    else
    {
        ui->statusbar->showMessage("正在保存数据");
        std::thread t{[this]{
            Excel->Write(Log.log_out());
            Excel->save();
            ui->statusbar->showMessage("数据保存成功");
        }};
        t.detach();
    }
}

void MainWindow::importLog()
{
    ui->log->append("数据导入成功");
}

void MainWindow::showPark()
{
    size_t num = MyPark.parkNums() % 11;
    for(size_t i = 0; i < num; i++)
    {
        car_park[i]->setText(MyPark.getStack(i).toString());
    }
    for(size_t i = num; i < 10; i++)
    {
        car_park[i]->setText("");
    }
}

void MainWindow::showQueue()
{
    size_t num = MyPark.queueNum() % 11;
    for(size_t i = 0; i < num; i++)
    {
        car_queue[i]->setText(MyPark.getQueue(i).toString());
    }
    for(size_t i = num; i < 10; i++)
    {
        car_queue[i]->setText("");
    }
}

void MainWindow::connectUI()
{
    car_park[0] = ui->park_1;
    car_park[1] = ui->park_2;
    car_park[2] = ui->park_3;
    car_park[3] = ui->park_4;
    car_park[4] = ui->park_5;
    car_park[5] = ui->park_6;
    car_park[6] = ui->park_7;
    car_park[7] = ui->park_8;
    car_park[8] = ui->park_9;
    car_park[9] = ui->park_10;

    car_queue[0] = ui->queue_10;
    car_queue[1] = ui->queue_9;
    car_queue[2] = ui->queue_8;
    car_queue[3] = ui->queue_7;
    car_queue[4] = ui->queue_6;
    car_queue[5] = ui->queue_5;
    car_queue[6] = ui->queue_4;
    car_queue[7] = ui->queue_3;
    car_queue[8] = ui->queue_2;
    car_queue[9] = ui->queue_1;

    for(int i = 0; i < 10; i++)
    {
        connect(car_park[i], &QPushButton::clicked, this, [=]{
            ui->comboBox->setCurrentIndex((int)(MyPark.getStack(i).getPlace()));
            ui->plateNumEdit->setText(MyPark.getStack(i).getPlate_num());
        });
        connect(car_queue[i], &QPushButton::clicked, this, [=]{
            ui->comboBox->setCurrentIndex((int)(MyPark.getQueue(i).getPlace()));
            ui->plateNumEdit->setText(MyPark.getQueue(i).getPlate_num());
        });
    }
}

static int stackTop = 0;  // TODO 待解决
static int queueTop = 0;
void MainWindow::parkIn()
{
    Car sight((carPlace)ui->comboBox->currentIndex(),\
        ui->plateNumEdit->text());
    if(sight.getPlate_num().isEmpty())
    {
        ui->statusbar->showMessage("请写车牌号");
    }
    else
    {
        if(!MyPark.find(sight))  //看看这个车在不在停车场
        {
            Log.log_in(sight);
            switch(MyPark.in(sight))
            {
            case state::OK:
                car_park[stackTop++]->setEnabled(true);
                ui->log->append(sight.toString() + "成功停入停车场\n");
                showPark();
                break;
            case state::park_full:
                car_queue[queueTop++]->setEnabled(true);
                ui->log->append(sight.toString() + "驶入等候区\n");
                showQueue();
                break;
            case state::queue_full:
                ui->statusbar->showMessage("等候区已满，无法停车\n",1000);
                break;
            default:
                break;
            }
        }
        else
            ui->statusbar->showMessage("请勿重复停车",1000);
    }
}

void MainWindow::parkOut()
{
    carParking car((carPlace)ui->comboBox->currentIndex(),\
                   ui->plateNumEdit->text());
    switch(MyPark.out(car))
    {
    case state::OK:
        showPark();
        showQueue();
        ui->log->append("出车成功:" + car.toString() + "\nin:" = car.getInTime().toString() + "\nout" + car.getOutTime().toString() + '\n');
        break;
    case state::queue_empty:
        showPark();
        ui->log->append("出车成功:" + car.toString() + "\nin:" = car.getInTime().toString() + "\nout" + car.getOutTime().toString() + '\n');
        break;
    case state::park_empty:
        ui->statusbar->showMessage("停车场已空", 1000);
        break;
    case state::no_find:
        ui->statusbar->showMessage("没有找到这辆车哦！", 1000);
        break;
    default:
        break;
    }
}
