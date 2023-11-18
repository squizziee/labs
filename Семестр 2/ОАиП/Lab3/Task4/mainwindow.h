#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Vector.h"

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
    void on_capacityBtn_clicked();

    void on_emplaceBtn_clicked();

    void on_emplaceBtn_2_clicked();

    void on_dataBtn_clicked();

    void on_eraseBtn_clicked();

    void on_showVectorBtn_clicked();

    void on_maxSizeBtn_clicked();

    void on_resizeBtn_clicked();

private:
    Ui::MainWindow *ui;
    void printVector();
    Vector<int> vector;
};
#endif // MAINWINDOW_H
