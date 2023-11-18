#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <fstream>
#include <sstream>
#include <io.h>
#include <sys/stat.h>
#include <QInputDialog>
#include <ArrayList.h>
#include <Employee.h>
#include <QMessageBox>
#include <thread>
#include <QMovie>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::setManipulationButtonsEnabled(bool state) {
    ui->addButton->setEnabled(state);
    ui->deleteButton->setEnabled(state);
    ui->editButton->setEnabled(state);
    ui->saveChangesButton->setEnabled(state);
    ui->searchNameButton->setEnabled(state);
    ui->searchDepartmentButton->setEnabled(state);
    ui->sortButton->setEnabled(state);
    ui->searchExperienceButton->setEnabled(state);
}

void MainWindow::setShowButtonsEnabled(bool state) {

}

bool MainWindow::isAlreadyPresent(Employee& obj) {
    for (int i = 0; i < currentEmployees.size(); i++) {
        if (obj.getName() == currentEmployees[i].getName()) {
            return true;
        }
    }
    return false;
}

void MainWindow::loadFromFile() {
    clearTable();
    std::fstream manip;
    manip.open(currentFileName, std::fstream::in | std::fstream::out);
    std::string line;
    while (std::getline(manip, line)) {
        if (!line.empty()) {
            //iterations++;
            try {
                std::stringstream stream(line);
                std::string segment;
                std::vector<std::string> result;
                while (std::getline(stream, segment, '|')) {
                    result.push_back(segment);
                }
                Employee temp(result[0], std::stoi(result[1]), result[2], result[3]);
                Date tempDate(result[3]);
                currentEmployees.push_back(temp);
            } catch(...) {
                //if ()
                QMessageBox msg;
                msg.setText("Incorrect file format.");
                msg.exec();
                currentEmployees.clear();
                currentFileName.clear();
                setManipulationButtonsEnabled(false);
                return;
            }
        }
    }
    manip.close();
}

void MainWindow::addRow(QString col1, QString col2, QString col3, QString col4, QString col5) {
    if (Date(col4.toStdString()).isCorrupted()) {
        col5 = QString("Invalid");
    }
    ui->tableWidget->insertRow(ui->tableWidget->rowCount());
    ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 0, new QTableWidgetItem(col1));
    ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 1, new QTableWidgetItem(col2));
    ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 2, new QTableWidgetItem(col3));
    ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 3, new QTableWidgetItem(col4));
    ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 4, new QTableWidgetItem(col5));
}

void MainWindow::createTable() {
    ui->tableWidget->setColumnCount(5);
    QStringList labels;
    labels << "Name" << "Departmant ID" << "Position" << "Works since" << "Days of experience";
    ui->tableWidget->setHorizontalHeaderLabels(labels);
    for (int i = 0; i < currentEmployees.size(); i++) {
        addRow(QString::fromStdString(currentEmployees[i].getName()),
               QString::number(currentEmployees[i].getDepartmentID()),
               QString::fromStdString(currentEmployees[i].getPosition()),
               QString::fromStdString(currentEmployees[i].getDate()),
               QString::number(currentEmployees[i].getWorkExperience()));
    }
}

void MainWindow::clearTable() {
    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(0);
}

void MainWindow::on_openFileButton_clicked() {
    QString filename = QFileDialog::getOpenFileName(this, "Choose file", QString(), "Employee list files (*.employees)");
    if (filename.isEmpty()) {
        return;
    }
    setManipulationButtonsEnabled(true);
    setShowButtonsEnabled(true);
    currentFileName = filename.toStdString();
    clearTable();
    currentEmployees.clear();
    loadFromFile();
    createTable();
    setMeme();
}

void MainWindow::setMeme() {
    QString path;
    srand((unsigned)time(0));
    int i = (rand()%3)+1;
    if (i == 1) {
        path = "C:\\Users\\HP\\Documents\\Lab2Task1_2\\bear-ff.gif";
    }
    else if (i == 2) {
        path = "C:\\Users\\HP\\Documents\\Lab2Task1_2\\vinejoel-catdance.gif";
    }
    else {
        path = "C:\\Users\\HP\\Documents\\Lab2Task1_2\\pepe-twitch.gif";
    }
    QMovie *movie = new QMovie(path);
    ui->memeLabel->setMovie(movie);
    movie->start();
}

void MainWindow::on_addButton_clicked() {
    bool ok;
    QString field1 = QInputDialog::getText(this, tr("Add Employee"),
                                           tr("Name:"), QLineEdit::Normal,
                                           QString::fromStdString("No one"), &ok);
    if (!ok) return;
    int field2 = QInputDialog::getInt(this, tr("Add Employee"),
                                      tr("Department ID:"), 1, 1, 100, 1, &ok);
    if (!ok) return;
    QString field3 = QInputDialog::getText(this, tr("Add Employee"),
                                           tr("Position:"), QLineEdit::Normal,
                                           QString::fromStdString("Nowhere"), &ok);
    if (!ok) return;
    QString field4 = QInputDialog::getText(this, tr("Add Employee"),
                                           tr("Date:"), QLineEdit::Normal,
                                           QString::fromStdString("12.12.2001"), &ok);
    if (!ok) return;
    Employee temp(field1.toStdString(), field2, field3.toStdString(), field4.toStdString());
    if (isAlreadyPresent(temp)) {
        QMessageBox msg;
        msg.setText("Employee with this name is already in system.");
        msg.exec();
        return;
    }
    currentEmployees.push_back(temp);
    std::thread tempThread([this, &field1, &field2, &field3, &field4, &temp]{
        addRow(field1, QString::number(field2), field3, field4, QString::number(temp.getWorkExperience()));
    });
    tempThread.join();
}

void sortList(ArrayList<Employee>&, int);
void MainWindow::on_searchNameButton_clicked() {
    if (!currentEmployees.size()) {
        QMessageBox msg;
        msg.setText("Nothing to search here.");
        msg.exec();
        return;
    }
    bool ok;
    QString name = QInputDialog::getText(this, tr("Search for Employee:"),
                                           tr("Name:"), QLineEdit::Normal,
                                           QString::fromStdString("No one"), &ok);
    if (!ok) {
        return;
    }
    QString text;
    ArrayList<Employee> tempList;
    for (int i = 0; i < currentEmployees.size(); i++) {
        tempList.push_back(currentEmployees[i]);
    }
    sortList(tempList, 4);
    for (int i = 0; i < tempList.size() - 1; i++) {
        auto temp = tempList[i];
        if (temp.getName() == name.toStdString()) {
            text.append(
                        QString::fromStdString(temp.getName())
                        + ", " + QString::number(temp.getDepartmentID())
                        + ", " + QString::fromStdString(temp.getPosition())
                        + ", " + QString::fromStdString(temp.getDate())
                        + "\n");
            if (tempList[i + 1].getName() != name.toStdString()) {
                break;
            }
            else if (i + 1 == tempList.size() - 1) {
                auto nextTemp = tempList[i + 1];
                text.append(
                            QString::fromStdString(nextTemp.getName())
                            + ", " + QString::number(nextTemp.getDepartmentID())
                            + ", " + QString::fromStdString(nextTemp.getPosition())
                            + ", " + QString::fromStdString(nextTemp.getDate())
                            + "\n");
            }

        }
    }
    QMessageBox msg;
    if (text.isEmpty()) {
        text = "Nothing found.";
    }
    msg.setText(text);
    msg.exec();
}

void sortList(ArrayList<Employee>&, int);
void MainWindow::on_searchDepartmentButton_clicked() {
    if (!currentEmployees.size()) {
        QMessageBox msg;
        msg.setText("Nothing to search here.");
        msg.exec();
        return;
    }
    bool ok;
    int id = QInputDialog::getInt(this, tr("Add Employee"),
                                      tr("Department ID:"), 1, 1, 100, 1, &ok);
    if (!ok) {
        return;
    }
    QString text;
    ArrayList<Employee> tempList;
    for (int i = 0; i < currentEmployees.size(); i++) {
        tempList.push_back(currentEmployees[i]);
    }
    sortList(tempList, 2);
    for (int i = 0; i < tempList.size() - 1; i++) {
        auto temp = tempList[i];
        if (temp.getDepartmentID() == id) {
            text.append(
                        QString::fromStdString(temp.getName())
                        + ", " + QString::number(temp.getDepartmentID())
                        + ", " + QString::fromStdString(temp.getPosition())
                        + ", " + QString::fromStdString(temp.getDate())
                        + "\n");
            if (tempList[i + 1].getDepartmentID() != id) {
                break;
            }
            else if (i + 1 == tempList.size() - 1) {
                auto nextTemp = tempList[i + 1];
                text.append(
                            QString::fromStdString(nextTemp.getName())
                            + ", " + QString::number(nextTemp.getDepartmentID())
                            + ", " + QString::fromStdString(nextTemp.getPosition())
                            + ", " + QString::fromStdString(nextTemp.getDate())
                            + "\n");
            }
        }
    }
    QMessageBox msg;
    if (text.isEmpty()) {
        text = "Nothing found.";
    }
    msg.setText(text);
    msg.exec();
}

void MainWindow::on_saveChangesButton_clicked()
{
    std::fstream manip;
    manip.open(currentFileName, std::fstream::trunc | std::fstream::out);
    for (int i = 0; i < currentEmployees.size(); i++) {
        Employee temp = currentEmployees[i];
        manip << temp.getName() +
                 "|" + std::to_string(temp.getDepartmentID()) +
                 "|" + temp.getPosition() +
                 "|" + temp.getDate() + "\n";
    }
    manip.close();
    QMessageBox msg;
    msg.setText(QString::fromStdString("Saved to " + currentFileName));
    msg.exec();
    return;
}

void MainWindow::on_deleteButton_clicked()
{
    if (!currentEmployees.size()) {
        QMessageBox msg;
        msg.setText("Nothing to delete here.");
        msg.exec();
        return;
    }
    bool ok;
    int index = QInputDialog::getInt(this, tr("Choose element"),
                                      tr("Index:"), 1, 1, currentEmployees.size(), 1, &ok);
    if (!ok) {
        return;
    }
    ArrayList<Employee> temp;
    for (int i = 0; i < currentEmployees.size(); i++) {
        if (i != index - 1) {
            temp.push_back(currentEmployees[i]);
        }
    }
    currentEmployees.clear();
    for (int i = 0; i < temp.size(); i++) {
         currentEmployees.push_back(temp[i]);
    }
    ui->tableWidget->removeRow(index - 1);
}

void MainWindow::on_editButton_clicked()
{
    if (currentEmployees.empty()) {
        QMessageBox msg;
        msg.setText("Nothing to edit here.");
        msg.exec();
        return;
    }
    bool ok;
    int index = QInputDialog::getInt(this, tr("Choose element"),
                                      tr("Index:"), 1, 1, currentEmployees.size(), 1, &ok);
    if (!ok) {
        return;
    }
    QString field1 = QInputDialog::getText(this, tr("Add Employee"),
                                           tr("Name:"), QLineEdit::Normal,
                                           QString::fromStdString(currentEmployees[index - 1].getName()), &ok);
    if (!ok) return;
    int field2 = QInputDialog::getInt(this, tr("Add Employee"),
                                      tr("Department ID:"), currentEmployees[index - 1].getDepartmentID(), 1, 100, 1, &ok);
    if (!ok) return;
    QString field3 = QInputDialog::getText(this, tr("Add Employee"),
                                           tr("Position:"), QLineEdit::Normal,
                                           QString::fromStdString(currentEmployees[index - 1].getPosition()), &ok);
    if (!ok) return;
    QString field4 = QInputDialog::getText(this, tr("Add Employee"),
                                           tr("Date:"), QLineEdit::Normal,
                                           QString::fromStdString(currentEmployees[index - 1].getDate()), &ok);
    if (!ok) return;
    Employee temp(field1.toStdString(), field2, field3.toStdString(), field4.toStdString());
    if (isAlreadyPresent(temp)) {
        QMessageBox msg;
        msg.setText("Employee with this name is already in system.");
        msg.exec();
        return;
    }
    currentEmployees[index - 1].setName(field1.toStdString());
    currentEmployees[index - 1].setDepartmentID(field2);
    currentEmployees[index - 1].setPosition(field3.toStdString());
    currentEmployees[index - 1].setDate(field4.toStdString());
    clearTable();
    createTable();
}

void merge(ArrayList<Employee>& list, int const left,
           int const mid, int const right, int fieldID) {
    auto const subArrayOne = mid - left + 1;
    auto const subArrayTwo = right - mid;
    ArrayList<Employee> leftArray, rightArray;
    for (auto i = 0; i < subArrayOne; i++)
        leftArray.push_back(list[left + i]);
    for (auto j = 0; j < subArrayTwo; j++)
        rightArray.push_back(list[mid + 1 + j]);
    auto indexOfSubArrayOne = 0,
         indexOfSubArrayTwo = 0;
    int indexOfMergedArray = left;
    while (indexOfSubArrayOne < subArrayOne &&
           indexOfSubArrayTwo < subArrayTwo) {
        if (fieldID == 2) {
            if (leftArray[indexOfSubArrayOne].getDepartmentID() <=
                rightArray[indexOfSubArrayTwo].getDepartmentID()) {
                list[indexOfMergedArray] =
                leftArray[indexOfSubArrayOne];
                indexOfSubArrayOne++;
            }
            else {
                list[indexOfMergedArray] =
                rightArray[indexOfSubArrayTwo];
                indexOfSubArrayTwo++;
            }

        }
        else if (fieldID == 4) {
            if (leftArray[indexOfSubArrayOne].getName() <=
                rightArray[indexOfSubArrayTwo].getName()) {
                list[indexOfMergedArray] =
                leftArray[indexOfSubArrayOne];
                indexOfSubArrayOne++;
            }
            else {
                list[indexOfMergedArray] =
                rightArray[indexOfSubArrayTwo];
                indexOfSubArrayTwo++;
            }

        }
        indexOfMergedArray++;
    }
    while (indexOfSubArrayOne < subArrayOne)
    {
        list[indexOfMergedArray] =
        leftArray[indexOfSubArrayOne];
        indexOfSubArrayOne++;
        indexOfMergedArray++;
    }
    while (indexOfSubArrayTwo < subArrayTwo)
    {
        list[indexOfMergedArray] =
        rightArray[indexOfSubArrayTwo];
        indexOfSubArrayTwo++;
        indexOfMergedArray++;
    }
}

void mergeSort(ArrayList<Employee>& list,
               int const begin,
               int const end, int fieldID)
{
    if (begin >= end)
        return;

    auto mid = begin + (end - begin) / 2;
    mergeSort(list, begin, mid, fieldID);
    mergeSort(list, mid + 1, end, fieldID);
    merge(list, begin, mid, end, fieldID);
}

void sortList(ArrayList<Employee>& list, int fieldID) {
    mergeSort(list, 0, list.size() - 1, fieldID);
}

void MainWindow::on_sortButton_clicked()
{
    sortList(currentEmployees, 2);
    clearTable();
    createTable();
}


void MainWindow::on_searchExperienceButton_clicked()
{
    if (!currentEmployees.size()) {
        QMessageBox msg;
        msg.setText("Nothing to search here.");
        msg.exec();
        return;
    }
    bool ok;
    int experience = QInputDialog::getInt(this, tr("Minimum work experience"),
                                          tr("Days:"), 1, 1, 100000, 1, &ok);
    if (!ok) {
        return;
    }
    QString text;
    ArrayList<Employee> tempList;
    for (int i = 0; i < currentEmployees.size(); i++) {
        tempList.push_back(currentEmployees[i]);
    }
    sortList(tempList, 4);
    for (int i = 0; i < tempList.size(); i++) {
        auto temp = tempList[i];
        if (temp.getWorkExperience() >= experience && !Date(temp.getDate()).isCorrupted()) {
            text.append(
                        QString::fromStdString(temp.getName())
                        + ", " + QString::number(temp.getDepartmentID())
                        + ", " + QString::fromStdString(temp.getPosition())
                        + ", " + QString::fromStdString(temp.getDate())
                        + "\n");

        }
    }
    QMessageBox msg;
    if (text.isEmpty()) {
        text = "Nothing found.";
    }
    msg.setText(text);
    msg.exec();
}

