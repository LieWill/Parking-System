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
    saveAction->setStatusTip("淇濆瓨鏁版嵁");
    saveAction->setText("淇濆瓨鏁版嵁");

    importAction->setShortcut(QKeySequence("Ctrl+L"));
    importAction->setStatusTip("瀵煎叆鏁版嵁");
    importAction->setText("瀵煎叆鏁版嵁");

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
        ui->statusbar->showMessage("鍋滆溅鎴愬姛");
        // static QPropertyAnimation *a1 = new QPropertyAnimation(ui->parkButton,"geometry");
        // // a1->setTargetObject(ui->parkButton);
        // // a1->setPropertyName("move");
        // a1->setStartValue(QRect(20,90, 251, 51));
        // a1->setEndValue(QRect(80,360, 251, 51));
        // // 4.璁剧疆鍔ㄧ敾鐨勬椂闂�
        // a1->setDuration(1000);
        // // 5.璁剧疆鍔ㄧ敾鐨勭紦鍜屾洸绾�
        // a1->setEasingCurve(QEasingCurve::Linear);
        // // 6.璁剧疆鍔ㄧ敾鐨勬挱鏀惧懆鏈�
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
    qDebug() << "浣犲ソ";
}

void MainWindow::come(QString& str)
{
    qDebug()<<str;
}

void MainWindow::saveLog()
{
    if(filePath.isEmpty())
    {
        filePath = QFileDialog::getOpenFileName(this,tr("閫夋嫨EXCLE鏂囦欢"),"./",tr("Excel File(*.xls *.xlsx)"));
        if(!filePath.isEmpty())
        {
            ui->lineEdit->setText(filePath);
            ui->statusbar->showMessage("姝ｅ湪淇濆瓨鏁版嵁");
            std::thread t{[this]{
                    Excel = new excel(filePath);
                    Excel->Write(Log.log_out());
                    Excel->save();
                    qDebug() << "鏁版嵁淇濆瓨鎴愬姛";
                    ui->statusbar->showMessage("鏁版嵁淇濆瓨鎴愬姛");
            }};
            t.detach();
        }
        else
        {
            qDebug() << "璇锋纭€夋嫨鏂囦欢澶�";
            ui->statusbar->showMessage("璇锋纭€夋嫨鏂囦欢澶�");
        }

    }
    else
    {
        ui->statusbar->showMessage("姝ｅ湪淇濆瓨鏁版嵁");
        std::thread t{[this]{
            Excel->Write(Log.log_out());
            Excel->save();
            qDebug() << "鏁版嵁淇濆瓨鎴愬姛";
            ui->statusbar->showMessage("鏁版嵁淇濆瓨鎴愬姛");
        }};
        t.detach();
    }
}

void MainWindow::importLog()
{
    qDebug() << "鏁版嵁瀵煎叆鎴愬姛";
}
