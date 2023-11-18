/********************************************************************************
** Form generated from reading UI file 'editwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITWINDOW_H
#define UI_EDITWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_EditWindow
{
public:
    QLineEdit *tableEdit;
    QLineEdit *dishNameEdit;
    QLineEdit *dishDescEdit;
    QLineEdit *dishPriceEdit;
    QLineEdit *dishQuantityEdit;
    QPushButton *saveButton;
    QPushButton *discardButton;

    void setupUi(QDialog *EditWindow)
    {
        if (EditWindow->objectName().isEmpty())
            EditWindow->setObjectName("EditWindow");
        EditWindow->resize(400, 300);
        tableEdit = new QLineEdit(EditWindow);
        tableEdit->setObjectName("tableEdit");
        tableEdit->setGeometry(QRect(20, 20, 361, 28));
        dishNameEdit = new QLineEdit(EditWindow);
        dishNameEdit->setObjectName("dishNameEdit");
        dishNameEdit->setGeometry(QRect(20, 60, 361, 28));
        dishDescEdit = new QLineEdit(EditWindow);
        dishDescEdit->setObjectName("dishDescEdit");
        dishDescEdit->setGeometry(QRect(20, 100, 361, 28));
        dishPriceEdit = new QLineEdit(EditWindow);
        dishPriceEdit->setObjectName("dishPriceEdit");
        dishPriceEdit->setGeometry(QRect(20, 140, 361, 28));
        dishQuantityEdit = new QLineEdit(EditWindow);
        dishQuantityEdit->setObjectName("dishQuantityEdit");
        dishQuantityEdit->setGeometry(QRect(20, 180, 361, 28));
        saveButton = new QPushButton(EditWindow);
        saveButton->setObjectName("saveButton");
        saveButton->setGeometry(QRect(300, 250, 83, 29));
        discardButton = new QPushButton(EditWindow);
        discardButton->setObjectName("discardButton");
        discardButton->setGeometry(QRect(210, 250, 83, 29));

        retranslateUi(EditWindow);

        QMetaObject::connectSlotsByName(EditWindow);
    } // setupUi

    void retranslateUi(QDialog *EditWindow)
    {
        EditWindow->setWindowTitle(QCoreApplication::translate("EditWindow", "Dialog", nullptr));
        saveButton->setText(QCoreApplication::translate("EditWindow", "Save", nullptr));
        discardButton->setText(QCoreApplication::translate("EditWindow", "Discard", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EditWindow: public Ui_EditWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITWINDOW_H
