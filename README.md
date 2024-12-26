# 停车场管理系统

## 目录

- 简介
- 功能
- 安装
- 使用
- 项目结构
- 技术特点
- 贡献
- 许可证

## 简介

停车场管理系统是一个基于 C++ 和 Qt 框架开发的桌面应用程序，旨在实现对停车场车辆的管理，包括车辆的进出记录、停车费用计算、停车场状态记录等功能。该系统可以应用于各种类型的停车场，提高停车场的管理效率和智能化水平。

## 功能

- 车辆管理：记录车辆的进出时间，计算停车费用。
- 停车场管理：管理停车场、等待队列和临时道路的状态。
- 日志记录：记录停车场状态和车辆进出记录。
- Excel 导入导出：将停车记录导出到 Excel 文件或从 Excel 文件导入记录。
- 用户界面：提供友好的图形用户界面，方便用户操作。

## 安装

### 环境要求

- 操作系统：Windows
- 编译器：MinGW 64-bit
- Qt 版本：6.7.2

### 编译步骤

1. 克隆项目代码(确保电脑安装git，并配置好git环境)：
    ```sh
    git clone https://github.com/LieWill/Parking-System.git
    ```

2. 使用 Qt Creator 或者命令行工具进行编译：
    ```sh
    mkdir build
    cd build
    cmake ..
    make
    ```

3. 运行程序：
    ```sh
    ./parking-management-system
    ```

## 使用

### 主界面

主界面包括以下功能按钮：

- **导出EXCEL数据**：将当前的停车记录导出到 Excel 文件。
- **导入EXCEL数据**：从 Excel 文件导入停车记录。
- **车辆进入**：记录车辆进入停车场。
- **车辆离开**：记录车辆离开停车场。

### 车辆管理

1. 点击 **停车** 按钮，输入车辆信息，记录车辆进入时间。
2. 点击 **出车** 按钮，选择离开的车辆，记录车辆离开时间并计算停车费用。

### 日志记录

1. 点击 **导出EXCEL数据** 按钮，将当前的停车记录导出到 Excel 文件。
2. 点击 **导入EXCEL数据** 按钮，从 Excel 文件导入停车记录。

## 项目结构

```
Parking-System/
├── build──├──  Desktop_Qt_6_7_2_MinGW_64_bit-Debug/     # 编译生成的可执行文件
├          └──  Desktop_Qt_6_7_2_MinGW_64_bit-Realease/  # 编译生成的可执行文件
├
├── mainwindows.ui          # 界面的布局
├── car.cpp                 # 车辆类实现文件
├── car.h                   # 车辆类头文件
├── carParking.cpp          # 停车场管理类实现文件
├── carParking.h            # 停车场管理类头文件
├── CMakeLists.txt          # CMake构建配置文件
├── excel.cpp               # Excel操作类实现文件
├── excel.h                 # Excel操作类头文件
├── log.cpp                 # 日志类实现文件
├── log.h                   # 日志类头文件
├── main.cpp                # 主函数实现文件
├── mainwindow.cpp          # 主窗口类实现文件
├── mainwindow.h            # 主窗口类头文件
├── my_queue.cpp            # 队列类实现文件
├── my_queue.hpp            # 队列类头文件
├── my_stack.cpp            # 栈类实现文件
├── my_stack.hpp            # 栈类头文件
├── park.cpp                # 停车场类实现文件
├── park.h                  # 停车场类头文件
├── CONTRIBUTING.md         # 项目开发文档
└── README.md               # 项目说明文档
```

### 主要代码文件介绍

- `car.h` 和 `car.cpp`：定义了车辆类 **Car**，包括车牌号和车辆位置的管理。
- `carParking.h` 和 `carParking.cpp`：定义了停车信息类 **carParking**，继承自 **Car**类，增加了停车时间和费用计算功能。
- `log.h` 和 `log.cpp`：定义了日志类 **log**，用于记录停车场状态和车辆进出记录。
- `excel.h` 和 `excel.cpp`：定义了 Excel 操作类 **excel**，用于将停车记录导出到 Excel 文件或从 Excel 文件导入记录。
- `park.h` 和 `park.cpp`：定义了停车场类 **park**，包括停车场、等待队列和临时道路的管理。
- `my_queue.hpp` 和 `my_queue.cpp`：定义了模板类 **queue**，实现了队列的基本操作。
- `my_stack.hpp` 和 `my_stack.cpp`：定义了模板类 **stack**，实现了栈的基本操作。
- `mainwindow.h` 和 `mainwindow.cpp`：定义了主窗口类 **MainWindow**，实现了用户界面的交互逻辑。
- `main.cpp`：程序入口，初始化应用程序并显示主窗口。

## 技术特点

### C++ 编程语言

使用 C++ 编程语言进行开发，具有高效的性能和丰富的库支持，适合开发高性能的应用程序。

### Qt 框架

使用 Qt 框架进行开发，提供了丰富的 GUI 控件和功能，适合开发桌面应用程序。Qt 的信号与槽机制使得事件处理变得简单高效。

### 模板编程

使用模板编程技术，通过模板类 `queue` 和 `stack` 实现了队列和栈的基本操作，提高了代码的复用性和灵活性。

### 多线程编程

使用多线程编程技术，通过 `std::thread` 实现了多线程操作，提高了程序的响应速度和性能。

### Excel 操作

使用 Qt 的 `QAxObject` 类实现了对 Excel 文件的读写操作，可以方便地将数据导出到 Excel 文件或从 Excel 文件导入数据。

### 日志记录

使用日志记录功能，通过 **log** 类实现停车场状态和车辆进出记录的管理，帮助管理人员了解停车场的使用情况，进行数据分析和决策。

### 用户界面

使用 Qt 的 GUI 控件实现了用户界面，通过 `MainWindow` 类实现用户界面的交互逻辑，提供友好的图形用户界面，方便用户操作。

### 数据结构

使用栈和队列两种数据结构，通过模板类 `stack` 和 `queue` 实现了栈和队列的基本操作，在停车场管理中起到了重要作用，分别用于管理停车场和等待队列。

## 贡献

欢迎贡献代码！请阅读 CONTRIBUTING.md 了解如何参与项目。

## 许可证

本项目使用 MIT 许可证。
