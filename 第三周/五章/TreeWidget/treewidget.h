#ifndef TREEWIDGET_H
#define TREEWIDGET_H

#include <QWidget>
#include <QTreeWidget>


QT_BEGIN_NAMESPACE
namespace Ui { class TreeWidget; }
QT_END_NAMESPACE

class TreeWidget : public QWidget
{
    Q_OBJECT

public:
    TreeWidget(QWidget *parent = nullptr);
    ~TreeWidget();

private:
    QTreeWidget *tree; //
    Ui::TreeWidget *ui;
};
#endif // TREEWIDGET_H
