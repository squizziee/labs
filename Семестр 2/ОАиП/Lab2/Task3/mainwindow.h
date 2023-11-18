#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "Expression.h"

#include <QMainWindow>

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
    void on_calcButton_clicked();

private:
    Ui::MainWindow *ui;
    double calculateExpression(std::string);
    double resolveVariable(std::string);
    void addExpressionToTable(Expression);
};
#endif // MAINWINDOW_H
