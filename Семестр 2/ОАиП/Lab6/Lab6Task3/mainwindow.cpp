#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QInputDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    bool ok;
    int key = QInputDialog::getInt(this, tr("Add pair"),
                                         tr("Choose key"), 0, 0, INT32_MAX, 1, &ok);
    if (!ok) return;
    QString val = QInputDialog::getText(this, tr("Add pair"),
                                         tr("Choose value"), QLineEdit::Normal,
                                         QString(), &ok);
    if (!ok) return;
    table.insert(key, val.toStdString());
}

void MainWindow::on_pushButton_2_clicked()
{
    QMessageBox msg;
    msg.setText(QString::fromStdString(table.min_key()));
    msg.exec();
}


void MainWindow::on_pushButton_3_clicked()
{
    bool ok;
    int key = QInputDialog::getInt(this, tr("Delete pair"),
                                         tr("Choose key to remove"), 0, 0, INT32_MAX, 1, &ok);
    if (!ok) return;
    table.remove(key);
}
