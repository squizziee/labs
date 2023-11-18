#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QInputDialog>

void MainWindow::form_treeview(QTreeWidgetItem* parent, custom::binary_search_tree<int> tree) {
    parent->addChild(new QTreeWidgetItem(parent));
}

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
    QStringList nums = ui->lineEdit->text().split(",");
    for (auto& n : nums) {
        tree.insert(n.toStdString());
    }
    std::string a;
    std::string b;
    std::string c;
    tree.to_string(a, 0);
    tree.to_string(b, 1);
    tree.to_string(c, 2);
    ui->listWidget->addItem(QString::fromStdString(a));
    ui->listWidget->addItem(QString::fromStdString(b));
    ui->listWidget->addItem(QString::fromStdString(c));
}


void MainWindow::on_pushButton_2_clicked()
{
    bool ok;
    QString text = QInputDialog::getText(this, tr("Delete element"),
                                         tr("Choose value to remove"), QLineEdit::Normal,
                                         QString(), &ok);
    if (!ok) return;
    tree.remove(text.toStdString());
    ui->listWidget->clear();
    std::string a;
    std::string b;
    std::string c;
    tree.to_string(a, 0);
    tree.to_string(b, 1);
    tree.to_string(c, 2);
    ui->listWidget->addItem(QString::fromStdString(a));
    ui->listWidget->addItem(QString::fromStdString(b));
    ui->listWidget->addItem(QString::fromStdString(c));
}

