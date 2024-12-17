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
{
    new QAxObject("Word.Application");
    ui->setupUi(this);
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

    connect(saveAction, &QAction::triggered, this, &MainWindow::saveLog);
    connect(importAction, &QAction::triggered, this, &MainWindow::importLog);
    connect(ui->randomButton,&QPushButton::clicked,this,[this](){
        Car rand;
        rand.show();
        ui->comboBox->setCurrentIndex((int)rand.getPlace());
        ui->plateNumEdit->setText(rand.getPlate_num());
        Log.log_in(rand);
    });
    connect(ui->parkButton,&QPushButton::clicked,this,[this]{
        ui->statusbar->showMessage("停车成功");
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
    });
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
            ui->lineEdit->setText(filePath);
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