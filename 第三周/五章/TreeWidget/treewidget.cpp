#include "treewidget.h"
#include "ui_treewidget.h"

TreeWidget::TreeWidget(QWidget *parent) : QWidget(parent), ui(new Ui::TreeWidget)
{
    ui->setupUi(this);
//    tree = new QTreeWidget(this);
//    tree->setColumnCount(1);

//    QTreeWidgetItem *root = new QTreeWidgetItem(tree, QStringList(QString("Root")));
//    QTreeWidgetItem *leaf = new QTreeWidgetItem(root, QStringList(QString("Leaf 1")));
//    QTreeWidgetItem *leaf2 = new QTreeWidgetItem(root, QStringList(QString("Leaf 2")));
//    leaf2->setCheckState(0, Qt::Checked);

//    root->addChild(leaf);
//    root->addChild(leaf2);

//    QTreeWidgetItem *root2 = new QTreeWidgetItem(tree, QStringList(QStri("root2")));            // 父节点是 tree 【QTreeWidget】
//    QTreeWidgetItem *root2_leaf = new QTreeWidgetItem(root2, QStringList(QString("root2_leaf"))); // 父节点是 root2 【QTreeWidgetItem】
//    root2->addChild(root2_leaf);

//    // 解释：QTreeWidget对象tree是树的总节点，这个总节点下面可以有多个子树【每个子树节点都是QTreeWidgetItem】
//    // 最后，把多个子树的头节点【比如root、root2】放在一个QList里面
//    // insertTopLevelItems方法把QList插入
//    QList<QTreeWidgetItem *> rootList;
//    rootList << root << root2;
//    tree->insertTopLevelItems(0, rootList);

    tree = new QTreeWidget(this);
    tree->setColumnCount(2);

    QStringList headers {"Name", "Number"};
    tree->setHeaderLabels(headers);

    QStringList rootTextList {"Root", "0"};
    QTreeWidgetItem *root = new QTreeWidgetItem(tree, rootTextList);

    QStringList leafTextList {"Leaf 1", "1"};
    QTreeWidgetItem *leaf = new QTreeWidgetItem(root, leafTextList);
    root->addChild(leaf);

    QStringList leaf2TextList {"Leaf 2", "2"};
    QTreeWidgetItem *leaf2 = new QTreeWidgetItem(root, leaf2TextList);
    leaf2->setCheckState(0, Qt::Checked);
    root->addChild(leaf2);

    QList<QTreeWidgetItem *> rootList;
    rootList << root;
    tree->insertTopLevelItems(0, rootList);
}

TreeWidget::~TreeWidget()
{
    delete ui;
}

