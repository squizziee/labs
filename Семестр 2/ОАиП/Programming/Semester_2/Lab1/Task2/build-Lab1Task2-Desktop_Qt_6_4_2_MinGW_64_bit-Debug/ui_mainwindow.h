/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QComboBox *comboBox;
    QListWidget *listWidget;
    QPushButton *editOrderButton;
    QPushButton *sortListButton;
    QPushButton *removeOrderButton;
    QPushButton *addOrderButton;
    QPushButton *openFileButton;
    QPushButton *popularDishesButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(499, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        comboBox = new QComboBox(centralwidget);
        comboBox->setObjectName("comboBox");
        comboBox->setEnabled(false);
        comboBox->setGeometry(QRect(20, 20, 191, 51));
        listWidget = new QListWidget(centralwidget);
        listWidget->setObjectName("listWidget");
        listWidget->setGeometry(QRect(220, 20, 256, 461));
        editOrderButton = new QPushButton(centralwidget);
        editOrderButton->setObjectName("editOrderButton");
        editOrderButton->setEnabled(false);
        editOrderButton->setGeometry(QRect(20, 80, 191, 41));
        editOrderButton->setCheckable(false);
        editOrderButton->setChecked(false);
        editOrderButton->setAutoExclusive(false);
        editOrderButton->setAutoDefault(false);
        editOrderButton->setFlat(false);
        sortListButton = new QPushButton(centralwidget);
        sortListButton->setObjectName("sortListButton");
        sortListButton->setEnabled(false);
        sortListButton->setGeometry(QRect(220, 500, 256, 41));
        removeOrderButton = new QPushButton(centralwidget);
        removeOrderButton->setObjectName("removeOrderButton");
        removeOrderButton->setEnabled(false);
        removeOrderButton->setGeometry(QRect(20, 130, 191, 41));
        addOrderButton = new QPushButton(centralwidget);
        addOrderButton->setObjectName("addOrderButton");
        addOrderButton->setEnabled(false);
        addOrderButton->setGeometry(QRect(20, 180, 191, 41));
        openFileButton = new QPushButton(centralwidget);
        openFileButton->setObjectName("openFileButton");
        openFileButton->setGeometry(QRect(20, 230, 191, 41));
        popularDishesButton = new QPushButton(centralwidget);
        popularDishesButton->setObjectName("popularDishesButton");
        popularDishesButton->setEnabled(false);
        popularDishesButton->setGeometry(QRect(20, 500, 191, 41));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 499, 25));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        editOrderButton->setDefault(false);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        editOrderButton->setText(QCoreApplication::translate("MainWindow", "Edit", nullptr));
        sortListButton->setText(QCoreApplication::translate("MainWindow", "Sort dishes by price", nullptr));
        removeOrderButton->setText(QCoreApplication::translate("MainWindow", "Remove", nullptr));
        addOrderButton->setText(QCoreApplication::translate("MainWindow", "Add", nullptr));
        openFileButton->setText(QCoreApplication::translate("MainWindow", "Import list", nullptr));
        popularDishesButton->setText(QCoreApplication::translate("MainWindow", "Popular dishes", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
