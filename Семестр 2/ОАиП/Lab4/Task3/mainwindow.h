#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>
#include <regex>

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
    void on_openFileBtn_clicked();

    void on_parseVCBtn_clicked();

    void on_parseFOBtn_clicked();

    void on_parseLVBtn_clicked();

    void on_parseVBtn_clicked();

    void on_parseMiscBtn_clicked();

    void on_parseFOBtn_2_clicked();

    void on_parseLEBtn_clicked();

private:
    void loadChangesIntoUI(std::regex, bool);
    void loadLocalVariablesIntoUI(std::regex);
    std::vector<int> countDepths();
    struct RegexMatchInfo {
        std::string expression;
        size_t row;
        size_t column;
        RegexMatchInfo() {}
        RegexMatchInfo(std::string expression, size_t row, size_t column) {
            this->expression = expression;
            this->row = row;
            this->column = column;
        }
    };
    Ui::MainWindow *ui;
    std::vector<RegexMatchInfo> changes;
    std::vector<RegexMatchInfo> localVariables;
};
#endif // MAINWINDOW_H
