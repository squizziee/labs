#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "date.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QTableWidget>
#include <Vector.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(800, 600);
    btn = ui->openFileButton;
    addDateBtn = ui->addDateButton;
    submitBdayBtn = ui->submitBdayButton;
    editDateBtn = ui->editdateButton;
    connect(btn, &QPushButton::clicked, this, &MainWindow::handleOpenFileButton);
    connect(addDateBtn, &QPushButton::clicked, this, &MainWindow::handleAddDateButton);
    connect(submitBdayBtn, &QPushButton::clicked, this, &MainWindow::handleSubmitBdayButton);
    connect(editDateBtn, &QPushButton::clicked, this, &MainWindow::handleEditDateButton);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addRow(QString col1, QString col2, QString col3, QString col4, QString col5) {
    ui->tableWidget->insertRow(ui->tableWidget->rowCount());
    auto item1 = new QTableWidgetItem(col1);
    item1->setFlags(item1->flags() ^ Qt::ItemIsEditable);
    auto item2 = new QTableWidgetItem(col2);
    item1->setFlags(item2->flags() ^ Qt::ItemIsEditable);
    auto item3 = new QTableWidgetItem(col3);
    item1->setFlags(item3->flags() ^ Qt::ItemIsEditable);
    auto item4 = new QTableWidgetItem(col4);
    item1->setFlags(item4->flags() ^ Qt::ItemIsEditable);
    auto item5 = new QTableWidgetItem(col5);
    item1->setFlags(item5->flags() ^ Qt::ItemIsEditable);
    ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 0, item1);
    ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 1, item2);
    ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 2, item3);
    ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 3, item4);
    ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 4, item5);
}

void MainWindow::refresh() {
   QString fileContent;
   QFile file(currentFileName);
   if (!file.open(QIODevice::ReadWrite | QIODevice::Text))
       return;

   QTextStream in(&file);
   fileContent = in.readAll();
   file.close();
   //ui->textEdit->clear();
   ui->tableWidget->clear();
   ui->tableWidget->setRowCount(0);
   ui->tableWidget->setColumnCount(0);
   //ui->textEdit->setPlainText(fileContent);
   createTable(currentFileName.toStdString());
}

void MainWindow::handleOpenFileButton() {
    QString fileContent;
    QString filename= QFileDialog::getOpenFileName(this, "Choose File", QString(), tr("Data files (*.aboba)"));
    currentFileName = filename;

   if(filename.isEmpty())
       return;
   //ui->textEdit->clear();
   ui->tableWidget->clear();
   ui->tableWidget->setRowCount(0);
   ui->tableWidget->setColumnCount(0);
   //ui->textEdit->setPlainText(fileContent);
   createTable(filename.toStdString());
   ui->addDateLineEdit->setEnabled(true);
   ui->editIndexLineEdit->setEnabled(true);
   ui->editValueLineEdit->setEnabled(true);
   ui->editdateButton->setEnabled(true);
   ui->addDateButton->setEnabled(true);
   ui->tableWidget->setEnabled(true);
}

void MainWindow::createTable(std::string filename) {
    ui->tableWidget->setColumnCount(5);
    QStringList labels;
    labels << "Date" << "Next Day" << "Previous day" << "Week number" << "Days till next date";
    ui->tableWidget->setHorizontalHeaderLabels(labels);
    std::fstream manipulator;
    manipulator.open(filename, std::fstream::in | std::fstream::out);
    Vector<Date> elements;
    std::string temp;
    while (std::getline(manipulator, temp)) {
        if (temp != "") {
            elements.push_back(Date(temp));
        }
    }
    QString column1Content;
    QString column2Content;
    QString column3Content;
    QString column4Content;
    QString column5Content;
    for (size_t i = 0; i < elements.size() - 1; i++) {
        if (elements[i + 1].isCorrupted() && !elements[i].isCorrupted()) {
                    column1Content = QString::fromStdString(elements[i].toString());
                    column2Content = QString::fromStdString(elements[i].nextDay().toString());
                    column3Content = QString::fromStdString(elements[i].previousDay().toString());
                    column4Content = QString::fromStdString(std::to_string(elements[i].weekNumber()));
                    column5Content = QString::fromStdString("-");
                    addRow(column1Content, column2Content, column3Content, column4Content, column5Content);
        } else if (elements[i + 1].isCorrupted() && elements[i].isCorrupted()) {
            column1Content = QString::fromStdString("Corrupted");
            column2Content = QString::fromStdString("Corrupted");
            column3Content = QString::fromStdString("Corrupted");
            column4Content = QString::fromStdString("Corrupted");
            column5Content = QString::fromStdString("Corrupted");
            addRow(column1Content, column2Content, column3Content, column4Content, column5Content);
        } else if (!elements[i].isCorrupted()) {
            column1Content = QString::fromStdString(elements[i].toString());
            column2Content = QString::fromStdString(elements[i].nextDay().toString());
            column3Content = QString::fromStdString(elements[i].previousDay().toString());
            column4Content = QString::fromStdString(std::to_string(elements[i].weekNumber()));
            column5Content = QString::fromStdString(std::to_string(elements[i].duration(elements[i + 1])));
            addRow(column1Content, column2Content, column3Content, column4Content, column5Content);
        } else {
            column1Content = QString::fromStdString("Corrupted");
            column2Content = QString::fromStdString("Corrupted");
            column3Content = QString::fromStdString("Corrupted");
            column4Content = QString::fromStdString("Corrupted");
            column5Content = QString::fromStdString("Corrupted");
            addRow(column1Content, column2Content, column3Content, column4Content, column5Content);
        }
    }
    column1Content = QString::fromStdString(elements[elements.size() - 1].toString());
    column2Content = QString::fromStdString(elements[elements.size() - 1].nextDay().toString());
    column3Content = QString::fromStdString(elements[elements.size() - 1].previousDay().toString());
    column4Content = QString::fromStdString(std::to_string(elements[elements.size() - 1].weekNumber()));
    column5Content = QString::fromStdString("-");
    addRow(column1Content, column2Content, column3Content, column4Content, column5Content);
    manipulator.close();
}

void MainWindow::handleAddDateButton() {
    QString content = ui->addDateLineEdit->text();
    if (Date(content.toStdString()).isCorrupted()) {
        return;
    }
    std::fstream manipulator;
    manipulator.open(currentFileName.toStdString(), std::fstream::in | std::fstream::out);
    manipulator.seekp(0, std::ios_base::end);
    manipulator << content.toStdString() << "\n";
    manipulator.close();
    refresh();
}

const std::string currentDate() {
    time_t now = time(0);
    struct tm tstruct;
    char buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%d.%m.%Y", &tstruct);
    return buf;
}

void MainWindow::handleSubmitBdayButton() {
    QString content = ui->submitBdayLineEdit->text();
    Date birthday(content.toStdString());
    Date now(currentDate());
    if (birthday.isCorrupted()) {
        return;
    }
    birthday.setYear(now.getYear());
    int daysToBday = now.duration(birthday);
    if (now.isLaterThan(birthday)) {
        daysToBday = 365 + now.isLeap() - daysToBday;
    }
    QString labelText = QString::fromStdString(std::to_string(daysToBday) + std::string(" days left till your birthday"));
    ui->bdayLabel->setText(labelText);
}

void MainWindow::handleEditDateButton() {
    try {
        int index = ui->editIndexLineEdit->text().toInt();
        std::fstream manipulator;
        manipulator.open(currentFileName.toStdString(), std::fstream::in | std::fstream::out);
        std::string line;
        int count = 0;
        Vector<std::string> content;
        while (std::getline(manipulator, line)) {
            count++;
            std::string tmp = line;
            content.push_back(tmp);
        }
        if (index <= count && index > 0) {
            content[index - 1] = ui->editValueLineEdit->text().toStdString();
            manipulator.close();
            manipulator.open(currentFileName.toStdString(), std::fstream::out | std::fstream::trunc);
            for (std::string s : content) {
                manipulator << s << "\n";
            }
            manipulator.close();
            refresh();
        }
        manipulator.close();
    } catch (...) {
        return;
    }
}
