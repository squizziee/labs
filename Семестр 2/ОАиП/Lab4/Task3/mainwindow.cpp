#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "BraceStack.h"
#include <QFile>
#include <QMessageBox>
#include <QFileDialog>
#include <regex>
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

void MainWindow::on_openFileBtn_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, "Choose file",
                                                    QString(), "Code files (*.txt *.java *.cpp *.js)");
    if (filename.isEmpty()) {
        return;
    }
    QFile file(filename);
    if(!file.open(QIODevice::ReadOnly)) {
        QMessageBox::information(0, "error", file.errorString());
    }
    ui->textEdit->setText(file.readAll());
    file.close();
}

std::vector<std::string> getVariables(std::string text) {
    std::vector<std::string> strings;
        std::regex rgx("(int|bool|long|long long|long|double|float|std::string|long double|char|Vector)(<.+?>)?\\s*\\*?\\s*\\s*\\n*([\\w]+?)\\s?\\n?(=\\s?\\n?([A-Za-z0-9\\+\\-\\*\\/\\s])*\\s*)?;");
        std::smatch result;
        while (std::regex_search(text, result, rgx)) {
            strings.push_back(result.str());
            text = result.suffix();
        }
       return strings;
}

std::vector<std::string> getFunctionPrototypes(std::string text) {
    std::vector<std::string> strings;
        std::regex rgx("((const)\\s+?)?(auto|int|bool|long long|long|double|float|std::string|long double|char|void|std::vector)(<(int|bool|double)>)?([&]|[*]+?|(&&))?\\s*([A-Za-z_][A-Za-z0-9_]*)\\((((auto|int|bool|long long|long|double|float|std::string|long double|char|std::vector)(<(int|bool|long)>)?([&]|[*]+?|(&&))?\\s*[A-Za-z_0-9]+?,)*\\s*((auto|int|bool|long long|long|double|float|std::string|long double|char|std::vector|Vector)(<.+?>)?([&]|[*]+?|(&&))?\\s*[A-Za-z0-9_]+?))?\\)");
        std::smatch result;
        while (std::regex_search(text, result, rgx)) {
            strings.push_back(result.str());
            text = result.suffix();
        }
       return strings;
}

std::vector<std::string> getMatches(std::string text, std::regex& regex) {
    std::vector<std::string> matches;
    std::smatch segResult;
    while (std::regex_search(text, segResult, regex)) {
        matches.push_back(segResult.str());
        text = segResult.suffix();
    }
    return matches;
}

/*void MainWindow::on_parseBtn_clicked()
{
    ui->variableBox->clear();
    ui->functionBox->clear();
    variableInfo.clear();
    /*std::string text = ui->textEdit->toPlainText().toStdString();
    std::regex rgx("(int|bool|long|long long|long|double|float|std::string|long double|char|Vector)(<.+?>)?\\s*\\n*([A-Za-z_][A-Za-z0-9_]*)\\s?\\n?=\\s?\\n?([A-Za-z0-9\\+\\-\\*\\/\\s])*\\s*;");
    std::smatch result;
    while (std::regex_search(text, result, rgx)) {
        /*BraceStack stack;
        stack.push_front('{');
        size_t start = result.position();
        size_t end;
        size_t index = start;
        for (; !stack.empty() && index < text.size(); index++) {
            if (text[index] == '{') {
                stack.push_front(text[index]);
            }
            if (text[index] == '}') {
                stack.pop_front();
            }
        }
        end = index;
        std::string segment = text.substr(start, end - start - 1);
        std::vector<std::string> changes;
        std::cout << "\n" << result.str(3) << "\n";
        std::regex segRgx(std::string("(") + result.str(3) + ")\\s*(\\+=|-=|\\/=|=|\\*=)\\s*([\"']?[A-Za-z0-9_\\*\\+\\s*]*[\"']?)");
        std::smatch segResult;
        while (std::regex_search(segment, segResult, segRgx)) {
            changes.push_back(segResult.str());
            segment = segResult.suffix();
        }
        variableInfo.push_back(changes);
        text = result.suffix();
    }
        QStringList lines = ui->textEdit->toPlainText().split('\n');
        for (int i = 0; i < lines.size(); i++) {
            auto tmp = lines[i].toStdString();
            std::regex regex("([\\w]+?)\\s*(\\+=|-=|\\/=|=|\\*=)\\s*([\"']?[A-Za-z0-9_\\*\\+\\s*]*[\"']?)");
            std::smatch tmpResult;
            while (std::regex_search(tmp, tmpResult, regex)) {
                changes.push_back(RegexMatchInfo(tmpResult.str(), i, tmpResult.position()));
                tmp = tmpResult.suffix();
            }
        }
        std::string toShow;
        for (auto& info : changes) {
            toShow += "[" + std::to_string(info.row) + ":" + std::to_string(info.column) + "] " + info.expression + "\n";
        }
        ui->variableTextEdit->setText(QString::fromStdString(toShow));
        /*for (auto& i : getMatches(text, rgx)) {
            ui->variableBox->addItem(QString::fromStdString(i));
        }*/

        /*for (auto& i : getFunctionPrototypes(ui->textEdit->toPlainText().toStdString())) {
            ui->functionBox->addItem(QString::fromStdString(i));
        }

}*/

void MainWindow::loadLocalVariablesIntoUI(std::regex rgx) {
    localVariables.clear();
    std::string text = ui->textEdit->toPlainText().toStdString();
    /*while (std::regex_search(text, result, oBrace)) {
        while (std::regex_search(text, result, rgx)) {
            localVariables.push_back(RegexMatchInfo(result.str(), ))
            text = result.suffix();
        }
        text = result.suffix();
    }*/
    BraceStack stack;
    size_t begin = 0, end = 0;
    size_t lineIndex = 1;
    bool braceNotClosed = false;
    for (size_t i = 0; i < text.size(); i++) {
        if (text[i] == '{') {
            if (stack.empty()) {
                begin = i;
                braceNotClosed = true;
            }
            stack.push_front('{');
        }
        else if (text[i] == '}') {
            stack.pop_front();
        }
        else if (text[i] == '\n') {
            lineIndex++;
        }
        if (stack.empty() && braceNotClosed) {
            end = i;
            std::string segment = text.substr(begin, end - begin - 1);
            QStringList lines = QString::fromStdString(segment).split("\n");
            for (long long j = 0; j < lines.size(); j++) {
                auto line = lines[j].toStdString();
                std::smatch segResult;
                //std::cout << segResult.str() << "\n";
                while (std::regex_search(line, segResult, rgx)) {
                    localVariables.push_back(RegexMatchInfo(segResult.str(), lineIndex, segResult.position()));
                    line = segResult.suffix();
                }
            }
            braceNotClosed = false;
        }
    }
    std::string toShow;
    for (auto& info : localVariables) {
        toShow += "[" + std::to_string(info.row) + ":" + std::to_string(info.column) + "] " + info.expression + "\n";
    }
    ui->localVariableTextEdit->setText(QString::fromStdString(toShow));
}

void MainWindow::loadChangesIntoUI(std::regex rgx, bool trunc) {
    QStringList lines = ui->textEdit->toPlainText().split('\n');
    for (int i = 0; i < lines.size(); i++) {
        auto tmp = lines[i].toStdString();
        std::smatch tmpResult;
        while (std::regex_search(tmp, tmpResult, rgx)) {
            changes.push_back(RegexMatchInfo(tmpResult.str().substr(0, tmpResult.str().size() - trunc), i, tmpResult.position()));
            tmp = tmpResult.suffix();
        }
    }
    std::string toShow;
    for (auto& info : changes) {
        toShow += "[" + std::to_string(info.row) + ":" + std::to_string(info.column) + "] " + info.expression + "\n";
    }
    ui->variableTextEdit->setText(QString::fromStdString(toShow));
}

void MainWindow::on_parseVCBtn_clicked()
{
    ui->variableTextEdit->clear();
    std::regex binary("([\\w]+?)(\\[.+?\\])?\\s*(\\+=|-=|\\/=|=|\\*=)\\s*([\"']?[A-Za-z0-9_\\[\\]\\*\\+\\s*]*[\"']?)");
    std::regex unaryPost("([\\w]+?)(\\[.+?\\])?\\s*(\\+\\+|\\-\\-)([);])");
    std::regex unaryPre("(\\+\\+|\\-\\-)\\s*([\\w]+?)(\\[.+?\\])?([;)])");
    loadChangesIntoUI(binary, 0);
    loadChangesIntoUI(unaryPost, 1);
    loadChangesIntoUI(unaryPre, 1);
}


void MainWindow::on_parseFOBtn_clicked()
{
    std::string text;
    auto tmp = ui->textEdit->toPlainText().toStdString();
    ui->functionTextEdit->clear();
    for (auto& str : getFunctionPrototypes(tmp)) {

        text += str + "\n";
    }
    ui->functionTextEdit->setText(QString::fromStdString(text));
}


void MainWindow::on_parseLVBtn_clicked()
{
    ui->localVariableTextEdit->clear();
    loadLocalVariablesIntoUI(std::regex("(int|bool|long|long long|long|double|float|std::string|long double|char|Vector)(<.+?>)?\\s*\\*?\\s*\\s*\\n*([\\w]+?)\\s?\\n?(=\\s?\\n?([A-Za-z0-9\\+\\-\\*\\/\\s])*\\s*)?;"));
}


void MainWindow::on_parseVBtn_clicked()
{
    ui->allVariablesTextEdit->clear();
    std::string text = ui->textEdit->toPlainText().toStdString();
    std::string toShow;
    for (auto& i : getVariables(text)) {
        toShow += i + "\n";
    }
    ui->allVariablesTextEdit->setText(QString::fromStdString(toShow));
}

std::vector<int> MainWindow::countDepths() {
    localVariables.clear();
    std::string text = ui->textEdit->toPlainText().toStdString();
    BraceStack stack;
    bool braceNotClosed = false;
    std::vector<int> result;
    int depth = 0;
    for (size_t i = 0; i < text.size(); i++) {
        if (text[i] == '{') {
            if (stack.empty()) {
                braceNotClosed = true;
            }
            depth++;
            stack.push_front('{');
        }
        else if (text[i] == '}') {
            stack.pop_front();
        }
        if (stack.empty() && braceNotClosed) {
            result.push_back(depth);
            depth = 0;
            braceNotClosed = false;
        }
    }
    return result;
}


void MainWindow::on_parseMiscBtn_clicked()
{
    //(class|struct)\s*([\w]+?)\s*({(.|\n)*});
    std::string text = ui->textEdit->toPlainText().toStdString();
    std::regex rgx("(class|struct)\\s*([\\w]+?)\\s*\\{[\\w\\;\\.\\,\\n\\s]*\\};");
    std::regex rgx2("(int|bool|long|long long|long|double|float|long double|char|)\\s*\\n*([\\w]+?)\\[\\]\\s?\\n?=\\s?\\n?([A-Za-z0-9\\+\\-\\*\\/\\s]+?);");
    int count1 = getMatches(text, rgx).size();
    int count2 = getMatches(text, rgx2).size();
    ui->countEdit->setText(QString::number(count1 + count2));
    std::string toShow;
    for (auto& i : countDepths()) {
        toShow += std::to_string(i) + ", ";
    }
    ui->depthEdit->setText(QString::fromStdString(toShow.substr(0, toShow.size() - 2)));
}


void MainWindow::on_parseFOBtn_2_clicked()
{
    std::vector<std::string> matches;
    std::vector<std::smatch> tmp;
    std::vector<std::string> final;
    std::smatch segResult;
    std::regex regex("((const)\\s+?)?(auto|int|bool|long long|long|double|float|std::string|long double|char|void|std::vector)(<(int|bool|double)>)?([&]|[*]+?|(&&))?\\s*([\\w]+?)\\((((auto|int|bool|long long|long|double|float|std::string|long double|char|std::vector)(<(int|bool|long)>)?([&]|[*]+?|(&&))?\\s*[A-Za-z_0-9]+?,)*\\s*((auto|int|bool|long long|long|double|float|std::string|long double|char|std::vector|Vector)(<.+?>)?([&]|[*]+?|(&&))?\\s*[A-Za-z0-9_]+?))?\\)");
    QStringList lines = ui->textEdit->toPlainText().split("\n");
    for (long long i = 0; i < lines.size(); i++) {
        auto line = lines[i].toStdString();
        while (std::regex_search(line, segResult, regex)) {
            tmp.push_back(segResult);
            matches.push_back(segResult.str(1));
            line = segResult.suffix();
        }
    }
    std::string toShow;
    for (auto& i : matches) {
        toShow += i + "\n";
    }
    ui->functionOverloadTextEdit->setText(QString::fromStdString(toShow));
}

void MainWindow::on_parseLEBtn_clicked()
{
    //std::string text = ui->textEdit->
    //std::vector<std::string> result;
    //std::vector<std::string> v1 = getMatches(ui->textEdit->toPlainText().toStdString(), std::regex("while(\\s*false\\s*)"));
}

