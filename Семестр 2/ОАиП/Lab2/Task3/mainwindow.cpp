#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Stack.h"
#include <iostream>
#include <QMessageBox>
#include "Expression.h"
#include "VStack.h"

std::string globalPostfix;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableWidget->setColumnWidth(0, 200);
    ui->tableWidget->setColumnWidth(1, 200);
    ui->tableWidget->setColumnWidth(2, 200);
    addExpressionToTable(Expression("8.6 / (2.4 - 5.1) * (0.3 + 7.9)"));
    addExpressionToTable(Expression("(7.4 + 3.6)*(2.8 - 9.5) / 0.9"));
    addExpressionToTable(Expression("3.1 - (5.4 + 0.2 * 9.6) / 7.8"));
    addExpressionToTable(Expression("1.2 / 0.7 - ((9.3 + 6.5) * 8.4)"));

    addExpressionToTable(Expression("(9.1 + 0.6 * 2.4) / (3.7 - 8.5)"));
    addExpressionToTable(Expression("0.5 * (6.1 - 8.9) / (2.4 + 7.3)"));
    addExpressionToTable(Expression("7.6 / (4.8 + 3.5 - 9.1 * 0.2)"));
    addExpressionToTable(Expression("(0.3 - 6.7) / (8.4 + 9.5) * 1.2"));

    addExpressionToTable(Expression("9.7 * (8.2 - 3.6 + 4.1) / 0.5"));
    addExpressionToTable(Expression("(0.8 + 4.1) * ( 7.9 - 6.2) / 3.5"));
    addExpressionToTable(Expression("1.6 * (4.9 - 5.7) / (0.8 + 2.3)"));
    addExpressionToTable(Expression("8.5 / (0.3 * (2.4 + 7.9)) - 1.6"));

    addExpressionToTable(Expression("(5.6 + (7.4 / 8.9 - 3.1)) * 0.2"));
    addExpressionToTable(Expression("0.4 * (2.3 + 6.7) / (5.8 - 9.1)"));
    addExpressionToTable(Expression("5.6 - (3.2 / 0.9  * (1.7 + 4.8))"));
    //addExpressionToTable(Expression("a / (b - c)", 1, 2, 1, 1, 1));
    //addExpressionToTable(Expression("a / b - ((c + d) * c)", 1.2, 0.7, 9.3, 6.5, 8.4));
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

bool areBracesValid(std::string expression) {
    QString text = QString::fromStdString(expression);
    QTextStream in(&text);
    VStack<Bracket> stack;
    int lineIndex = 1;
    while(!in.atEnd()) {
        QString line = in.readLine();
        int colIndex = 1;
        for (QChar c : line) {
            if (c == '(') {
                stack.push_front(Bracket(lineIndex, colIndex, c));
            }
            else if (c == ')') {
                if (stack.empty()) {
                    return false;
                }
                if (stack.front().isSameType(c)) {
                    stack.pop_front();
                }
                else {
                    return false;
                }
            }
            colIndex++;
        }
        lineIndex++;
    }
    if (stack.empty()) {
        return true;
    }
    return false;
}

bool isValid(std::string expression) {
    bool bracesFlag = areBracesValid(expression);
    bool symbolsFlag = true;
    for (char c : expression) {
        if (c != '(' && c != ')' && (c < 48
                || c > 57) && c != '*' && c != '/' && c != '+' && c != '-' && c != '.' && c != ' ') {
            symbolsFlag = false;
        }
    }
    return bracesFlag && symbolsFlag && !expression.empty();
}

std::string convert(std::string expression);
void MainWindow::addExpressionToTable(Expression e) {
    ui->tableWidget->insertRow(ui->tableWidget->rowCount());
    ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 0, new QTableWidgetItem(QString::fromStdString(e.prefixForm)));
    double result = calculateExpression(e.prefixForm);
    ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 1, new QTableWidgetItem(QString::fromStdString(globalPostfix)));
    ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 2, new QTableWidgetItem(QString::number(result)));
}

/*void removeWhiteSpaces(std::string& str) {
    std::string result;
    for (char c : str) {
        if (c != ' ') {
            result.push_back(c);
        }
    }
    str = result;
}

int getPriorityBias(char a, char b) {
    if ((a == '+' && b == '-') ||
        (a == '-' && b == '+') ||
        (a == '*' && b == '/') ||
        (a == '/' && b == '*') ||
        (a == b)) {
        return 0;
    }
    else if ((a == '+' && b == '*') ||
             (a == '+' && b == '/') ||
             (a == '-' && b == '*') ||
             (a == '-' && b == '/')) {
        return -1;
    }
    return 1;
}

bool isOperation(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}*/

int priority(std::string alpha) {
  char alp = alpha[0];
  if (alp == '+' || alp == '-')
    return 1;
  if (alp == '*' || alp == '/')
    return 2;
  return 0;
}

std::string convert(Vector<std::string> infix) {
        int i = 0;
        std::string postfix = "";
        Node* head = NULL;
        Stack s;
        std::string ps = "";
        while (i != infix.size())
        {

            ps = infix[i];

            if (ps[0] == '-' and ps.size() != 1)
            {
                ps.replace(0, 1, "0");
            }

            if (ps >= "0" && ps <= "99999999999999999")
            {
                postfix += infix[i];
                postfix += " ";
                i++;
            }
            else if (ps == "(") {
                std::string str = "";
                str += infix[i];
                s.push(&head, str);
                i++;

            }
            else if (ps == ")") {
                while (s.top(head) != "(")
                    postfix += s.pop(head, &head);
                s.pop(head, &head);
                i++;
            }
            else {
                while (!s.isEmpty(&head) && priority(ps) <= priority(s.top(head))) {
                    postfix += s.pop(head, &head);
                }
                std::string str = "";
                str += infix[i];
                str += " ";
                s.push(&head, str);
                i++;
            }

        }
        while (!s.isEmpty(&head)) {
            postfix += s.pop(head, &head);
        }
        return postfix;
    /*removeWhiteSpaces(expression);
    std::string result;
    Stack<char> operations;
    for (char c : expression) {
        if (c == 'a' || c == 'b' || c =='c' || c == 'd' || c == 'e') {
            result.push_back(c);
        }
        else if (c == '+' || c == '-' || c == '*' || c == '/') {
            if (operations.empty()) {
                operations.push_front(c);
            }
            else {
                Stack<char> tempStack;
                while (!operations.empty()) {
                    char operation = operations.front();
                    if (operation != '(' && operation != ')' && getPriorityBias(c, operation) <= 0) {
                        result.push_back(operation);
                        operations.pop_front();
                    }
                    else if (operation != '(' && operation != ')' && getPriorityBias(c, operation) == 1) {
                        tempStack.push_front(operation);
                        operations.pop_front();
                    }
                    else if (operation == ')') {
                        tempStack.push_front(operation);
                        operations.pop_front();
                    }
                    else if (operation == '(') {
                        tempStack.push_front(operation);
                        operations.pop_front();
                        break;
                    }
                }
                while (!tempStack.empty()) {
                    operations.push_front(tempStack.front());
                    tempStack.pop_front();
                }
                operations.push_front(c);
            }
        }
        else if (c == '(') {
            operations.push_front(c);
        }
        else if (c == ')') {
            operations.push_front(c);
            Stack<char> tempStack;
            tempStack.push_front(c);
            /*while (0) {
                char temp = operations.front();
                if (isOperation(temp)) {
                    tempStack.push_front(temp);
                }
                else if (temp == '(') {
                    tempStack.push_front(temp);
                    operations.pop_front();
                    break;
                }
                operations.pop_front();
            }
            while (!operations.empty()) {
                char temp = operations.front();
                if (temp == '(') {
                    break;
                }
                result.push_back(temp);
                operations.pop_front();
            }
            while (!tempStack.empty()) {
                char temp = tempStack.front();
                if (temp == ')' || temp == '(') {
                    tempStack.pop_front();
                    continue;
                }
                operations.push_front(temp);
                tempStack.pop_front();
            }
        }
    }
    while (!operations.empty()) {
        char temp = operations.front();
        if (temp != ')' && temp != '(') {
            result.push_back(temp);
        }
        operations.pop_front();
    }
    std::string final;
    for (char c : result) {
        if (c != '(' && c != ')') {
            final.push_back(c);
        }
    }
    return final;*/
}

void MainWindow::on_calcButton_clicked()
{
    std::string expression = ui->textEdit->toPlainText().toStdString();
    try {
        if (isValid(expression)) {
            addExpressionToTable(Expression(expression));
        }
        else {
            QMessageBox msg;
            msg.setText("Wrong input");
            msg.exec();
        }
    } catch (...) {
        QMessageBox msg;
        msg.setText("Wrong input");
        msg.exec();
    }
}

/*double MainWindow::resolveVariable(std::string variable) {
    double a = ui->AValue->text().toDouble();
    double b = ui->BValue->text().toDouble();
    double c = ui->CValue->text().toDouble();
    double d = ui->DValue->text().toDouble();
    double e = ui->EValue->text().toDouble();
    if (variable == "a") return a;
    if (variable == "b") return b;
    if (variable == "c") return c;
    if (variable == "d") return d;
    if (variable == "e") return e;
    return std::stod(variable);
}

double operate(double a, std::string action, double b) {
    if (action == "+") {
        return a + b;
    }
    if (action == "-") {
        return b - a;
    }
    if (action == "*") {
        return a * b;
    }
    if (action == "/") {
        return b / a;
    }
    return -1;
}*/

double MainWindow::calculateExpression(std::string infix) {

    std::string inf = "";
        infix.erase(std::remove(infix.begin(), infix.end(), ' '), infix.end());

        std::string get_ = "";
        std::string arr = "";

        Vector<std::string> vector;

        for (int i = 0; i < infix.size(); ++i)
        {
            if (infix[i] != ' ') {

                if ((infix[i] == '-' and i == 0) or (infix[i] == '-' and infix[i - 1] == '('))
                {
                    arr += infix[i];
                }
                else if (infix[i] == '(')
                {
                    get_ += infix[i];
                    vector.push_back(get_);
                    get_.clear();
                }
                else if (infix[i] == ')')
                {
                    if (arr.size() != 0) {
                        vector.push_back(arr);
                        arr.clear();
                    }
                    get_ += infix[i];
                    vector.push_back(get_);
                    get_.clear();
                }
                else
                {
                    if (infix[i] != '+' and infix[i] != '-' and infix[i] != '*' and infix[i] != '/' and infix[i] != '%')
                    {
                        arr += infix[i];
                    }
                    else
                    {
                        if (arr.size() != 0) {
                            vector.push_back(arr);
                            arr.clear();
                        }
                        get_ += infix[i];
                        vector.push_back(get_);
                        get_.clear();
                    }
                }
            }
        }
        if (arr.size() != 0) vector.push_back(arr);
        std::string get_post = convert(vector);

        globalPostfix = get_post;

        Node* head = NULL;
        Stack container;
        Vector<std::string> lox1;
        std::string var;


        for (int i = 0; i < get_post.size(); ++i)
        {
            if (get_post[i] != ' ')
            {
                var += get_post[i];
            }
            else
            {
                lox1.push_back(var);
                var.clear();
            }
        }

        Vector<std::string> reversed;
        for (int i = lox1.size() - 1; i >= 0; --i) {

            reversed.push_back(lox1[i]);
        }

        for (int i = 0; i < reversed.size(); ++i) {

            container.push(&head, reversed[i]);
        }

        long double ans;

        Vector<std::string> storage;
        while (!(container.isEmpty(&head)))
        {
            std::string get_ar = container.pop(head, &head);

            if (get_ar == "+")
            {
                ans = atof(storage[storage.size() - 2].c_str()) + atof(storage[storage.size() - 1].c_str());
                storage.pop_back();
                storage.pop_back();
                storage.push_back(std::to_string(ans));
            }
            else if (get_ar == "-")
            {
                ans = atof(storage[storage.size() - 2].c_str()) - atof(storage[storage.size() - 1].c_str());
                storage.pop_back();
                storage.pop_back();
                storage.push_back(std::to_string(ans));
            }
            else if (get_ar == "*")
            {
                ans = atof(storage[storage.size() - 2].c_str()) * atof(storage[storage.size() - 1].c_str());
                storage.pop_back();
                storage.pop_back();
                storage.push_back(std::to_string(ans));
            }
            else if (get_ar == "/")
            {
                ans = atof(storage[storage.size() - 2].c_str()) / atof(storage[storage.size() - 1].c_str());
                storage.pop_back();
                storage.pop_back();
                storage.push_back(std::to_string(ans));
            }
            else
            {
                storage.push_back(get_ar);
            }

        };
    long double result = atof(storage[0].c_str());
    return result;
    /*Stack<std::string> symbols;
    for (char symbol : expression) {
        if (symbol == 'a' || symbol == 'b' || symbol =='c' || symbol == 'd' || symbol == 'e') {
            std::string temp;
            temp.push_back(symbol);
            symbols.push_front(temp);
        }
        else if (symbol == '/' || symbol == '*' || symbol =='-' || symbol == '+') {
            std::string leftOperand = symbols.front();
            symbols.pop_front();
            std::string rightOperand = symbols.front();
            symbols.pop_front();
            double loVal;
            double roVal;
                loVal = resolveVariable(leftOperand);
                roVal = resolveVariable(rightOperand);
            std::string temp;
            temp.push_back(symbol);
            symbols.push_front(std::to_string(operate(loVal, temp, roVal)));
        }
    }
    double result;
    try {
        result = std::stod(symbols.front());
    } catch (...) {
        result = -69.69;
    }
    return result;*/
}
