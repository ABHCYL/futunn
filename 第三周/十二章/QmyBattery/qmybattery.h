#ifndef QMYBATTERY_H
#define QMYBATTERY_H

#include <QWidget>
#include <QColor>

QT_BEGIN_NAMESPACE
namespace Ui { class QmyBattery; }
QT_END_NAMESPACE

class QmyBattery : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(int  powerLevel READ powerLevel WRITE setPowerLevel NOTIFY powerLevelChanged)
signals:
    void   powerLevelChanged(int );
public:
    explicit QmyBattery(QWidget *parent = nullptr);
    ~QmyBattery();
    void    setPowerLevel(int pow);//设置当前电量
    int     powerLevel();
    void    setWarnLevel(int warn);//设置电量低阈值
    int     warnLevel();
    QSize   sizeHint();//报告缺省大小

private:
    Ui::QmyBattery *ui;
    QColor  mColorBack=Qt::white;//背景颜色
        QColor  mColorBorder=Qt::black;//电池边框颜色
        QColor  mColorPower=Qt::green;//电量柱颜色
        QColor  mColorWarning=Qt::red;//电量短缺时的颜色

        int mPowerLevel=60;//电量0-100
        int mWarnLevel=20;//电量低警示阈值
public slots:
};
#endif // QMYBATTERY_H
