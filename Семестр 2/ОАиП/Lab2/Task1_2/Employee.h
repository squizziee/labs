#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <iostream>
#include "Date.h"

class Employee {
private:
    std::string name;
    int departmentID;
    std::string position;
    std::string worksSince;
public:
    Employee() {}
    Employee(std::string name, int departmentID, std::string position, std::string worksSince) {
        this->name = name;
        this->departmentID = departmentID;
        this->position = position;
        this->worksSince = worksSince;
    }

    ~Employee() {

    }

    void setName(std::string name) {
        this->name = name;
    }

    std::string getName() {
        return name;
    }

    int getDepartmentID() {
        return departmentID;
    }

    void setDepartmentID(int departmentID) {
        this->departmentID = departmentID;
    }

    void setPosition(std::string position) {
        this->position = position;
    }

    std::string getPosition() {
        return position;
    }

    void setDate(std::string worksSince) {
        this->worksSince = worksSince;
    }

    int getWorkExperience() {
        auto now = Date::currentDate();
        auto since = Date(worksSince);
        if (since.isCorrupted()) {
            return -1;
        }
        return since.daysTill(now);
    }

    std::string getDate() {
        return worksSince;
    }
};

#endif // EMPLOYEE_H
