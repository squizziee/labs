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

void MainWindow::update_ui() {
    ui->lineEdit->clear();
    QString text;
    for (size_t i = 0; i < dq.get_size(); i++) {
        text += QString::number(dq[i]) + " ";
    }
    ui->lineEdit->setText(text);
}

void MainWindow::on_pushButton_clicked()
{
    bool ok;
    int element = QInputDialog::getInt(this, tr("push_back"),
                                      tr("Value"), 1, INT32_MIN, INT32_MAX, 1, &ok);
    if (!ok) {
        return;
    }
    dq.push_back(element);
    update_ui();
}


void MainWindow::on_pushButton_2_clicked()
{
    dq.pop_back();
    update_ui();
}


void MainWindow::on_pushButton_4_clicked()
{
    bool ok;
    int element = QInputDialog::getInt(this, tr("push_back"),
                                      tr("Value"), 1, INT32_MIN, INT32_MAX, 1, &ok);
    if (!ok) {
        return;
    }
    dq.push_front(element);
    update_ui();
}


void MainWindow::on_pushButton_3_clicked()
{
    dq.pop_front();
    update_ui();
}


void MainWindow::on_pushButton_5_clicked()
{
    QMessageBox msg;
    msg.setText("size: " + QString::number(dq.get_size()));
    msg.exec();
}


void MainWindow::on_pushButton_6_clicked()
{
    QMessageBox msg;
    msg.setText("empty: " + QString(dq.empty()? "true" : "false"));
    msg.exec();
}


void MainWindow::on_pushButton_7_clicked()
{
    dq.clear();
    update_ui();
}

