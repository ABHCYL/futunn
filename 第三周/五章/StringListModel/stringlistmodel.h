#ifndef STRINGLISTMODEL_H
#define STRINGLISTMODEL_H

#include <QWidget>
#include <QListView>
#include <QStringListModel>

QT_BEGIN_NAMESPACE
namespace Ui { class StringListModel; }
QT_END_NAMESPACE

class StringListModel : public QWidget
{
    Q_OBJECT

public:
    StringListModel(QWidget *parent = nullptr);
    ~StringListModel();

private:
    Ui::StringListModel *ui;
    QStringListModel *model; // model
    QListView *listView; // 视图
private slots:
        void insertData();
        void deleteData();
        void showData();
};
#endif // STRINGLISTMODEL_H
