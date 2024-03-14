#include "listwidget.h"
#include "ui_listwidget.h"

ListWidget::ListWidget(QWidget *parent): QWidget(parent), ui(new Ui::ListWidget)
{
    ui->setupUi(this);
    label = new QLabel;
    label->setFixedWidth(70);
    list = new QListWidget;
    list->addItem(new QListWidgetItem(QIcon(":/images/line.PNG"), tr("Line")));
    list->addItem(new QListWidgetItem(QIcon(":/images/rect.PNG"), tr("Rectangle")));
    list->addItem(new QListWidgetItem(QIcon(":/images/oval.PNG"), tr("Oval")));
    list->addItem(new QListWidgetItem(QIcon(":/images/tri.PNG"), tr("Triangle")));
    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(label);
    layout->addWidget(list);

    setLayout(layout);

    // QListWidget 对象 list 发出 currentTextChanged 信号 到 label，执行 setText槽函数
    connect(list, SIGNAL(currentTextChanged(QString)), label, SLOT(setText(QString)));
}

ListWidget::~ListWidget()
{
    delete ui;
}

