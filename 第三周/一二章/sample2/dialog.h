#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QCheckBox>
#include <QRadioButton>
#include <QPlainTextEdit>


QT_BEGIN_NAMESPACE
namespace Ui { class Dialog; }
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();
private slots:
    void on_chkBoxUnder(bool checked);//Underline的槽函数
    void on_chkBoxItalic(bool checked);//Italic的槽函数
    void on_chkBoxBold(bool checked);//Bold的棒函数
    void setTextFontColor();//设置字体颜色
private:

    QCheckBox  *chkBoxUnder;
    QCheckBox  *chkBoxItalic;
    QCheckBox  *chkBoxBold;
    QRadioButton  * rBtnBlack;
    QRadioButton  * rBtnRed;
    QRadioButton  * rBtnBlue;
    QPlainTextEdit  *txtEdit;
    QPushButton  *btnOK;
    QPushButton  *btnCancel;
    QPushButton  *btnClose;
    void  iniUI(); //UI创建与初始化
    void  iniSignalSlots();//初始化信号与槽的链接
};
#endif // DIALOG_H
