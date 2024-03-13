#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->tenButton, &QPushButton::clicked, this, &MainWindow::on_jinzhiButton_clicked);
    connect(ui->twoButton, &QPushButton::clicked, this, &MainWindow::on_jinzhiButton_clicked);
    connect(ui->sixteenButton, SIGNAL(clicked()), this, SLOT(on_jinzhiButton_clicked())); // 两种格式
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    int num = ui->num->text().toInt(); // QString 转 int
    float price = ui->price->text().toFloat(); // QString 转 float
    float allPrice = num * price;
    ui->allPrice->setText(QString::asprintf("%.2F", allPrice));
}

void MainWindow::on_jinzhiButton_clicked()
{
    // 三个按钮信号关联到这同一个槽函数，用 sender() 区分信号发射者
    QPushButton *but = qobject_cast<QPushButton *>(sender());
    int num;
    if (but == ui->tenButton) {
        num = ui->ten->text().toInt();
        ui->two->setText(QString::number(num, 2));
        ui->sixteen->setText(QString::number(num, 16).toUpper());
    } else if (but == ui->twoButton) {
        bool ok;
        num = ui->two->text().toInt(&ok, 2); // 二进制数字的十进制表示
        ui->ten->setText(QString::number(num, 10));
        ui->sixteen->setText(QString::number(num, 16).toUpper());
    } else {
        // 同理
    }
}
