#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "LinkedList.h"
#include "Client_.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_openFileButton_clicked();

    void on_addButton_clicked();

    void on_searchNameButton_clicked();

    void on_removeDuplicatesButton_clicked();

    void on_searchDateButton_clicked();

    void on_saveChangesButton_clicked();

    void on_deleteButton_clicked();

    void on_editButton_clicked();

    void on_sortButton_clicked();

    void on_completedOrdersButton_clicked();

    void on_uncompletedOrdersButton_clicked();

    void on_allOrdersButton_clicked();

private:
    std::string currentFileName;
    LinkedList<Client> currentClients;
    void loadFromFile();
    void createTable();
    void clearTable();
    void addRow(QString, QString, QString, QString, QString);
    void setManipulationButtonsEnabled(bool);
    void setShowButtonsEnabled(bool);
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
