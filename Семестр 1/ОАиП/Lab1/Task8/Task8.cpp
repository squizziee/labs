#include <iostream>
using namespace std;

void printHours(int mins);

void task8()
{
	int h1, min1, h2, min2;
	cin >> h1 >> min1 >> h2 >> min2;
	if (h1 >= 24 || h2 >= 24 || min1 >= 60 || min2 >= 60)
		cout << "dude\n";
	else {
		int totalMins = (h2 - h1) * 60 + (min2 - min1);
		if (totalMins < 0)
			totalMins = 1440 + totalMins;
		printHours(totalMins);
	}
}

void printHours(int mins) {
	if (mins >= 60) {
		int hours = mins / 60;
		int minutes = mins % (hours * 60);
		printf("%d hours %d minutes", hours, minutes);
	}
	else {
		printf("%d hours %d minutes", 0, mins);
	}
}

int main() {
	task8();
	return 0;
}