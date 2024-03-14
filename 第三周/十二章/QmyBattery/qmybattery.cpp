#include "qmybattery.h"
#include "ui_qmybattery.h"

QmyBattery::QmyBattery(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::QmyBattery)
{
    ui->setupUi(this);
}

QmyBattery::~QmyBattery()
{
    delete ui;
}

