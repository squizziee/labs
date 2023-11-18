#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

int main() {
	std::ifstream aIn;
	std::ifstream bIn;
	aIn.open("a.txt", std::fstream::in);
	bIn.open("b.txt", std::fstream::in);
	int mCount1 = 4;
	int mCount2 = 4;
	std::vector<std::string> fileContent1;
	std::vector<std::string> fileContent2;
	std::string temp;
	while (getline(aIn, temp)) {
		fileContent1.push_back(temp);
	}
	while (getline(bIn, temp)) {
		fileContent2.push_back(temp);
	}
	aIn.close();
	bIn.close();
	remove("a.txt");
	remove("b.txt");
	for (int i = 1; i < mCount1 && i < mCount2; i++) {
		if ((i + 1) % 2 == 0) {
			std::string mtrx = fileContent1[i];
			fileContent1[i] = fileContent2[i - 1];
			fileContent2[i - 1] = mtrx;
		}
	}
	std::ofstream aOut ("a.txt");
	std::ofstream bOut ("b.txt");
	for (std::string mtrx : fileContent1) {
		aOut << mtrx << "\n";
	}
	for (std::string mtrx : fileContent2) {
		bOut << mtrx << "\n";
	}
	aOut.close();
	bOut.close();
}