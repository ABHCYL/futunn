#ifndef MYFILESYSTEMMODEL_H
#define MYFILESYSTEMMODEL_H

#include <QWidget>
#include <QFileSystemModel>
#include <QTreeView>
#include <QHBoxLayout>
#include <QPushButton>
#include <QHeaderView>
#include <QInputDialog>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class MyFileSystemModel; }
QT_END_NAMESPACE

class MyFileSystemModel : public QWidget
{
    Q_OBJECT

public:
    MyFileSystemModel(QWidget *parent = nullptr);
    ~MyFileSystemModel();

private:
    QFileSystemModel *model;
    QTreeView *treeView;
    Ui::MyFileSystemModel *ui;
private slots:
        void mkdir();
        void rm();
};
#endif // MYFILESYSTEMMODEL_H
