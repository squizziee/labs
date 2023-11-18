#ifndef DISH_H
#define DISH_H

#include <iostream>

#define ull unsigned long long

class Dish {
private:
    std::string name;
    std::string desc;
    long long price = 0;
public:
    Dish() {}
    Dish(std::string name, std::string desc, long long price) {
        this->name = name;
        this->desc = desc;
        this->price = price;
    }

    void setName(std::string name) {
        this->name = name;
    }

    std::string getName() {
        return name;
    }

    void setDesc(std::string desc) {
        this->desc = desc;
    }

    std::string getDesc() {
        return desc;
    }

    void setPrice(long long price) {
        this->price = price;
    }

    long long getPrice() {
        return price;
    }

    std::string toString() {
        return name + "|" + desc + "|" + std::to_string(price);
    }

    bool operator==(const Dish& dish) {
        return dish.name == name && dish.price == price;
    }

    bool operator<(const Dish& dish) {
        return dish.price < price;
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
        result <<= 1;
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

    int getOrderID() {
        return orderID;
    }

    void setOrderTable(int orderTable) {
        this->orderTable = orderTable;
    }

    int getOrderTable() {
        return orderTable;
    }

    void setDish(Dish dish) {
        this->dish = dish;
    }

    Dish& getDish() {
        return dish;
    }

    void setDishQuantity(int dishQuantity) {
        this->dishQuantity = dishQuantity;
    }

    int getDishQuantity() {
        return dishQuantity;
    }

    std::string toString() {
        return std::to_string(orderTable) + "|" + dish.toString() + "|" + std::to_string(dishQuantity);
    }
};

#endif // DISH_H
