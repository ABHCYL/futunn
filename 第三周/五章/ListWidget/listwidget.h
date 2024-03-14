#ifndef LISTWIDGET_H
#define LISTWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QListWidget>
#include <QHBoxLayout>


QT_BEGIN_NAMESPACE
namespace Ui { class ListWidget; }
QT_END_NAMESPACE

class ListWidget : public QWidget
{
    Q_OBJECT

public:
    ListWidget(QWidget *parent = nullptr);
    ~ListWidget();

private:
    QLabel *label;
    QListWidget *list;

    Ui::ListWidget *ui;
};
#endif // LISTWIDGET_H
