#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <fstream>
#include <sstream>
#include <io.h>
#include <sys/stat.h>
#include <QInputDialog>
#include <LinkedList.h>
#include <Client_.h>
#include <QMessageBox>

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
    ui->removeDuplicatesButton->setEnabled(state);
    ui->saveChangesButton->setEnabled(state);
    ui->searchNameButton->setEnabled(state);
    ui->searchDateButton->setEnabled(state);
    ui->sortButton->setEnabled(state);
}

void MainWindow::setShowButtonsEnabled(bool state) {
    ui->allOrdersButton->setEnabled(state);
    ui->completedOrdersButton->setEnabled(state);
    ui->uncompletedOrdersButton->setEnabled(state);
}

bool contains(LinkedList<Client>& list, Client& toFind) {
    for (int i = 0; i < list.getSize(); i++) {
        //std::cout << list[i].toString() << "|";
        //std::cout << toFind.toString() << "\n";
        if (list[i].getName() == toFind.getName() &&
            list[i].getHomeAdress() == toFind.getHomeAdress()) {
            //std::cout << "found\n";
            return true;
        }
    }
    return false;
}
void removeDuplicates(LinkedList<Client>& list) {
    LinkedList<Client> result;
    for (int i = 0; i < list.getSize(); i++) {
        Client temp = list[i];
        if (!contains(result, temp)) {
            result.add(temp);
        }
    }
    list = result;
}

void MainWindow::loadFromFile() {
    clearTable();
    std::fstream manip;
    manip.open(currentFileName, std::fstream::in | std::fstream::out);
    std::string line;
    int iterations = 0;
    while (std::getline(manip, line)) {
        if (!line.empty()) {
            iterations++;
            try {
                std::stringstream stream(line);
                std::string segment;
                std::vector<std::string> result;
                while (std::getline(stream, segment, '|')) {
                    result.push_back(segment);
                }
                Client temp(std::stoi(result[0]), result[1], result[2], result[3], std::stoi(result[4]));
                currentClients.add(temp);
            } catch(...) {
                QMessageBox msg;
                msg.setText("Incorrect file format.");
                msg.exec();
                LinkedList<Client> newList;
                currentClients = newList;
                return;
            }
        }
    }
    manip.close();
}

void MainWindow::addRow(QString col1, QString col2, QString col3, QString col4, QString col5) {
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
    labels << "Number" << "Name" << "Home address" << "Date" << "Completion";
    ui->tableWidget->setHorizontalHeaderLabels(labels);
    for (int i = 0; i < currentClients.getSize(); i++) {
        addRow(QString::number(currentClients[i].getNumber()),
               QString::fromStdString(currentClients[i].getName()),
               QString::fromStdString(currentClients[i].getHomeAdress()),
               QString::fromStdString(currentClients[i].getDate()),
               QString::fromStdString(currentClients[i].isCompleted() ? "Completed" : "Waiting"));
    }
}

void MainWindow::clearTable() {
    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(0);
}

void MainWindow::on_openFileButton_clicked() {
    QString filename = QFileDialog::getOpenFileName(this, "Choose file", QString(), "Client list files (*.clients)");
    if (filename.isEmpty()) {
        return;
    }
    setManipulationButtonsEnabled(true);
    setShowButtonsEnabled(true);
    currentFileName = filename.toStdString();
    clearTable();
    LinkedList<Client> temp;
    currentClients = temp;
    //currentClients.clear();
    loadFromFile();
    createTable();
}


void MainWindow::on_addButton_clicked() {
    bool ok;
    int field1 = QInputDialog::getInt(this, tr("Add client"),
                                      tr("Number:"), 1, 1, 25, 1, &ok);
    if (!ok) return;
    QString field2 = QInputDialog::getText(this, tr("Add client"),
                                           tr("Name:"), QLineEdit::Normal,
                                           QString::fromStdString("No one"), &ok);
    if (!ok) return;
    QString field3 = QInputDialog::getText(this, tr("Add client"),
                                           tr("Address:"), QLineEdit::Normal,
                                           QString::fromStdString("Nowhere"), &ok);
    if (!ok) return;
    QString field4 = QInputDialog::getText(this, tr("Add client"),
                                           tr("Date:"), QLineEdit::Normal,
                                           QString::fromStdString("Never"), &ok);
    bool field5 = QInputDialog::getInt(this, tr("Add client"),
                                      tr("Completed:"), 0, 0, 1, 1, &ok);
    if (!ok) return;
    std::fstream manip;
    Client temp(field1, field2.toStdString(), field3.toStdString(), field4.toStdString(), field5);
    currentClients.add(temp);
    addRow(QString::number(field1), field2, field3, field4, QString::number(field5));
}

void sortList(LinkedList<Client>&, int);
void MainWindow::on_searchNameButton_clicked() {
    bool ok;
    QString name = QInputDialog::getText(this, tr("Search for client:"),
                                           tr("Name:"), QLineEdit::Normal,
                                           QString::fromStdString("No one"), &ok);
    if (!ok) {
        return;
    }
    QString text;
    LinkedList<Client> tempList;
    for (int i = 0; i < currentClients.getSize(); i++) {
        tempList.add(currentClients[i]);
    }
    //sortList(tempList, 2);
    for (int i = 0; i < tempList.getSize(); i++) {
        auto temp = tempList[i];
        if (temp.getName() == name.toStdString()) {
            text.append(
                                                          QString::number(temp.getNumber())
                                                          + ", " + QString::fromStdString(temp.getName())
                                                          + ", " + QString::fromStdString(temp.getHomeAdress())
                                                          + ", " + QString::fromStdString(temp.getDate())
                                                          + "\n");
        }
        /*if (tempList[i + 1].getName() != name.toStdString()) {
            break;
        }
        else if (i + 1 == tempList.getSize() - 1) {
            auto nextTemp = tempList[i + 1];
            text.append(
                                                          QString::number(nextTemp.getNumber())
                                                          + ", " + QString::fromStdString(nextTemp.getName())
                                                          + ", " + QString::fromStdString(nextTemp.getHomeAdress())
                                                          + ", " + QString::fromStdString(nextTemp.getDate())
                                                          + "\n");
        }*/
    }
    QMessageBox msg;
    msg.setText(text);
    msg.exec();
}

void sortList(LinkedList<Client>&, int);
void MainWindow::on_searchDateButton_clicked() {
    bool ok;
    QString date = QInputDialog::getText(this, tr("Search for client:"),
                                           tr("Date:"), QLineEdit::Normal,
                                           QString::fromStdString("Never"), &ok);
    if (!ok) {
        return;
    }
    QString text;
    LinkedList<Client> tempList;
    for (int i = 0; i < currentClients.getSize(); i++) {
        tempList.add(currentClients[i]);
    }
    //sortList(tempList, 4);
    for (int i = 0; i < tempList.getSize(); i++) {
        auto temp = tempList[i];
        if (temp.getDate() == date.toStdString()) {
            text.append(
                                                          QString::number(temp.getNumber())
                                                          + ", " + QString::fromStdString(temp.getName())
                                                          + ", " + QString::fromStdString(temp.getHomeAdress())
                                                          + ", " + QString::fromStdString(temp.getDate())
                                                          + "\n");
        }
        /*if (tempList[i + 1].getDate() != date.toStdString()) {
            break;
        }
        else if (i + 1 == tempList.getSize() - 1) {
            auto nextTemp = tempList[i + 1];
            text.append(
                                                          QString::number(nextTemp.getNumber())
                                                          + ", " + QString::fromStdString(nextTemp.getName())
                                                          + ", " + QString::fromStdString(nextTemp.getHomeAdress())
                                                          + ", " + QString::fromStdString(nextTemp.getDate())
                                                          + "\n");
        }*/
    }
    QMessageBox msg;
    msg.setText(text);
    msg.exec();
}

void MainWindow::on_removeDuplicatesButton_clicked(){
    removeDuplicates(currentClients);
    clearTable();
    createTable();
}

void MainWindow::on_saveChangesButton_clicked()
{
    std::fstream manip;
    manip.open(currentFileName, std::fstream::trunc | std::fstream::out);
    for (int i = 0; i < currentClients.getSize(); i++) {
        Client temp = currentClients[i];
        manip << std::to_string(temp.getNumber()) +
                 "|" + temp.getName() +
                 "|" + temp.getHomeAdress() +
                 "|" + temp.getDate() +
                 "|" + std::to_string(temp.isCompleted()) + "\n";
    }
    manip.close();
}


void MainWindow::on_deleteButton_clicked()
{
    bool ok;
    int index = QInputDialog::getInt(this, tr("Choose element"),
                                      tr("Index:"), 1, 1, currentClients.getSize(), 1, &ok);
    if (!ok) {
        return;
    }
    currentClients.remove(index - 1);
    ui->tableWidget->removeRow(index - 1);
}


void MainWindow::on_editButton_clicked()
{
    bool ok;
    int index = QInputDialog::getInt(this, tr("Choose element"),
                                      tr("Index:"), 1, 1, currentClients.getSize(), 1, &ok);
    if (!ok) {
        return;
    }
    int field1 = QInputDialog::getInt(this, tr("Edit client"),
                                      tr("Number:"), 1, 1, 25, 1, &ok);
    if (!ok) return;
    QString field2 = QInputDialog::getText(this, tr("Edit client"),
                                           tr("Name:"), QLineEdit::Normal,
                                           QString::fromStdString("No one"), &ok);
    if (!ok) return;
    QString field3 = QInputDialog::getText(this, tr("Edit client"),
                                           tr("Address:"), QLineEdit::Normal,
                                           QString::fromStdString("Nowhere"), &ok);
    if (!ok) return;
    QString field4 = QInputDialog::getText(this, tr("Edit client"),
                                           tr("Date:"), QLineEdit::Normal,
                                           QString::fromStdString("Never"), &ok);
    bool field5 = QInputDialog::getInt(this, tr("Add client"),
                                      tr("Completed:"), 0, 0, 1, 1, &ok);
    if (!ok) return;
    currentClients[index - 1].setNumber(field1);
    currentClients[index - 1].setName(field2.toStdString());
    currentClients[index - 1].setHomeAddress(field3.toStdString());
    currentClients[index - 1].setDate(field4.toStdString());
    currentClients[index - 1].setCompleted(field5);
    clearTable();
    createTable();
}

void merge(LinkedList<Client>& list, int const left,
           int const mid, int const right, int fieldID) {
    auto const subArrayOne = mid - left + 1;
    auto const subArrayTwo = right - mid;
    LinkedList<Client> leftArray, rightArray;
    for (auto i = 0; i < subArrayOne; i++)
        leftArray.add(list[left + i]);
    for (auto j = 0; j < subArrayTwo; j++)
        rightArray.add(list[mid + 1 + j]);
    auto indexOfSubArrayOne = 0,
         indexOfSubArrayTwo = 0;
    int indexOfMergedArray = left;
    while (indexOfSubArrayOne < subArrayOne &&
           indexOfSubArrayTwo < subArrayTwo) {
        if (fieldID == 2) {
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
        else if (fieldID == 4) {
            if (leftArray[indexOfSubArrayOne].getDate() <=
                rightArray[indexOfSubArrayTwo].getDate()) {
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

void mergeSort(LinkedList<Client>& list,
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

void sortList(LinkedList<Client>& list, int fieldID) {
    mergeSort(list, 0, list.getSize() - 1, fieldID);
}

void MainWindow::on_sortButton_clicked()
{
    sortList(currentClients, 2);
    clearTable();
    createTable();
}


void MainWindow::on_completedOrdersButton_clicked()
{
    clearTable();
    setManipulationButtonsEnabled(false);
    for (int i = 0; i < currentClients.getSize(); i++) {
        if (currentClients[i].isCompleted()) {
            addRow(QString::number(currentClients[i].getNumber()),
                   QString::fromStdString(currentClients[i].getName()),
                   QString::fromStdString(currentClients[i].getHomeAdress()),
                   QString::fromStdString(currentClients[i].getDate()),
                   QString::fromStdString(currentClients[i].isCompleted() ? "Completed" : "Waiting"));
        }
    }
}


void MainWindow::on_uncompletedOrdersButton_clicked()
{
    clearTable();
    setManipulationButtonsEnabled(false);
    for (int i = 0; i < currentClients.getSize(); i++) {
        if (!currentClients[i].isCompleted()) {
            addRow(QString::number(currentClients[i].getNumber()),
                   QString::fromStdString(currentClients[i].getName()),
                   QString::fromStdString(currentClients[i].getHomeAdress()),
                   QString::fromStdString(currentClients[i].getDate()),
                   QString::fromStdString(currentClients[i].isCompleted() ? "Completed" : "Waiting"));
        }
    }
}


void MainWindow::on_allOrdersButton_clicked()
{
    clearTable();
    setManipulationButtonsEnabled(true);
    for (int i = 0; i < currentClients.getSize(); i++) {
        addRow(QString::number(currentClients[i].getNumber()),
               QString::fromStdString(currentClients[i].getName()),
               QString::fromStdString(currentClients[i].getHomeAdress()),
               QString::fromStdString(currentClients[i].getDate()),
               QString::fromStdString(currentClients[i].isCompleted() ? "Completed" : "Waiting"));
    }
}

