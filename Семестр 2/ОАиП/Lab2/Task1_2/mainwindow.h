#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ArrayList.h"
#include "Employee.h"

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

    void on_searchDepartmentButton_clicked();

    void on_saveChangesButton_clicked();

    void on_deleteButton_clicked();

    void on_editButton_clicked();

    void on_sortButton_clicked();

    void on_searchExperienceButton_clicked();

private:
    std::string currentFileName;
    ArrayList<Employee> currentEmployees;
    void loadFromFile();
    void createTable();
    void clearTable();
    void addRow(QString, QString, QString, QString, QString);
    void setManipulationButtonsEnabled(bool);
    void setShowButtonsEnabled(bool);
    bool isAlreadyPresent(Employee&);
    void setMeme();
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
