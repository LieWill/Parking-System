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
        {
            qDebug() << "请正确选择文件夹";
            ui->statusbar->showMessage("请正确选择文件夹");
        }

    }
    else
    {
        ui->statusbar->showMessage("正在保存数据");
        std::thread t{[this]{
            Excel->Write(Log.log_out());
            Excel->save();
            qDebug() << "数据保存成功";
            ui->statusbar->showMessage("数据保存成功");
        }};
        t.detach();
    }
}

void MainWindow::importLog()
{
    qDebug() << "数据导入成功";
}

void MainWindow::showPark()
{
    size_t num = MyPark.parkNums() % 11;
    for(size_t i = 0; i < num; i++)
    {
        car_park[i]->setText(MyPark.showStack(i).toString());
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
        car_queue[i]->setText(MyPark.showQueue(i).toString());
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
}

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
        static Car here(carPlace::GuangDong,"");
        if(here.getPlace() != sight.getPlace() || \
           here.getPlate_num() != sight.getPlate_num())
        {
            Log.log_in(Car((carPlace)ui->comboBox->currentIndex(),\
                        ui->plateNumEdit->text()));
            ui->statusbar->showMessage("停车成功");
            here = sight;
            state temp = MyPark.in(sight);
            if(temp == state::OK)
            {
                showPark();
            }
            else if(temp == state::park_full)
            {
                showQueue();
            }
        }
        else
        {
            ui->statusbar->showMessage("请勿重复停车");
        }
    }
}

void MainWindow::parkOut()
{
    carParking car;
    state temp = MyPark.out(car);
    if(temp == state::OK)
    {
        showPark();
        showQueue();
        ui->statusbar->showMessage("成功出车" + car.toString());
    }
    else if(temp == state::queue_empty)
    {
        showPark();
        ui->statusbar->showMessage("成功出车" + car.toString());
    }
    else if(temp == state::park_empty)
    {
        ui->statusbar->showMessage("停车场已空");
    }
}
