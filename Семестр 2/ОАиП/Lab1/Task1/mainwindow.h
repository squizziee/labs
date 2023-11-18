#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>

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
    void handleAddDateButton();
    void handleSubmitBdayButton();
    void handleEditDateButton();
private:
    QString currentFileName;
    QPushButton *btn;
    QPushButton *addDateBtn;
    QPushButton *submitBdayBtn;
    QPushButton *editDateBtn;
    Ui::MainWindow *ui;
    void createTable(std::string);
    void addRow(QString, QString, QString, QString, QString);
    void refresh();
};
#endif // MAINWINDOW_H
