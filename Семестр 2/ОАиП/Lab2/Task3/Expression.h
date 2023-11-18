#ifndef EXPRESSION_H
#define EXPRESSION_H
#include <iostream>

struct Expression {
    std::string prefixForm;
    Expression(std::string prefixForm) :
        prefixForm(prefixForm) {}
};

#endif // EXPRESSION_H
