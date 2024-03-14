#ifndef TABLEWIDGET_H
#define TABLEWIDGET_H

#include <QWidget>
#include <QTableWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class TableWidget; }
QT_END_NAMESPACE

class TableWidget : public QWidget
{
    Q_OBJECT

public:
    TableWidget(QWidget *parent = nullptr);
    ~TableWidget();

private:
    QTableWidget *table;
    Ui::TableWidget *ui;
};
#endif // TABLEWIDGET_H
