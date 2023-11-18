#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QComboBox>
#include "Dish.h"
#include <Vector.h>

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
    void handleOpenFileButton();
    void handleComboBoxChange();
    void handleRemoveOrderButton();
    void handleEditOrderButton();
    void handleAddOrderButton();
    void handleSortListButton();
    void handlePopularDishesButton();
private:
    std::vector<Order> currentItems;
    void refresh();
    void loadFileIntoUI();
    void loadChangesIntoFile();
    void enableButtons();
    void disableButtons();
    std::string currentFileName{""};
    QComboBox *orderComboBox;
    QPushButton *openFileBtn;
    QPushButton *removeOrderBtn;
    QPushButton *editOrderBtn;
    QPushButton *addOrderBtn;
    QPushButton *sortListBtn;
    QPushButton *popularDishesBtn;
    Ui::MainWindow *ui;
    //EditWindow *editWindow;
};
#endif // MAINWINDOW_H
