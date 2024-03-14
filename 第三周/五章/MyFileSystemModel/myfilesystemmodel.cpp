#include "myfilesystemmodel.h"
#include "ui_myfilesystemmodel.h"

MyFileSystemModel::MyFileSystemModel(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MyFileSystemModel)
{
    ui->setupUi(this);
    model = new QFileSystemModel;
    model->setReadOnly(false);


    treeView = new QTreeView;
    treeView->setModel(model); // view 关联 model
    treeView->header()->setStretchLastSection(true);
    treeView->header()->setSortIndicator(0, Qt::AscendingOrder);
    treeView->header()->setSortIndicatorShown(true);

    QModelIndex index = model->index(QDir::currentPath()); // QDir::currentPath()获取当前 exe 文件运行时路径，并把这个路径当成程序启动时显示的路径。
    treeView->expand(index); // expand()函数即展开这一路径
    treeView->scrollTo(index); // scrollTo()函数是把视图的视口滚动到这个路径的位置
    treeView->resizeColumnToContents(0); // resizeColumnToContents()是要求把列头适应内容的宽度，也就是不产生...符号

    QHBoxLayout *btnLayout = new QHBoxLayout;
    QPushButton *createBtn = new QPushButton(tr("Create Directory..."));
    QPushButton *delBtn = new QPushButton(tr("Remove"));
    btnLayout->addWidget(createBtn);
    btnLayout->addWidget(delBtn);
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(treeView);
    mainLayout->addLayout(btnLayout);
    this->setLayout(mainLayout);

    connect(createBtn, SIGNAL(clicked()), this, SLOT(mkdir()));
    connect(delBtn, SIGNAL(clicked()), this, SLOT(rm()));
}

MyFileSystemModel::~MyFileSystemModel()
{
    delete ui;
}

void MyFileSystemModel::mkdir()
{
    QModelIndex index = treeView->currentIndex();
    if (!index.isValid()) return;

    QString dirName = QInputDialog::getText(this, tr("Create Directory"), tr("Directory name"));
    if (!dirName.isEmpty())
    {
        if (!model->mkdir(index, dirName).isValid())
        {
            QMessageBox::information(this, tr("Create Directory"), tr("Failed to create the directory"));
        }
    }
}
void MyFileSystemModel::rm()
{
    QModelIndex index = treeView->currentIndex();
    if (!index.isValid()) return;

    bool ok;
    if (model->fileInfo(index).isDir()) ok = model->rmdir(index);
    else ok = model->remove(index);

    if (!ok) QMessageBox::information(this, tr("Remove"), tr("Failed to remove %1").arg(model->fileName(index)));
}
