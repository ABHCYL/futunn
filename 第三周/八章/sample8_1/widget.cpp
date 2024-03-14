#include "widget.h"
#include "ui_widget.h"

#include <QPainter>

void Widget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);//创建QPainter对象
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::TextAntialiasing);

    int W = this->width(); //绘图区宽度
    int H = this->height(); //绘图区高度
    QRect rect(W/4,H/4,W/2,H/2); //中间区域矩形框

    QPen pen;
    pen.setWidth(3); //线宽
    pen.setColor(Qt::red); //划线颜色
    pen.setStyle(Qt::SolidLine);//线的类型，实线、虚线等
    pen.setCapStyle(Qt::FlatCap);//线端点样式
    pen.setJoinStyle(Qt::BevelJoin);//线的连接点样式
    painter.setPen(pen);

    // 设置画刷
    QPixmap texturePixmap(":images/ft.jpg");

    QBrush  brush;
    brush.setStyle(Qt::SolidPattern); //画刷填充样式
    painter.setBrush(brush);

    painter.drawRect(rect);
}

Widget::Widget(QWidget *parent) :QWidget(parent),ui(new Ui::Widget)
{
    ui->setupUi(this);

    setPalette(QPalette(Qt::white));//设置窗口为白色背景
    setAutoFillBackground(true);
    this->resize(400,400);
}

Widget::~Widget()
{
    delete ui;
}
