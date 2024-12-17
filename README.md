停车系统是一个用于管理停车场的应用程序。它提供了用户界面，允许用户查看和管理停车场中的车辆信息。该系统包括以下主要功能：

车辆的进入和离开
车辆信息的记录和显示
车辆信息的导入和导出

功能
车辆的进入和离开
车辆可以通过输入车牌号来进入停车场。系统会记录车辆进入的时间，并显示在用户界面上。当车辆离开时，系统会计算停车时间并显示在用户界面上。

车辆信息的记录和显示
系统会记录所有进入和离开的车辆信息，包括车牌号、进入时间和离开时间。这些信息可以通过用户界面查看。

车辆信息的导入和导出
系统可以导入和导出车辆信息到Excel文件中。用户可以导出当前停车场中的所有车辆信息，也可以导入之前导出的车辆信息。

使用方法
运行应用程序。
在用户界面上输入车牌号，点击“进入”按钮，车辆进入停车场。
在用户界面上输入车牌号，点击“离开”按钮，车辆离开停车场。
在用户界面上点击“导入”按钮，选择要导入的Excel文件。
在用户界面上点击“导出”按钮，选择要导出的Excel文件。
文件结构

car.cpp和car.h：定义了车辆类，包括车辆的基本信息和操作。
parkingtime.cpp和parkingtime.h：定义了停车时间类，用于计算停车时间。
log.cpp和log.h：定义了日志类，用于记录车辆进入和离开的信息。
park.cpp和park.h：定义了停车场类，用于管理停车场的车辆信息。
excel.cpp和excel.h：定义了Excel类，用于导入和导出车辆信息到Excel文件中。
main.cpp：应用程序的入口点。
mainwindow.cpp和mainwindow.h：定义了主窗口类，包括用户界面的设计和功能实现。

注意事项
请确保在使用应用程序之前已经安装了Qt库。
请确保在使用应用程序之前已经安装了Excel软件。

版权声明
本应用程序遵循MIT许可证。有关详细信息，请参阅LICENSE文件。