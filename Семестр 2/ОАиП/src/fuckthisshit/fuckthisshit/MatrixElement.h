#pragma once
#include <iostream>
#include <string>
#include "pch.h"

struct MatrixElement {
private:
    double value;
    int row, column;
public:
    MatrixElement(double value, int row, int column) {
        this->value = value;
        this->row = row;
        this->column = column;
    }

    double getValue() {
        return value;
    }

    int getRow() {
        return row;
    }

    int getColumn() {
        return column;
    }

    std::string toString() {
        return "{value: " + std::to_string(this->getValue()) +
            ", row: " + std::to_string(this->getRow()) +
            ", column: " + std::to_string(this->getColumn()) + "}";
    }

    bool operator==(const MatrixElement toCompare) {
        return this->value == toCompare.value &&
            this->row == toCompare.row &&
            this->column == toCompare.column;
    }
};
