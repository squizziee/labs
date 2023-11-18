#include <iostream>

int ternaryStrToInt(std::string num) {
    reverse(num.begin(), num.end());
    int digit = 0;
    for (int i = 0; i < num.length(); i++)
        digit += (num[i] - '0') * (int)pow(3, i);
    return digit;
}

std::string convertToTernary(int n) {
    std::string ternary = "";
    while (n) {
        ternary = (char)((n % 3) + 48) + ternary; // 48 = 0
        n /= 3;
    }
    while (ternary.length() != 5)
        ternary = '0' + ternary;
    return ternary;
}

int input() {
    int x;
    while (true) {
        std::cin >> x;
        while (std::cin.peek() == ' ')
            std::cin.ignore(1, ' ');
        if (std::cin.fail() || std::cin.peek() != '\n' || !(x >= 1 && x <= 240)) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Invalid number, try again ";
        }
        else {
            return x;
        }
    }
}

int func(int N, int ALIVE) {
    std::cout << "Алгоритм: \n";
    std::cout << "Переводим номер каждой бочки в троичную систему счисления\n";
    std::cout << "Даём каждому рабу число в троичке:\n";
    std::cout << "Если 0 - раб умер в 1 день\n";
    std::cout << "Если 1 - раб умер во 2 день\n";
    std::cout << "Если 2 - раб выжил\n";
    std::cout << "Если посмотреть на номер отравленной бочки в троичной\n";
    std::cout << "системе счисления, то видно состояние каждого из 5 рабов: \n";
    std::cout << "0 - умер в первый день, 1 - умер во второй день, 2 - выжил \n";
    std::string poison = convertToTernary(N);
    std::string* barells = new std::string[240];
    for (int i = 0; i < 240; i++)
        barells[i] = convertToTernary(i + 1);
    int Slave[5] = { 1,1,1,1,1 };
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 240; j++)
            if (barells[j][i] == '0' && barells[j] == poison)
                Slave[i] = 0;
    }
    std::cout << "\nПервый день:";
    int alive = 0;
    for (int i = 0; i < 5; i++)
        if (Slave[i])
            alive++;
        else
            std::cout << "\nРаб #" << i + 1 << " умер";
    std::cout << "\n";

    std::string* afterDayOne = new std::string[240];
    int afterD1 = 0;
    if (alive == 5) {
        for (int b = 0; b < 240; b++) {
            bool add = true;
            for (int i = 0; i < 5; i++)
                if (barells[b][i] == '0')
                    add = false;
            if (add)
                afterDayOne[afterD1++] = barells[b];
        }
    }
    else {
        for (int j = 0; j < 240; j++) {
            bool add = true;
            for (int i = 0; i < 5; i++) {
                if (Slave[i] == 0 && barells[j][i] != '0')
                    add = false;
            }
            if (add)
                afterDayOne[afterD1++] = barells[j];
        }
    }
    std::cout << "Потенциально отравленные бочки: \n";
    for (int i = 0; i < afterD1; i++) {
        std::cout << afterDayOne[i] << "(" << ternaryStrToInt(afterDayOne[i]) << "), ";
    }
    std::cout << "\n\n";
    int tempSlave[5];
    for (int i = 0; i < 5; i++)
        tempSlave[i] = Slave[i];
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < afterD1; j++)
            if (tempSlave[i] && afterDayOne[j][i] == '1' && afterDayOne[j] == poison) {
                tempSlave[i] = 0;
            }
    }
    std::cout << "\nВторой день:";
    for (int i = 0; i < 5; i++)
        if (tempSlave[i] == 0 && Slave[i] == 1)
            std::cout << "\nРаб #" << i + 1 << " умер";
    std::cout << "\n\n";

    std::string* afterDayTwo = new std::string[240];
    int afterD2 = 0;
    for (int i = 0; i < afterD1; i++) {
        bool add = true;
        for (int j = 0; j < 5; j++) {
            if (Slave[j] == 1 && tempSlave[j] == 0 && afterDayOne[i][j] != '1')
                add = false;
        }
        if (add)
            afterDayTwo[afterD2++] = afterDayOne[i];
    }
    ALIVE = 0;
    for (int i = 0; i < 5; i++) {
        if (tempSlave[i]) {
            ALIVE++;
            for (int b = 0; b < afterD2; b++)
                afterDayTwo[b][i] = '2';
        }
    }
    int ans = ternaryStrToInt(afterDayTwo[0]);
    return ans;
}

int main() {
    setlocale(0, "");
    std::cout << "Введите номер отравленной бочки: ";
    int N = input();
    int ans = func(N, 0);
    std::cout << "Отравленная бочка: " << convertToTernary(ans) << "(";
    std::cout << ans << ")";
    return 0;
}

/*#include <iostream>
#include <vector>
#include <set>
#include <functional>

struct Range {
    int start; 
    int end;
    Range(int start, int end) {
        this->start = start;
        this->end = end;
    }

    size_t operator()(const Range& rng) const {
        return std::hash<int>{}(rng.start) ^ std::hash<int>{}(rng.end);
    }

    size_t operator<(const Range& rng) const {
        return this->start < rng.start && this->end < rng.end;
    }

};

inline bool operator==(const Range& r1, const Range& r2) {
    return (r1.start == r2.start) && (r1.end == r2.end);
}

struct Slave {
    bool dead = false;
    std::vector<Range> ranges;
    void drink(std::vector<int> barrels, Range range) {
        ranges.push_back(range);
        //std::std::cout << range.start << " ";
        int a = range.start, b = range.end;
        for (int i = range.start; i < range.end; i++) {
            if (barrels[i]) {
                this->dead = true;
            }
        }
    }
};

int main()
{
    Slave s1, s2, s3, s4, s5;
    std::vector<int> barrels(240, 0);
    barrels[0] = 1;

    Range row1_1(0, 15);
    Range row1_2(15, 30);
    Range row1_3(30, 45);
    Range row1_4(45, 60);

    Range row2_1(60, 75);
    Range row2_2(75, 90);
    Range row2_3(90, 105);
    Range row2_4(105, 120);

    Range row3_1(120, 135);
    Range row3_2(135, 150);
    Range row3_3(150, 165);
    Range row3_4(165, 180);

    Range row4_1(180, 195);
    Range row4_2(195, 210);
    Range row4_3(210, 225);
    Range row4_4(225, 240);

    // 1
    s1.drink(barrels, row1_1);
    s1.drink(barrels, row1_2);
    s1.drink(barrels, row1_3);
    s1.drink(barrels, row1_4);

    s1.drink(barrels, row2_1);
    s1.drink(barrels, row3_1);
    s1.drink(barrels, row4_1);

    // 2
    s2.drink(barrels, row2_1);
    s2.drink(barrels, row2_2);
    s2.drink(barrels, row2_3);
    s2.drink(barrels, row2_4);

    s2.drink(barrels, row1_2);
    s2.drink(barrels, row3_2);
    s2.drink(barrels, row4_2);

    // 3
    s3.drink(barrels, row3_1);
    s3.drink(barrels, row3_2);
    s3.drink(barrels, row3_3);
    s3.drink(barrels, row3_4);

    s3.drink(barrels, row1_3);
    s3.drink(barrels, row2_3);
    s3.drink(barrels, row4_3);

    // 4
    s4.drink(barrels, row4_1);
    s4.drink(barrels, row4_2);
    s4.drink(barrels, row4_3);
    s4.drink(barrels, row4_4);

    s4.drink(barrels, row1_4);
    s4.drink(barrels, row2_4);
    s4.drink(barrels, row3_4);

    std::set<Range> temp1;
    int deadSlaves = 0;
    if (s1.dead) deadSlaves++;
    if (s2.dead) deadSlaves++;
    if (s3.dead) deadSlaves++;
    if (s4.dead) deadSlaves++;

    if (deadSlaves == 1) {
        Slave areaSlave;
        if (s1.dead) areaSlave = s1;
        if (s2.dead) areaSlave = s2;
        if (s3.dead) areaSlave = s3;
        if (s4.dead) areaSlave = s4;
        for (Range range : areaSlave.ranges) {
            temp1.insert(range);
        }
        for (Range r : temp1) {
            std::std::cout << r.start << " " << r.end << "\n";
        }
    }

    //if (s1.dead)
    //std::std::cout << deadSlaves;
}*/