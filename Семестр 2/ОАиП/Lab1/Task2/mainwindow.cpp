#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMainWindow>
#include <QInputDialog>
#include <QFileDialog>
#include <QDir>
#include <fstream>
#include <map>
#include "Dish.h"
#include <Vector.h>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(500, 600);

    openFileBtn = ui->openFileButton;
    orderComboBox = ui->comboBox;
    removeOrderBtn = ui->removeOrderButton;
    editOrderBtn = ui->editOrderButton;
    addOrderBtn = ui->addOrderButton;
    sortListBtn = ui->sortListButton;
    popularDishesBtn = ui->popularDishesButton;

    connect(openFileBtn, &QPushButton::clicked, this, &MainWindow::handleOpenFileButton);
    connect(orderComboBox, &QComboBox::currentIndexChanged, this, &MainWindow::handleComboBoxChange); 
    connect(removeOrderBtn, &QPushButton::clicked, this, &MainWindow::handleRemoveOrderButton);
    connect(editOrderBtn, &QPushButton::clicked, this, &MainWindow::handleEditOrderButton);
    connect(addOrderBtn, &QPushButton::clicked, this, &MainWindow::handleAddOrderButton);
    connect(sortListBtn, &QPushButton::clicked, this, &MainWindow::handleSortListButton);
    connect(popularDishesBtn, &QPushButton::clicked, this, &MainWindow::handlePopularDishesButton);

    //ui->listWidget->addItem(QString("item 1"));
    //ui->listWidget->itemClicked(
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::enableButtons() {
    ui->addOrderButton->setEnabled(true);
    ui->editOrderButton->setEnabled(true);
    ui->removeOrderButton->setEnabled(true);
    ui->sortListButton->setEnabled(true);
    ui->popularDishesButton->setEnabled(true);
    ui->comboBox->setEnabled(true);
}

void MainWindow::disableButtons() {
    ui->addOrderButton->setEnabled(false);
    ui->editOrderButton->setEnabled(false);
    ui->removeOrderButton->setEnabled(false);
    ui->sortListButton->setEnabled(false);
    ui->popularDishesButton->setEnabled(false);
    ui->comboBox->setEnabled(false);
}

void MainWindow::loadChangesIntoFile() {
    try {
        std::fstream manip;
        manip.open(currentFileName, std::fstream::trunc | std::fstream::out);
        for (Order o : currentItems) {
            manip << o.toString() << "\n";
        }
        manip.close();
    } catch(...) {
        return;
    }
}

void MainWindow::loadFileIntoUI() {
        if (currentFileName != "") {
            enableButtons();
        }
        currentItems.clear();
        ui->comboBox->clear();
        std::fstream manip;
        manip.open(currentFileName, std::fstream::in | std::fstream::out);
        std::vector<Order> orders;
        std::string line;
        int iterations = 0;
        while (std::getline(manip, line)) {
            if (!line.empty()) {
                iterations++;
                try {
                    std::string temp(line);
                    line.clear();
                    std::stringstream stream(temp);
                    std::string segment;
                    std::vector<std::string> result;
                    while (std::getline(stream, segment, '|')) {
                        result.push_back(segment);
                    }
                    Dish dish(result[1], result[2], std::stoi(result[3]));
                    Order order(std::stoi(result[0]), dish, std::stoi(result[4]));
                    currentItems.push_back(order);
                    ui->comboBox->addItem(QString::fromStdString("Order №" + std::to_string(order.getOrderID())));
                    result.clear();
                    segment.clear();
                    stream.clear();
                } catch(...) {
                    continue;
                }
            }
        }
        if (iterations > 0 && currentItems.empty()) {
            disableButtons();
            ui->listWidget->clear();
            QMessageBox msg;
            msg.setText("Wrong file, dumbass");
            msg.exec();
        }
        if (currentItems.empty()) {
            ui->listWidget->clear();
        }
        /*for (Order o : currentItems) {
            ui->comboBox->addItem(QString::fromStdString("Order №" + std::to_string(o.getOrderID())));
        }*/
        manip.close();
}

void MainWindow::handleOpenFileButton() {
    QString filename= QFileDialog::getOpenFileName(this, "Choose File", QString(), "Text files (*.txt)");
    if (currentFileName == filename.toStdString()) {
        QMessageBox msg;
        msg.setText(QString("File is already opened."));
        msg.exec();
        return;
    }
    currentFileName = filename.toStdString();
    if(filename.isEmpty())
        return;
    loadFileIntoUI();
}

void MainWindow::handleComboBoxChange() {
    ui->listWidget->clear();
    int index = ui->comboBox->currentIndex();
    int price = currentItems[index].getDish().getPrice() * currentItems[index].getDishQuantity();
    QString line1 = QString::fromStdString("Total cost: $" + std::to_string(price));
    QString line2 = QString::fromStdString("Dish: " + currentItems[index].getDish().getName());
    QString line3 = QString::fromStdString("Description: " + currentItems[index].getDish().getDesc());
    QString line4 = QString::fromStdString("Portions: " + std::to_string(currentItems[index].getDishQuantity()));
    QString line5 = QString::fromStdString("Table : №" + std::to_string(currentItems[index].getOrderTable()));
    ui->listWidget->addItem(line1);
    ui->listWidget->addItem(line2);
    ui->listWidget->addItem(line3);
    ui->listWidget->addItem(line4);
    ui->listWidget->addItem(line5);
}

void MainWindow::handleRemoveOrderButton() {
    unsigned int index = ui->comboBox->currentIndex();
    std::vector<Order> temp;
    for (unsigned int i = 0; i < currentItems.size(); i++) {
        if (i != index) {
            temp.push_back(currentItems[i]);
        }
    }
    std::fstream manip;
    manip.open(currentFileName, std::fstream::trunc | std::fstream::out);
    for (Order o : temp) {
        manip << o.toString() << "\n";
    }
    manip.close();
    loadFileIntoUI();
}

void MainWindow::handleEditOrderButton() {
    if(ui->comboBox->count() == 0) {
        return;
    }
    unsigned int index = ui->comboBox->currentIndex();
    Order temp = currentItems[index];
    bool ok;
    int field1 = QInputDialog::getInt(this, tr("Edit order"),
                                      tr("Table number:"), temp.getOrderTable(), 1, 25, 1, &ok);
    if (!ok) return;
    QString field2 = QInputDialog::getText(this, tr("Edit order"),
                                           tr("Dish name:"), QLineEdit::Normal,
                                           QString::fromStdString(temp.getDish().getName()), &ok);
    if (!ok) return;
    QString field3 = QInputDialog::getText(this, tr("Edit order"),
                                           tr("Dish description:"), QLineEdit::Normal,
                                           QString::fromStdString(temp.getDish().getDesc()), &ok);
    if (!ok) return;
    int field4 = QInputDialog::getInt(this, tr("Edit order"),
                                      tr("Dish price(USD):"), temp.getDish().getPrice(), 1, 1000, 1, &ok);
    if (!ok) return;
    int field5 = QInputDialog::getInt(this, tr("Edit order"),
                                      tr("Dish portions:"), temp.getDishQuantity(), 1, 1000, 1, &ok);
    if (!ok) return;
    if (ok) {
        currentItems[index].setOrderTable(field1);
        currentItems[index].setDish(Dish(field2.toStdString(), field3.toStdString(), field4));
        currentItems[index].setDishQuantity(field5);
        loadChangesIntoFile();
        loadFileIntoUI();
    }
}

void MainWindow::handleAddOrderButton() {
    bool ok;
    int field1 = QInputDialog::getInt(this, tr("Edit order"),
                                      tr("Table number:"), 2, 1, 25, 1, &ok);
    if (!ok) return;
    QString field2 = QInputDialog::getText(this, tr("Edit order"),
                                           tr("Dish name:"), QLineEdit::Normal,
                                           QString::fromStdString("Nothing"), &ok);
    if (!ok) return;
    QString field3 = QInputDialog::getText(this, tr("Edit order"),
                                           tr("Dish description:"), QLineEdit::Normal,
                                           QString::fromStdString("Absolutely nothing"), &ok);
    if (!ok) return;
    int field4 = QInputDialog::getInt(this, tr("Edit order"),
                                      tr("Dish price(USD):"), 1, 1, 1000, 1, &ok);
    if (!ok) return;
    int field5 = QInputDialog::getInt(this, tr("Edit order"),
                                      tr("Dish portions:"), 1, 1, 1000, 1, &ok);
    if (!ok) return;
    if (ok) {
        Order temp(field1, Dish(field2.toStdString(), field3.toStdString(), field4), field5);
        currentItems.push_back(temp);
        loadChangesIntoFile();
        loadFileIntoUI();
    }
}

void selectionSort(std::vector<Dish> &vect) {
    for (size_t i = 0; i < vect.size() - 1; i++) {
        int minIndex = i;
        for (size_t j = i + 1; j < vect.size(); j++) {
            if (vect[minIndex].getPrice() > vect[j].getPrice()) {
                minIndex = j;
            }
        }
        Dish temp = vect[minIndex];
        vect[minIndex] = vect[i];
        vect[i] = temp;
    }
}

void MainWindow::handleSortListButton() {
    if(ui->comboBox->count() == 0) {
        return;
    }
    std::vector<Dish> dishes;
    for (Order o : currentItems) {
        Dish temp = o.getDish();
        if (std::find(dishes.begin(), dishes.end(), temp) == dishes.end()) {
            //std::cout <<
            dishes.push_back(temp);
        }
    }
    sort(dishes.begin(), dishes.end());
    ui->listWidget->clear();
    for (Dish d : dishes) {
        ui->listWidget->addItem(QString::fromStdString(d.getName() + " — $" + std::to_string(d.getPrice())));
    }
}

bool cmp(std::pair<std::string, int>& a,
         std::pair<std::string, int>& b) {
    return a.second <  b.second;
}

std::vector<std::pair<std::string, int>> sortMap(std::map<std::string, int>& M) {
    std::vector<std::pair<std::string, int> > A;
    for (auto& it : M) {
        A.push_back(it);
    }
    sort(A.rbegin(), A.rend(), cmp);
    return A;
}

void MainWindow::handlePopularDishesButton() {
    if(ui->comboBox->count() == 0) {
        return;
    }
    std::map<std::string, int> map;
    for (Order o : currentItems) {
        map.insert(std::make_pair(o.getDish().getName(), 0));
    }
    for (Order o : currentItems) {
        Dish temp = o.getDish();
        std::map<std::string, int>::iterator it = map.find(temp.getName());
        if (it != map.end()) {
            it->second +=1 ;
        }
    }
    std::vector<std::pair<std::string, int>> vect = sortMap(map);
    ui->listWidget->clear();
    for (auto& pair : vect) {
        ui->listWidget->addItem(QString::fromStdString(pair.first + " — ordered " + std::to_string(pair.second) + " times"));
    }
}

