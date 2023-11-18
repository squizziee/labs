#include <iostream>
#include <fstream>
#include <string>
#include "../Lab8/CVector.h"
#include <regex>

class Date {
private:
    std::string day;
    std::string month;
    std::string year;
public:
    Date() {}

    Date(std::string input) {
        setDate(input);
    }

    bool setDate(std::string input) {
        bool match = isDateFormat(input);
        if (!match) {
            return false;
        }
        int pointer = 0;
        std::string _day;
        std::string _month;
        std::string _year;
        for (; input[pointer] != '.'; pointer++) {
            _day.push_back(input[pointer]);
        }
        pointer++;
        for (; input[pointer] != '.'; pointer++) {
            _month.push_back(input[pointer]);
        }
        pointer++;
        for (; pointer < input.size(); pointer++) {
            _year.push_back(input[pointer]);
        }
        int iDay = std::stoi(_day);
        int iMonth = std::stoi(_month);
        int iYear = std::stoi(_year);
        if (iDay <= 31 && iMonth <= 12 && iYear > 0 && iMonth > 0 && iDay > 0) {
            this->day = _day;
            this->month = _month;
            this->year = _year;
            return true;
        }
        return false;
    }

    ~Date() {}

    bool isDateFormat(std::string input) {
        std::regex rx("[0-9]{2}\\.[0-9]{2}\\.[0-9]{4}");
        bool match = std::regex_match(input.c_str(), rx);
        return match;
    }

    std::string toString() {
        std::string temp;
        temp.append(day);
        temp.push_back('.');
        temp.append(month);
        temp.push_back('.');
        temp.append(year);
        //std::cout << day << "*";
        return temp;
    }
};

class Client {
private:
    std::string name;
    std::string address;
    int id;
    Date date;

    bool hasForbiddenSymbols(std::string str) {
        for (char c : str) {
            if (c == ',' || c == '.' || c == '\n') {
                return true;
            }
        }
        return false;
    }
public:
    Client() {

    }

    Client(std::string name, std::string address, int id, std::string date) {
        setName(name);
        setAddress(address);
        this->id = id;
        setDate(date);
    }

    ~Client() {};

    bool operator==(Client& cl) {
        return this->name == cl.name && this->address == cl.address;
    }

    std::string toString() {
        std::string temp;
        temp.append(name);
        temp.append(",");
        temp.append(address);
        temp.append(",");
        temp.append(date.toString());
        return temp;
    }

    bool setName(std::string name) {
        if (!hasForbiddenSymbols(name)) {
            this->name = name;
            return true;
        }
        return false;
    }

    bool setAddress(std::string address) {
        if (!hasForbiddenSymbols(name)) {
            this->address = address;
            return true;
        }
        return false;
    }

    bool setDate(std::string input) {
        Date temp;
        if (temp.setDate(input)) {
            this->date = temp;
            return true;
        }
        return false;
    }
};

int inputControl(int lBound, int hBound) {
    int x;
    while (true) {
        std::cin >> x;
        while (std::cin.peek() == ' ')
            std::cin.ignore(1, ' ');
        if (std::cin.fail() || std::cin.peek() != '\n' || !(x >= lBound && x <= hBound)) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "[Invalid input, try again]: ";
        }
        else {
            return x;
        }
    }
}

void clearAndWriteToFile(std::ofstream& file, CVector<Client>& arr) {
    file.open("data.txt", std::ofstream::out | std::ofstream::trunc);
    file.close();
    file.open("data.txt", std::ofstream::app);
    for (Client cl : arr) {
        file << cl.toString() << "\n";
    }
    file.close();
}

void writeToFile(std::ofstream& file, Client client) {
    file.open("data.txt", std::ofstream::app);
    file << client.toString() << "\n";
    file.close();
}

CVector<Client> readFromFile(std::ifstream& file) {
    file.open("data.txt");
    CVector<Client> temp;
    std::string data;
    int count = 0;
    while (getline(file, data)) {
        int pointer;
        std::string name;
        for (pointer = 0; data[pointer] != ','; pointer++) {
            name.push_back(data[pointer]);
        }
        std::string address;
        pointer++;
        for (; data[pointer] != ','; pointer++) {
            address.push_back(data[pointer]);
        }
        pointer++;
        std::string date;
        for (; pointer < data.size(); pointer++) {
            date.push_back(data[pointer]);
        }
        Client client(name, address, ++count, date);
        temp.push_back(client);
    }
    file.close();
    return temp;
}

void editClient(Client client, std::ifstream& fileIn, std::ofstream& fileOut) {
    CVector<Client> vect = readFromFile(fileIn);
    CVector<Client> newVect;
    for (Client element : vect) {
        if (element == client) {
            std::cout << "[What info do you want to edit? (1 - name, 2 - address, 3 - date)]: ";
            int fieldID = inputControl(1, 3);
            if (fieldID == 1) {
                nameInput:
                std::string newName;
                std::cin >> newName;
                if (!element.setName(newName)) {
                    std::cout << "[Invalid input, \'.\', \',\', \'\\n\' are not allowed, try again]: ";
                    goto nameInput;
                }
            }
            else if (fieldID == 2) {
                addressInput:
                std::string newAddress;
                std::cin >> newAddress;
                if (!element.setAddress(newAddress)) {
                    std::cout << "[Invalid input, \'.\', \',\', \'\\n\' are not allowed, try again]: ";
                    goto addressInput;
                }
            }
            else if (fieldID == 3) {
                dateInput:
                std::string newDate;
                std::cin >> newDate;
                std::regex rx("[0-9]{2}\\.[0-9]{2}\\.[0-9]{4}");
                bool match = std::regex_match(newDate.c_str(), rx);
                if (!match) {
                    std::cout << "[Invalid input, date format is DD.MM.YYYY, try again]: ";
                    goto dateInput;
                }
            }
        }
        newVect.push_back(element);
    }
    clearAndWriteToFile(fileOut, newVect);
}

void deleteClient(Client client, std::ifstream& fileIn, std::ofstream& fileOut) {
    CVector<Client> vect = readFromFile(fileIn);
    CVector<Client> temp;
    for (Client element : vect) {
        if (!(element == client)) {
            temp.push_back(element);
        }
    }
    clearAndWriteToFile(fileOut, temp);
}

void filter(std::ifstream& in, std::ofstream& out) {
    CVector<Client> vect = readFromFile(in);
    CVector<Client> temp;
    for (Client client : vect) {
        bool alreadyPresent = false;
        for (Client element : temp) {
            if (element == client) {
                alreadyPresent = true;
            }
        }
        if (!alreadyPresent) {
            temp.push_back(client);
        }
    }
    clearAndWriteToFile(out, temp);
}

void printFile(std::ifstream& file) {
    file.open("data.txt");
    std::string data;
    while (getline(file, data)) {
        std::cout << data << "\n";
    }
    file.close();
}

int main()
{
    std::ifstream fin;
    std::ofstream fout;
    while (1) {
        std::cout << "[Choose action (1 - show structures, 2 - add structure, 3 - delete structure, 4 - edit structure)]: ";
        int action = inputControl(1, 4);
        CVector<Client> arr = readFromFile(fin);
        if (action == 1) {
            for (Client cl : arr) {
                std::cout << cl.toString() << "\n";
            }
        }
        else if (action == 2) {
            addClient:
            std::cout << "[Enter name]: ";
            std::string name;
            std::cin >> name;
            std::cout << "[Enter address]: ";
            std::string address;
            std::cin >> address;
            std::cout << "[Enter date]: ";
            std::string date;
            std::cin >> date;
            Client temp;
            if (!temp.setName(name)) {
                std::cout << "[Invalid name, try again]: ";
                goto addClient;
            }
            if (!temp.setAddress(address)) {
                std::cout << "[Invalid address, try again]: ";
                goto addClient;
            }
            if (!temp.setDate(date)) {
                std::cout << "[Invalid date, try again]: ";
                goto addClient;
            }
            arr.push_back(temp);
            clearAndWriteToFile(fout, arr);
        }
        else if (action == 3) {
            std::cout << "[Enter client`s name and address to find and delete]: \n";
            std::cout << "[Enter name]: ";
            std::string name;
            std::cin >> name;
            std::cout << "[Enter address]: ";
            std::string address;
            std::cin >> address;
            Client temp(name, address, -1, "01.01.0001");
            deleteClient(temp, fin, fout);
        }
        else if (action == 4) {
            std::cout << "[Enter client`s name and address to find and edit]: \n";
            std::cout << "[Enter name]: ";
            std::string name;
            std::cin >> name;
            std::cout << "[Enter address]: ";
            std::string address;
            std::cin >> address;
            Client temp(name, address, -1, "01.01.0001");
            editClient(temp, fin, fout);
        }
        filter(fin, fout);
    }
}