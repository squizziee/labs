#ifndef CLIENT__H
#define CLIENT__H

#pragma once
#include <iostream>
#include <cstring>

class Client {
private:
    static int const NAME_SIZE = 32,
                     HOME_ADDRESS_SIZE = 64,
                     DATE_SIZE = 32;
    int number;
    char name[NAME_SIZE];
    char homeAddress[HOME_ADDRESS_SIZE];
    char date[DATE_SIZE];
    bool completed;
public:
    Client() {}
    Client(int number, std::string name, std::string homeAddress, std::string date, bool completed) {
        this->number = number;
        strcpy_s(this->name, NAME_SIZE, name.c_str());
        strcpy_s(this->homeAddress, HOME_ADDRESS_SIZE, homeAddress.c_str());
        strcpy_s(this->date, DATE_SIZE, date.c_str());
        this->completed = completed;
    }

    bool operator==(Client& cl) {
        return this->name == cl.name && this->homeAddress == cl.homeAddress;
    }

    bool equals(Client& cl) {
        return this->name == cl.name && this->homeAddress == cl.homeAddress;
    }

    void setNumber(int number) {
        this->number = number;
    }

    int getNumber() {
        return number;
    }

    void setName(std::string name) {
        strcpy_s(this->name, NAME_SIZE, name.c_str());
    }

    std::string getName() {
        return std::string(name);
    }

    void setHomeAddress(std::string homeAddress) {
        strcpy_s(this->homeAddress, HOME_ADDRESS_SIZE, homeAddress.c_str());
    }

    std::string getHomeAdress() {
        return std::string(homeAddress);
    }

    void setDate(std::string date) {
        strcpy_s(this->date, DATE_SIZE, date.c_str());
    }

    std::string getDate() {
        return std::string(date);
    }

    void setCompleted(bool completed) {
        this->completed = completed;
    }

    bool isCompleted() {
        return completed;
    }

    //friend bool contains(LinkedList<Client>& list, Client& toFind);
};


#endif // CLIENT__H
