#pragma once
#include <iostream>
#include "LinkedList.h"

class Client {
private:
    static int const NAME_SIZE = 32,
                     HOME_ADDRESS_SIZE = 64,
                     DATE_SIZE = 32;
    int number;
    char name[NAME_SIZE];
    char homeAddress[HOME_ADDRESS_SIZE];
    char date[DATE_SIZE];
public:
    Client() {}
    Client(int number, std::string name, std::string homeAddress, std::string date) {
        this->number = number;
        strcpy_s(this->name, NAME_SIZE, name.c_str());
        strcpy_s(this->homeAddress, HOME_ADDRESS_SIZE, homeAddress.c_str());
        strcpy_s(this->date, DATE_SIZE, date.c_str());
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

    //friend bool contains(LinkedList<Client>& list, Client& toFind);
};

bool contains(LinkedList<Client>& list, Client& toFind) {
    for (int i = 0; i < list.getSize(); i++) {
        //std::cout << list[i].toString() << "|";
        //std::cout << toFind.toString() << "\n";
        if (list[i].getName() == toFind.getName() &&
            list[i].getHomeAdress() == toFind.getHomeAdress()) {
            //std::cout << "found\n";
            return true;
        }
    }
    return false;
}
void removeDuplicates(LinkedList<Client>& list) {
    LinkedList<Client> result;
    for (int i = 0; i < list.getSize(); i++) {
        Client temp = list[i];
        if (!contains(result, temp)) {
            result.add(temp);
        }
    }
    list = result;
}
