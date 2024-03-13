#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <string>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->red, SIGNAL(clicked()), this, SLOT(setTextFontColor()));
    connect(ui->green, SIGNAL(clicked()), this, SLOT(setTextFontColor()));
    connect(ui->blue, SIGNAL(clicked()), this, SLOT(setTextFontColor()));
    // sender(发信号的组件), signal, receiver(this), method(槽函数)
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setTextFontColor()
{
    // 自定义槽函数，不会在 ui->setupUi(this); 中自动关联信号与槽【VS都是这样】
    // 构造函数 Widget() 中手动调用 connect 关联
    QPalette palette = ui->textEdit->palette();
    if (ui->red->isChecked())
        palette.setColor(QPalette::Text, Qt::red);
    else if (ui->green->isChecked())
        palette.setColor(QPalette::Text, Qt::green);
    else if (ui->blue->isChecked())
        palette.setColor(QPalette::Text, Qt::blue);

    ui->textEdit->setPalette(palette);
}
