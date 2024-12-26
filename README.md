# 项目文档

## 简介
本项目是一个基于QT框架开发的停车场管理系统。该系统旨在帮助停车场管理员高效地管理停车场的车辆进出、收费以及数据记录等工作。

## 功能模块
- 车辆管理：记录车辆的进入和离开时间，计算停车费用。
- 停车场管理：管理停车场的停车位状态，实时更新空余停车位数量。
- 数据记录：记录停车场的停车记录和收费信息，并支持导出为Excel文件。
- 日志管理：记录系统的操作日志，便于追踪和审计。

## 文件结构
```
park2/
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
└── README.md               # 项目说明文档
```

## 主要类说明
- `Car`：车辆类，包含车辆的基本信息如车牌号、车型等。
- `carParking`：停车场管理类，包含停车场的停车信息管理，如停车时间、费用计算等。
- `excel`：Excel操作类，用于读取和写入Excel文件，记录停车数据和收费信息。
- `log`：日志类，用于记录系统的操作日志。
- `MainWindow`：主窗口类，是用户与系统交互的主要界面。

## 使用说明
1. 克隆项目到本地环境。
2. 使用CMake构建项目，生成可执行文件。
3. 运行程序，进入主窗口界面。
4. 通过主窗口界面进行车辆的进出管理、停车费用计算和数据记录等操作。

## 开发环境
- QT框架
- MingW编译器,13.1版本以上

## 贡献者
- 项目由团队共同开发，感谢所有参与贡献的成员。

## 许可证
本项目遵循MIT许可证。请查看LICENSE文件了解更多信息。

## 联系方式
如有任何问题或建议，请通过项目的issue跟踪器与我们联系。

---

请注意，本README文件中已删除所有个人可识别信息（PII）和网站超链接，以保护隐私并避免潜在的安全风险。
