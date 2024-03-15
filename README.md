## Youliechen(陈友烈) 学习笔记

## 第一二周
《C++ Prime 5th》 和 《Effective Modern C++》的学习笔记，包括
1. 智能指针（基本语法、实现shared_ptr、引用计数的性能、控制块机制、shared_ptr 不能直接管理 this 指针对象、优先使用 make_unique/make_shared 函数）
2. 移动语义move、完美转发语义forward、左值引用右值引用、引用折叠、移动不比拷贝快的情况
3. 拷贝构造+赋值运算符+析构函数+移动构造+移动赋值运算符的三五法则
4. 花括号初始化的细节
5. 虚函数、纯虚函数、虚析构函数、虚函数表
6. 顶底层const 
7. lambda默认捕获模式的问题

## 第三周
《QT 5.9 开发指南》，主要学习 新人checklist里面要求的 （第1~3、4.1、5、8、12.1、16章）。

1-2章： 2个简单的QT项目创建运行的整个过程、Qt项目的目录结构、以及怎么放组件、怎么跳转槽等基础。

3章：
1. QT 的元对象系统 `QObject::metaObject()` `Q_PROPERTY 宏` 
2. `connect()` 两种传参方式、最后一个参数 Qt::ConnectionType type 表示了信号与槽之间的关联方式
3. `sender()`获得信号发射者，同时定义多个控件时，用sender区分当前使用的是哪个控件【比如一个槽函数关联多个信号】
4. 自定义信号 emit
5. 容器类
    51. QList、QLinkedList、QVector
    52. QStack、QQueue
    53. QSet、QHash、QMultiHash 哈希 O(1)
    54. QMap、QMultiMap 红黑树 O(Log N)
    55. 两类迭代器：Java、c++

4.1章： 主要是QString的实用函数
1. QString 转 数字
2. QString 转 小数点格式 4种
3. QString 进制转换
4. 常用函数，如 `s.split(QRegExp("\\s+"), QString::SkipEmptyParts) 分割字符串，返回QStringList`

5章： 5章有三个md，分别是《五章.md》、《QStandardItemModel.md》、《Delegate.md》
1. Model / View / Delegate 的概念，类似于 MVC
2. 三个简单的 Widget ：QListWidget、QTreeWidget、QTableWidget，UI场景不复杂的情况可以不用Model而是用Widget
3. QStringListModel：通常与 QListView 使用，UI效果自然是字符串列表
    ```cpp
    model = new QStringListModel(this); // 创建 QStringListModel
    listView = new QListView(this); // 创建 QListView
    listView->setModel(model); // View 关联 model

    int row = listView->currentIndex().row(); // 鼠标焦点所在的那一行 【其它的Model、View方法不再赘述】
    ```
4. QFileSystemModel、QDirModel【不再使用】，通常与 QTreeView 使用，UI效果是目录树
    QFileSystemModel、QDirModel方法是一样的，QFileSystemModel采用单独的线程获取目录文件结构,而QDirMode不使用单独的线程。使用单独的线程就不会阻碍主线程。

5. QStandardItemModel 【具体的用法见 QStandardItemModel.md 】
    51. 一种二维表格的形式的 dataModel ，可以保存任何类型的内容，比如文本
    52. 通常与 QTableView 【二维表格视图】关联使用
    53. QItemSelectionModel 是一种特殊的 model ， 它的作用是，当鼠标选中【视图表格】里的【某单元格】时，QItemSelectionModel 可以获得【被选中单元格】的 (i, j) 行列坐标。

6. Delegate 
    61. Delegate 的概念
    62. 自定义 Delegate、使用自定义Delegate

8章：
1. 绘图系统，主要是 paintEvent 事件、QPainter 、QPen 、QBrush 的各种方法
2. 坐标系统，平移translate、旋转rotate、缩放scale三个方法

12章：自定义一个UI组件的流程、使用自定义组件

16章：
1. 多语言界面
2. windeployqt 发布EXE程序