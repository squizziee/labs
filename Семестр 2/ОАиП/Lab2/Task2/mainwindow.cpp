#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <Stack.h>
#include <iostream>

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

class Bracket {
private:
    int line;
    int col;
    QChar symbol;
public:
    Bracket() {}
    Bracket(int line, int col, QChar symbol) :
        line(line), col(col), symbol(symbol) {}

    bool isSameType(QChar c) {
        if ((symbol == '(' && c == ')') ||
            (symbol == '[' && c == ']') ||
            (symbol == '{' && c == '}')) {
            return true;
        }
        return false;
    }

    int getLine() {
        return line;
    }

    int getCol() {
        return col;
    }

    QChar getSymbol() {
        return symbol;
    }
};

void MainWindow::loadFileIntoTextEdit(QString url) {
    QFile file(url);
    if(!file.open(QIODevice::ReadOnly)) {
        QMessageBox::information(0, "error", file.errorString());
    }
    ui->textEdit->setText(file.readAll());
    file.close();
}

void MainWindow::on_openFileButton_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, "Choose file",
                                                    QString(), "Code files (*.txt *.java *.cpp *.js)");
    if (filename.isEmpty()) {
        return;
    }
    loadFileIntoTextEdit(filename);
}


void MainWindow::on_processButton_clicked()
{
    QString text = ui->textEdit->toPlainText();
    QTextStream in(&text);
    Stack<Bracket> stack;
    int lineIndex = 1;
    while(!in.atEnd()) {
        QString line = in.readLine();
        int colIndex = 1;
        for (QChar c : line) {
            if (c == '(' || c == '{' || c == '[') {
                stack.push_front(Bracket(lineIndex, colIndex, c));
            }
            else if (c == ')' || c == '}' || c == ']') {
                if (stack.empty()) {
                    QMessageBox msg(this);
                    msg.setText(QString("Bracket not opened: ") + QString::number(lineIndex) + QString("::") + QString::number(colIndex));
                    msg.exec();
                    return;
                }
                if (stack.front().isSameType(c)) {
                    stack.pop_front();
                }
                else {
                    QMessageBox msg(this);
                    msg.setText(QString("Wrong bracket: ") + QString::number(lineIndex) + QString(":") + QString::number(colIndex));
                    msg.exec();
                    return;
                }
            }
            colIndex++;
        }
        lineIndex++;
    }
    if (stack.empty()) {
        QMessageBox msg(this);
        msg.setText("Success");
        msg.exec();
        return;
    }
    else {
        Bracket bracket;
        while (!stack.empty()) {
            bracket = stack.front();
            stack.pop_front();
        }
        QMessageBox msg(this);
        msg.setText(QString("Bracket not closed: ") + QString::number(bracket.getLine()) + QString(":")
                    + QString::number(bracket.getCol()));
        msg.exec();
        return;
    }
}

