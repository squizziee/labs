#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QFile>
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->listWidget->setSelectionMode(QAbstractItemView::MultiSelection);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, "Choose file", QString(), "Text files (*.cpp *.txt)");
    if (filename.isEmpty()) {
        return;
    }
    QFile file(filename);
    file.open(QIODevice::ReadOnly);
    QStringList list = QString(file.readAll()).split("\n");
    for (auto& line : list) {
        ui->listWidget->addItem(line);
    }
    file.close();
}


void MainWindow::on_pushButton_3_clicked()
{
    QList<QListWidgetItem *> list= ui->listWidget->selectedItems();
    delete_range_begin = ui->listWidget->selectionModel()->selectedIndexes().first().row();
    delete_range_end = ui->listWidget->selectionModel()->selectedIndexes().last().row();
    for (auto& line : list) {
        selectedRows.push(line->text());
    }
    ui->listWidget->selectionModel()->clear();
    ui->listWidget->setSelectionMode(QAbstractItemView::SingleSelection);
}


void MainWindow::on_pushButton_2_clicked()
{
    custom::queue<QString> allRows;
    for(long long i = 0; i <  ui->listWidget->model()->rowCount(); i++) {
        allRows.push(ui->listWidget->item(i)->text());
    }
    std::cout << delete_range_begin << "\n";
    std::cout << delete_range_end << "\n";
    //std::cout << allRows.get_size() << "\n";
    allRows.remove_range(delete_range_begin, delete_range_end);
    //std::cout << allRows.get_size() << "\n";
    allRows.insert(ui->listWidget->selectionModel()->selectedIndexes().at(0).row(), selectedRows);
    ui->listWidget->clear();
    while (!allRows.empty()) {
        ui->listWidget->addItem(allRows.front());
        allRows.pop();
    }
}

