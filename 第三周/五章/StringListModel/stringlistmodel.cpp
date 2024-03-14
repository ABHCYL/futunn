#include "stringlistmodel.h"
#include "ui_stringlistmodel.h"

#include <QHBoxLayout>
#include <QPushButton>
#include <QMessageBox>
#include <QInputDialog>


StringListModel::StringListModel(QWidget *parent) : QWidget(parent), ui(new Ui::StringListModel)
{
    ui->setupUi(this);
    QStringList data;
    data << "Letter A" << "Letter B" << "Letter C";


    listView = new QListView(this); // 创建 QListView
    model = new QStringListModel(this); // 创建 QStringListModel
    model->setStringList(data); // model 初始化原始值 A B C
    listView->setModel(model); // View 关联 model

    QPushButton *insertBtn = new QPushButton(tr("insert"), this);
    QPushButton *delBtn = new QPushButton(tr("Delete"), this);
    QPushButton *showBtn = new QPushButton(tr("Show"), this);

    QHBoxLayout *btnLayout = new QHBoxLayout;
    btnLayout->addWidget(insertBtn);
    btnLayout->addWidget(delBtn);
    btnLayout->addWidget(showBtn);
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(listView);
    mainLayout->addLayout(btnLayout);
    this->setLayout(mainLayout);

    connect(insertBtn, SIGNAL(clicked()), this, SLOT(insertData()));
    connect(delBtn, SIGNAL(clicked()), this, SLOT(deleteData()));
    connect(showBtn, SIGNAL(clicked()), this, SLOT(showData()));
}

StringListModel::~StringListModel()
{
    delete ui;
}

void StringListModel::insertData()
{
    bool isOK;
    QString text = QInputDialog::getText(NULL, "Insert", "Please input new data:", QLineEdit::Normal, "You are inserting new data.", &isOK);
    if (isOK)
    {
        int row = listView->currentIndex().row(); // 鼠标焦点所在的那一行
        model->insertRows(row, 1);                // 在这一行下面插入1行
        QModelIndex index = model->index(row);
        model->setData(index, text);
        listView->setCurrentIndex(index);
        listView->edit(index);
    }
}

void StringListModel::deleteData()
{
    if (model->rowCount() > 1)
        model->removeRows(listView->currentIndex().row(), 1);
}

void StringListModel::showData()
{
    QStringList data = model->stringList();
    QString str;
    foreach (QString s, data)
        str += s + "\n";
    QMessageBox::information(this, "Data", str);
}
