#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    Ui::Widget *ui;
    void    myDrawFilledRect();
    void    myDrawTextureRect();
    void    myDrawGradient();

    void    total();
    void    myDrawShape(); //绘制基本图形
protected:
    void    paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
};
#endif // WIDGET_H
