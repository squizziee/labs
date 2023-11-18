#include <iostream>
#include "CVector.h"

struct Receipt {
private:
    std::string name = "";
    std::string date = "";
    bool isRepaired = false;
    bool isEmpty = false;
public:
    Receipt() {};
    ~Receipt() {
        name.erase();
        date.erase();
    };
    Receipt(std::string name, std::string date, bool isRepaired) {
        this->name = name;
        this->date = date;
        this->isRepaired = isRepaired;
    }

    bool operator<(Receipt& operand) {
        return this->isRepaired < operand.isRepaired;
    }

    bool operator==(Receipt& operand) {
        return this->toString() == operand.toString();
    }

    bool getState() {
        return isRepaired;
    }

    std::string getName() {
        return name;
    }

    std::string getDate() {
        return date;
    }

    std::string toString() {
        return "Name: " + name + ", received: " + date + (isRepaired ? ", repaired" : ", not repaired");
    }
};

void bubbleSort(CVector<Receipt> &arr) {
    bool isSorted = false;
    while (!isSorted) {
        for (int i = 0; i < arr.size() - 1; i++) {
            if (arr[i + 1] < arr[i]) {
                isSorted = false;
                Receipt temp = arr[i];
                arr[i] = arr[i + 1];
                arr[i + 1] = temp;
                continue;
            }
            isSorted = true;
        }
    }
}

void searchForState(CVector<Receipt> &arr, bool toFind) {
    int count = 0;
    for (int i = 0; i < arr.size(); i++) {
        if (arr[i].getState() == toFind) {
            std::cout << arr[i].toString() << "\n";
            count++;
        }
    }
    if (!count) {
        std::cout << "[No matches] \n";
    }
}

void searchForName(CVector<Receipt> &arr, std::string toFind) {
    int count = 0;
	for (int i = 0; i < arr.size(); i++) {
		if (arr[i].getName() == toFind) {
            std::cout << arr[i].toString() << "\n";
		}
        count++;
	}
    if (!count) {
        std::cout << "[No matches] \n";
    }
}

void searchForDate(CVector<Receipt> &arr, std::string toFind) {
    int count = 0;
    for (int i = 0; i < arr.size(); i++) {
        if (arr[i].getDate() == toFind) {
            std::cout << arr[i].toString() << "\n";
            count++;
        }
    }
    if (!count) {
        std::cout << "[No matches] \n";
    }
}

void printAll(CVector<Receipt> &arr) {
    for (int i = 0; i < arr.size(); i++) {
        std::cout << arr[i].toString() << "\n";
    }
}

void readToArr(CVector<Receipt> &arr) {
    bool a;
    std::string b, c;
    std::cin >> b >> c >> a;
    arr.push_back(Receipt(b, c, a));
}

CVector<Receipt> deleteFromArrByState(CVector<Receipt> &arr, bool toFind) {
    CVector<Receipt> temp;
    for (int i = 0; i < arr.size(); i++) {
        if (arr[i].getState() != toFind) {
            temp.push_back(Receipt(arr[i].getName(), arr[i].getDate(), arr[i].getState()));
        }
    }
    arr.~CVector();
    return temp;
}

CVector<Receipt> deleteFromArrByName(CVector<Receipt>& arr, std::string toFind) {
    CVector<Receipt> temp;
    for (int i = 0; i < arr.size(); i++) {
        if (arr[i].getName() != toFind) {
            temp.push_back(Receipt(arr[i].getName(), arr[i].getDate(), arr[i].getState()));
        }
    }
    arr.~CVector();
    return temp;
}

CVector<Receipt> deleteFromArrByDate(CVector<Receipt>& arr, std::string toFind) {
    CVector<Receipt> temp;
    for (int i = 0; i < arr.size(); i++) {
        if (arr[i].getDate() != toFind) {
            temp.push_back(Receipt(arr[i].getName(), arr[i].getDate(), arr[i].getState()));
        }
    }
    arr.~CVector();
    return temp;
}

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

int main()
{
    CVector<Receipt> arr;
    input:
    std::cout << "[Choose the type of input (1 - number of structures, 2 - until repaired item)]: ";
    int typeOfInput = inputControl(1, 2);
    if (typeOfInput == 1) {
        std::cout << "[Enter a number of structures you want to create]: ";
        int structureCount = inputControl(1, 100);
        while (structureCount--) {
            bool a;
            std::string b, c;
            std::cin >> b >> c;
            a = inputControl(0, 1);
            arr.push_back(Receipt(b, c, a));
        }
    }
    else if (typeOfInput == 2) {
        while (1) {
            bool a;
            std::string b, c;
            std::cin >> b >> c;
            a = inputControl(0, 1);
            arr.push_back(Receipt(b, c, a));
            if (a) {
                break;
            }
        }
    }
    else {
        std::cout << "[Invalid input, try again]: \n";
        goto input;
    }
    while (1) {
        std::cout << "[Choose an action (1 - print structures, 2 - structure input, 3 - search, 4 - deletion, 5 - program termination)]: ";
        int action = inputControl(1, 5);
        if (action == 1) {
            printAll(arr);
        }
        else if (action == 2) {
            goto input;
        }
        else if (action == 3) {
            std::cout << "[Choose the type of value to search by (1 - repairment state, 2 - name, 3 - date)]: ";
            int typeOfSearch;
            std::cin >> typeOfSearch;
            if (typeOfSearch == 1) {
                std::cout << "[Enter the state (1 - repaired, 0 - not repaired)]: ";
                bool temp = inputControl(0, 1);
                searchForState(arr, temp);
            }
            else if (typeOfSearch == 2) {
                std::cout << "[Enter the name]: ";
                std::string temp;
                std::cin >> temp;
                searchForName(arr, temp);
            }
            else if (typeOfSearch == 3) {
                std::cout << "[Enter the date]: ";
                std::string temp;
                std::cin >> temp;
                searchForDate(arr, temp);
            }
        }
        else if (action == 4) {
            std::cout << "[Choose the type of value for element deletion (1 - repairment state, 2 - name, 3 - date)]: ";
            deletion:
            int typeOfSearch = inputControl(1, 3);
            if (typeOfSearch == 1) {
                std::cout << "[Enter the state (1 - repaired, 0 - not repaired)]: ";
                bool temp = inputControl(0, 1);
                arr = deleteFromArrByState(arr, temp);
            }
            else if (typeOfSearch == 2) {
                std::cout << "[Enter the name]: ";
                std::string temp;
                std::cin >> temp;
                arr = deleteFromArrByName(arr, temp);
            }
            else if (typeOfSearch == 3) {
                std::cout << "[Enter the date]: ";
                std::string temp;
                std::cin >> temp;
                arr = deleteFromArrByDate(arr, temp);
            }
            else {
                std::cout << "[Invalid input, try again: ]";
                goto deletion;
            }
        }
        else if (action == 5) {
            std::cout << "[Terminating... ";
            if (arr.size() != 0) {
                arr.~CVector();
            }
            std::cout << "Done]\n";
            exit(0);
        }
        else {
            std::cout << "[Invalid input, try again]: \n";
        }
    }
}