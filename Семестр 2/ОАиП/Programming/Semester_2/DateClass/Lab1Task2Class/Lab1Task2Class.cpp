#include <iostream>

#define ull unsigned long long

class Dish {
private:
	std::string name;
	std::string desc;
	int price = 0;
public:
	Dish() {}
	Dish(std::string name, std::string desc, int price) {
		this->name = name;
		this->desc = desc;
		this->price = price;
	}

	std::string getName() {
		return name;
	}

	std::string getDesc() {
		return desc;
	}

	int getPrice() {
		return price;
	}
};

class Order {
private:
	int orderID = 0;
	int orderTable = 0;
	Dish dish;
	int dishQuantity = 0;
	ull hash(std::string str) {
		ull result = 0;
		for (char c : str) {
			result += c;
		}
		result << 1;
		return result;
	}
public:
	Order() {}
	Order(int orderTable, Dish dish, int dishQuantity) {
		this->orderTable = orderTable;
		this->dish = dish;
		this->dishQuantity = dishQuantity;
		this->orderID = hash(dish.getName()) + ~(orderTable >> 1);
	}
};