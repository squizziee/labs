#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Vector.h"
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


void MainWindow::on_capacityBtn_clicked()
{
    ui->lineEdit->setText(QString::number(vector.getCapacity()));
}


void MainWindow::printVector() {
    std::string text;
    for (int i : vector) {
        text += std::to_string(i);
        text += ", ";
    }
    ui->lineEdit->setText(QString::fromStdString(text.substr(0, text.size() - 2)));
}

void MainWindow::on_emplaceBtn_clicked()
{
    bool ok;
    int index = QInputDialog::getInt(this, "Emplace", "Index", 0, 0, vector.size() - 1, 1, &ok);
    if (!ok) return;
    int el = QInputDialog::getInt(this, "Emplace", "Value", 0, INT32_MIN, INT32_MAX, 1, &ok);
    if (!ok) return;
    vector.emplace(index, el);
    printVector();
}


void MainWindow::on_emplaceBtn_2_clicked()
{
    bool ok;
    int el = QInputDialog::getInt(this, "Emplace back", "Value", 0, INT32_MIN, INT32_MAX, 1, &ok);
    if (!ok) return;
    vector.emplace_back(el);
    printVector();
}


void MainWindow::on_dataBtn_clicked()
{
    ui->lineEdit->setText(QString::number(*(vector.data())));
}


void MainWindow::on_eraseBtn_clicked()
{
    bool ok;
    int start = QInputDialog::getInt(this, "Erase", "Start index", 0, 0, vector.size() - 1, 1, &ok);
    if (!ok) return;
    int end = QInputDialog::getInt(this, "Erase", "End index", 0, 0, vector.size() - 1, 1, &ok);
    if (!ok) return;
    try {
        vector.erase(start, end);
    } catch (...) {
        QMessageBox msg;
        msg.setText("Wrong input");
        msg.exec();
    }
    printVector();
}


void MainWindow::on_showVectorBtn_clicked()
{
    printVector();
}

void MainWindow::on_maxSizeBtn_clicked()
{
    ui->lineEdit->setText(QString::number(vector.max_size()));
}


void MainWindow::on_resizeBtn_clicked()
{
    bool ok;
    int newSize = QInputDialog::getInt(this, "Emplace back", "Value", 0, 0, vector.size(), 1, &ok);
    if (!ok) return;
    vector.resize(newSize);
    printVector();
}

