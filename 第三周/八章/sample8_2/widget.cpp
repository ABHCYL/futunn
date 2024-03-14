#include "widget.h"
#include "ui_widget.h"
#include <QPainter>
#include <cmath>

Widget::Widget(QWidget *parent): QWidget(parent), ui(new Ui::Widget)
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

void Widget::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::TextAntialiasing);

    QFont font;
    font.setBold(true);
    font.setPointSize(12);
    painter.setFont(font);

    QPen pen;
    pen.setWidth(3);
    pen.setColor(Qt::red);
    pen.setStyle(Qt::SolidLine);
    pen.setCapStyle(Qt::FlatCap);
    pen.setJoinStyle(Qt::BevelJoin);
    painter.setPen(pen);

    QBrush  brush;
    brush.setColor(Qt::yellow);
    brush.setStyle(Qt::SolidPattern);
    painter.setBrush(brush);
// 下面是新增的，上面和之前一样
    // 五角星 5个顶点坐标，原点在星星的中心
    qreal R = 100; // qreal == double
    const qreal PI = 3.14;
    qreal deg = PI *72 / 180;
    QPoint points[] = {
        QPoint(R, 0),
        QPoint(R*std::cos(deg), -R * std::sin(deg)),
        QPoint(R*std::cos(deg*2), -R * std::sin(deg*2)),
        QPoint(R*std::cos(deg*3), -R * std::sin(deg*3)),
        QPoint(R*std::cos(deg*4), -R * std::sin(deg*4)),
    };

    // 设计绘制五角星的PainterPath,以便重复使用
    QPainterPath starPath;
    starPath.moveTo(points[0]);
    starPath.lineTo(points[2]);
    starPath.lineTo(points[4]);
    starPath.lineTo(points[1]);
    starPath.lineTo(points[3]);
    starPath.closeSubpath(); // 闭合路径,最后一个点与第一个点相连
    starPath.addText(points[0], font, "0"); // 显示:端点编号
    starPath.addText(points[1], font, "1");
    starPath.addText(points[2], font, "2");
    starPath.addText(points[3], font, "3");
    starPath.addText(points[4], font,"4");

    painter.save();
    painter.translate(100, 120);
    painter.drawPath(starPath);
    painter.drawText(0, 0, "S1");
    painter.restore();//恢复坐标状态
    painter.translate(300,120);//平移
    painter.scale(0.8,0.8);//缩放
    painter.rotate(90);//顺时针旋转90度
    painter.drawPath(starPath);//画星星
    painter.drawText(0,0, "S2");
    painter.resetTransform();//复位所有坐标变换
    painter.translate(500,120);//平移
    painter.rotate(-145);//逆时针旋转145度
    painter.drawPath(starPath);//画星星
    painter.drawText(0,0, "S3");

}
