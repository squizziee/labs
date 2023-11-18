#include <iostream>
#include <sstream>
#include <vector>
#include <ctime>

class Date {
private:
    /*
    * Basic storage class for a month.
    * Contains quantity of days in a month (int days)
    * and number of month in a year (int number).
    * Two getters for those fields.
    */
    class Month {
    private:
        int number;
        int days;
    public:
        Month() {
            this->number = 1;
            this->days = 1;
        }

        Month(int number, int days) {
            this->number = number;
            this->days = days;
        }

        int getNumber() {
            return number;
        }

        int getDays() {
            return days;
        }
    };

    std::vector<Month> months;
    int day = 1;
    Month month;
    int year = 1970;
public:
    Date(std::string input) {
        std::stringstream stream(input);
        std::string segment;
        std::vector<std::string> result;
        while (std::getline(stream, segment, '.')) {
            result.push_back(segment);
        }
        try {
            int tempDay = std::stoi(result[0]);
            int tempMonth = std::stoi(result[1]);
            int tempYear = std::stoi(result[2]);
            if (checkLeap(tempYear)) {
                months = { Month(1, 31), Month(2, 29), Month(3, 31),
                           Month(4, 30), Month(5, 31), Month(6, 30),
                           Month(7, 31), Month(8, 31), Month(9, 30),
                           Month(10, 31), Month(11, 30), Month(12, 31)
                };
            }
            else {
                months = { Month(1, 31), Month(2, 28), Month(3, 31),
                           Month(4, 30), Month(5, 31), Month(6, 30),
                           Month(7, 31), Month(8, 31), Month(9, 30),
                           Month(10, 31), Month(11, 30), Month(12, 31),
                };
            }
            if (tempMonth > 12 || tempMonth < 1) {
                std::cout << "[Error]\n";
                exit(1);
            }
            if (tempDay < 1) {
                std::cout << "[Error]\n";
                exit(1);
            }
            if (tempDay > months[tempMonth - 1].getDays()) {
                std::cout << "[Error]\n";
                exit(1);
            }
            this->day = tempDay;
            this->month = Month(tempMonth, months[tempMonth - 1].getDays());
            this->year = tempYear;
        }
        catch (...) {
            std::cout << "[Error]\n";
            exit(1);
        }
    }

    int isLaterThan(Date date) {
        if (this->year > date.year) {
            return true;
        }
        else if (this->year < date.year) {
            return false;
        }
        else {
            if (this->month.getNumber() > date.month.getNumber()) {
                return true;
            }
            else if (this->month.getNumber() < date.month.getNumber()) {
                return false;
            }
            else {
                if (this->day > date.day) {
                    return true;
                }
                else if (this->day < date.day) {
                    return false;
                }
                else {
                    return -1;
                }
            }
        }
    }

    Date nextDay() {
        if (day < month.getDays()) {
            return Date(std::to_string(day + 1) + "." 
                      + std::to_string(month.getNumber()) + "." 
                      + std::to_string(year));
        }
        else {
            if (month.getNumber() == 12 && day == 31) {
                return Date(std::to_string(1) + "." 
                          + std::to_string(1) + "." 
                          + std::to_string(year + 1));
            }
            else {
                return Date(std::to_string(1) + "." 
                          + std::to_string(month.getNumber() + 1) + "." 
                          + std::to_string(year));
            }
        }
    }

    Date previousDay() {
        if (day > 1) {
            return Date(std::to_string(day - 1) + "." 
                      + std::to_string(month.getNumber()) + "." 
                      + std::to_string(year));
        }
        else {
            if (month.getNumber() == 1 && day == 1) {
                return Date(std::to_string(31) + "." 
                          + std::to_string(12) + "." 
                          + std::to_string(year - 1));
            }
            else {
                return Date(std::to_string(months[month.getNumber() - 2].getDays()) + "." 
                          + std::to_string(month.getNumber() - 1) + "." 
                          + std::to_string(year));
            }
        }
    }

    int duration(Date& destination) {
        Date temp1 = destination;
        Date temp2 = *this;
        int leapDays = 0;
        for (int i = temp2.year; i <= temp1.year; i++) {
            leapDays += checkLeap(i);
        }
        int part1 = (destination.year - this->year) * 365;
        temp1.year = temp2.year;
        int part2;
        if (temp1.isLaterThan(temp2)) {
            part2 = temp2.daysTill(temp1);
        }
        else {
            part2 = temp1.daysTill(temp2);
        }
        return abs(part1) + part2 + leapDays - checkLeap(temp1.year);
    }

    int daysTill(Date& destination) {
        Date temp(std::to_string(day) + "." + std::to_string(month.getNumber()) + "." + std::to_string(year));
        int count = 0;
        if (temp.isLaterThan(destination)) {
            return 0;
        }
        while (temp.toString() != destination.toString()) {
            count++;
            temp = temp.nextDay();
        }
        return count;
    }

    int daysBefore(Date& destination) {
        Date temp(std::to_string(day) + "." + std::to_string(month.getNumber()) + "." + std::to_string(year));
        int count = 0;
        if (!temp.isLaterThan(destination)) {
            return 0;
        }
        while (temp.toString() != destination.toString()) {
            count++;
            temp = temp.previousDay();
        }
        return count;
    }

    int weekNumber() {
        Date temp(std::to_string(day) + "." + std::to_string(month.getNumber()) + "." + std::to_string(year));
        Date start("01.01." + std::to_string(temp.year));
        int monthCodes[12] = { 5, 1, 1, 4, 6, 2, 4, 0, 3, 5, 1, 3 };
        int monthCodesLeap[12] = { 4, 0, 1, 4, 6, 2, 4, 0, 3, 5, 1, 3 };
        int yearIndex = (temp.year * 5 / 4) % 7;
        int dayIndex = temp.day % 5 + isLeap();
        int weekDay = (yearIndex + (isLeap() ? monthCodesLeap[temp.month.getNumber() - 1] : monthCodes[temp.month.getNumber() - 1]) + dayIndex) % 7 - 1;
        weekDay = (weekDay < 0) ? 6 : weekDay;
        int week = 1;
        int count = weekDay + 1;
        while (count < start.duration(temp)) {
            count += 7;
            week++;
        }
        return week;
    }

    static bool checkLeap(int lYear) {
        if (lYear == 0) {
            return false;
        }
        if (lYear % 4 == 0) {
            if (lYear % 100 == 0) {
                if (lYear % 400 == 0) {
                    return true;
                }
                return false;
            }
            return true;
        }
        return false;
    }

    bool isLeap() {
        return checkLeap(this->year);
    }

    std::string toString() {
        return std::to_string(day) + "." + std::to_string(month.getNumber()) + "." + std::to_string(year);
    }
};

const std::string currentDateTime() {
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%d.%m.%Y", &tstruct);

    return buf;
}

Date fromStdTime(std::string stdTime) {
    std::stringstream stream(stdTime);
    std::string segment;
    std::vector<std::string> result;
    while (std::getline(stream, segment, '-')) {
        result.push_back(segment);
    }
    std::string dayStr({result[2][0], result[2][1]});
    return Date(dayStr + "." + result[1] + "." + result[0]);
}

int main() {
    Date date("01.09.2016");
    Date temp("14.01.2023");
    std::cout << temp.weekNumber();
    //std::cout << date.duration(temp) << "\n";
    //std::cout << date.previousDay().toString();
    //std::cout << (std::string("01.09.2000") > std::string("30.08.2000"));
    //std::string now(currentDateTime());
    //std::cout << now << "\n";
    //std::cout << fromStdTime(now).toString() << "\n";
    return 0;
}