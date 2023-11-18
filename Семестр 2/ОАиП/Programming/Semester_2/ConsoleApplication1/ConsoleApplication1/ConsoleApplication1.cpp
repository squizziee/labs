#include <iostream>
#include <string>
#include "LinkedList.h"

class Client {
private:
	int number;
	std::string name;
	std::string homeAddress;
	std::string date;
public:
	explicit Client()
		: number(0), name(""), homeAddress(""), date("") {}
	explicit Client(int number, std::string name, std::string homeAddress, std::string date) 
		: number(number), name(name), homeAddress(homeAddress), date(date) {}

	bool operator==(const Client& cl) const {
		return this->name == cl.name && this->homeAddress == cl.homeAddress;
	}

	std::string getName() {
		return name;
	}

	friend bool contains(LinkedList<Client>& list, Client& toFind);

	std::string toString() {
		std::string temp;
		temp.append(std::to_string(number));
		temp.append(" ");
		temp.append(name);
		temp.append(" ");
		temp.append(homeAddress);
		temp.append(" ");
		temp.append(date);
		return temp;
	}
};

bool contains(LinkedList<Client>& list, Client& toFind) {
	for (int i = 0; i < list.getSize(); i++) {
		//std::cout << list[i].toString() << "|";
		//std::cout << toFind.toString() << "\n";
		if (list[i].name == toFind.name && list[i].homeAddress == toFind.homeAddress) {
			std::cout << "found\n";
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

int main()
{
	LinkedList<Client> list;
	list.add(Client(1, "a", "a", "a"));
	list.add(Client(2, "b", "b", "b"));
	list.add(Client(2, "b", "b", "b"));
	list.add(Client(4, "d", "d", "d"));
	Client someone(1, "a", "a", "a");
	for (int i = 0; i < list.getSize(); i++) {
		//std::cout << list[i].toString();
	}
	removeDuplicates(list);
	for (int i = 0; i < list.getSize(); i++) {
		std::cout << list[i].getName() << "\n";
	}
	//list.remove(2);
	//std::cout << contains(list, someone);
	list.~LinkedList();
	return 0;
}