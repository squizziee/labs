#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

class Expression {
public:
    virtual double evaluate() {
        return 0;
    };
    virtual int const getType() {
        return 0;
    }
protected:
    Expression() {};
};

class Number : public Expression {
private:
    double value;
    int const type = 1;
public:
    Number(double value) {
        this->value = value;
    }

    double evaluate() {
        return value;
    }

    int const getType() {
        return type;
    }
};

class BinaryOperation : public Expression {
private:
    Expression* leftOperand;
    Expression* rightOperand;
    char operation;
    int const type = 2;
    const char* name;
public:
    BinaryOperation(Expression* a, char operation, Expression* b) {
        leftOperand = a;
        rightOperand = b;
        this->operation = operation;
    }

    double evaluate() {
        try {
            double a = leftOperand->evaluate();
            double b = rightOperand->evaluate();
            if (operation == '+') {
                return a + b;
            }
            else if (operation == '-') {
                return a - b;
            }
            else if (operation == '*') {
                return a * b;
            }
            else if (operation == '/') {
                return a / b;
            }
            else {
                return NAN;
            }
        }
        catch (...) {
            return NAN;
        }
        return NAN;
    }

    int const getType() {
        return type;
    }
};

bool checkEquals(Expression const* left, Expression const* right) {
    int* get_first = (int*)right;
    int* get_second = (int*)left;
    if (*get_first == *get_second) return true;
    else return false;
}

int main() {
    Expression* a = new Number(1);
    Expression* b = new Number(2);
    Expression* c = new BinaryOperation(new Number(4), '+', new Number(3));
    Expression* d = new BinaryOperation(new Number(5), '+', new Number(9));
    std::cout << checkEquals(b, a);
    //delete a;
    //delete b;
    //remove("tmp.txt");
}