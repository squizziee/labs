#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Vector.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    Pair<Vector<int>, Vector<Pair<int, double>>> a;
    a.a = Vector<int>({1, 2, 3});
    a.b = Vector<Pair<int, double>>({Pair<int, double>(1, 2), Pair<int, double>(1, 3), Pair<int, double>(1, 4)});

    vector.push_back(a);

    Pair<Vector<int>, Vector<Pair<int, double>>> b;
    b.a = Vector<int>({4, 5, 6});
    b.b = Vector<Pair<int, double>>({Pair<int, double>(11, 2), Pair<int, double>(45, 3), Pair<int, double>(0, 4)});

    vector.push_back(b);

    Pair<Vector<int>, Vector<Pair<int, double>>> c;
    c.a = Vector<int>({14, 69, 88});
    c.b = Vector<Pair<int, double>>({Pair<int, double>(0, 0), Pair<int, double>(-47, 15), Pair<int, double>(13, 67)});

    vector.push_back(a);

    for (auto& el : vector) {
        std::string left;
        for (int i : el.a) {
            left += std::to_string(i) + ", ";
        }
        std::string right;
        for (auto& i : el.b) {
            right += i.toString() + ", ";
        }
        QString item = QString::fromStdString(left.substr(0, left.size() - 2) + " - " + right.substr(0, right.size() - 2));
        ui->listWidget->addItem(item);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

