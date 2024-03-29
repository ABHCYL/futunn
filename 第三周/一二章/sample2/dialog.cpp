#include "dialog.h"
#include "ui_dialog.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>

Dialog::Dialog(QWidget *parent) : QDialog(parent)
{
    iniUI();
    iniSignalSlots();
    setWindowTitle("富途实习QT例子2代码化设计UI");
}
Dialog::~Dialog() {}

void Dialog::on_chkBoxUnder(bool checked)
{
    QFont font = txtEdit->font();
    font.setUnderline(checked);
    txtEdit->setFont(font);
}

void Dialog::on_chkBoxItalic(bool checked)
{
    QFont font = txtEdit->font();
    font.setItalic(checked);
    txtEdit->setFont(font);
}

void Dialog::on_chkBoxBold(bool checked)
{
    QFont font = txtEdit->font();
    font.setBold(checked);
    txtEdit->setFont(font);
}

void Dialog::setTextFontColor()
{
    QPalette plet = txtEdit->palette();
    if (rBtnBlue->isChecked())
        plet.setColor(QPalette::Text, Qt::blue);
    else if (rBtnRed->isChecked())
        plet.setColor(QPalette::Text, Qt::red);
    else if (rBtnBlack->isChecked())
        plet.setColor(QPalette::Text, Qt::black);
    else
        plet.setColor(QPalette::Text, Qt::black);

    txtEdit->setPalette(plet);
}

void Dialog::iniUI()
{
    // 创建 Underline, Italic, Bold三个CheckBox，并水平布局
    chkBoxUnder = new QCheckBox(tr("Underline"));
    chkBoxItalic = new QCheckBox(tr("Italic"));
    chkBoxBold = new QCheckBox(tr("Bold"));
    QHBoxLayout *HLay1 = new QHBoxLayout;
    HLay1->addWidget(chkBoxUnder);
    HLay1->addWidget(chkBoxItalic);
    HLay1->addWidget(chkBoxBold);

    // 创建 Black, Red, Blue三个RadioButton，并水平布局
    rBtnBlack = new QRadioButton(tr("Black"));
    rBtnBlack->setChecked(true); // 缺省被选中
    rBtnRed = new QRadioButton(tr("Red"));
    rBtnBlue = new QRadioButton(tr("Blue"));
    QHBoxLayout *HLay2 = new QHBoxLayout;
    HLay2->addWidget(rBtnBlack);
    HLay2->addWidget(rBtnRed);
    HLay2->addWidget(rBtnBlue);

    // 创建 确定, 取消, 退出 三个 QPushButton, 并水平布局
    btnOK = new QPushButton(tr("确定"));
    btnCancel = new QPushButton(tr("取消"));
    btnClose = new QPushButton(tr("退出"));

    QHBoxLayout *HLay3 = new QHBoxLayout;
    HLay3->addStretch();
    HLay3->addWidget(btnOK);
    HLay3->addWidget(btnCancel);
    HLay3->addStretch();
    HLay3->addWidget(btnClose);

    // 创建文本框,并设置初始字体
    txtEdit = new QPlainTextEdit;
    txtEdit->setPlainText("富途NN");

    QFont font = txtEdit->font();
    font.setPointSize(20);
    txtEdit->setFont(font);

    // 创建垂直布局，并设置为主布局
    QVBoxLayout *VLay = new QVBoxLayout;
    VLay->addLayout(HLay1);   // 添加字体类型组
    VLay->addLayout(HLay2);   // 添加字体颜色组
    VLay->addWidget(txtEdit); // 添加PlainTextEdit
    VLay->addLayout(HLay3);   // 添加按键组

    setLayout(VLay); // 设置为窗体的主布局
}

void Dialog::iniSignalSlots()
{
    // 颜色radiobutton
    connect(rBtnRed, SIGNAL(clicked()), this, SLOT(setTextFontColor()));
    connect(rBtnBlue, SIGNAL(clicked()), this, SLOT(setTextFontColor()));
    connect(rBtnBlack, SIGNAL(clicked()), this, SLOT(setTextFontColor()));

    // 字体设置的QCheckBox 的clicked(bool)事件与 相应的槽函数关联
    connect(chkBoxUnder, SIGNAL(clicked(bool)), this, SLOT(on_chkBoxUnder(bool)));
    connect(chkBoxItalic, SIGNAL(clicked(bool)), this, SLOT(on_chkBoxItalic(bool)));
    connect(chkBoxBold, SIGNAL(clicked(bool)), this, SLOT(on_chkBoxBold(bool)));

    // 按键与窗体的槽函数关联
    connect(btnOK, SIGNAL(clicked()), this, SLOT(accept()));
    connect(btnCancel, SIGNAL(clicked()), this, SLOT(reject()));
    connect(btnClose, SIGNAL(clicked()), this, SLOT(close()));
}
