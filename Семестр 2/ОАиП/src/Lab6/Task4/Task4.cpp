#include <iostream>
#include <regex>

bool isInBounds(std::string text, int index) {
	return index >= 0 && index < text.size();
}

bool isUpperCase(char c) {
	if (c <= 90) {
		return true;
	}
	return false;
}

char changeCase(char c) {
	if (c <= 90) {
		return c + 32;
	}
	return c - 32;
}

std::string convert(std::string input) {
	std::string text;
	for (char c : input) {
		text.push_back(c);
	}
	bool isReady = false;
	while (!isReady) {
		bool wasChanged = false;
		for (int i = 0; i < text.size(); i++) {
			/*if (text[i] == 'C' || text[i] == 'Q' || text[i] == 'W' || text[i] == 'X') {
				text.replace(i, 1, "");
				wasChanged = true;
			}*/
			if ((text[i] == text[i + 1] || changeCase(text[i]) == text[i + 1]) && isInBounds(text, i + 1) &&
				text[i] != 'a' &&
				text[i] != 'e' &&
				text[i] != 'i' &&
				text[i] != 'o' &&
				text[i] != 'u' &&
				text[i] != 'y' &&
				text[i] != 'A' &&
				text[i] != 'E' &&
				text[i] != 'I' &&
				text[i] != 'O' &&
				text[i] != 'U' &&
				text[i] != 'Y') {
				int count = 0;
				for (int j = i; text[i] == text[j] || changeCase(text[i]) == text[j]; j++) {
					count++;
				}
				std::string strLiteral(1, text[i]);
				text.replace(i, count, strLiteral);
				wasChanged = true;
			}
			if ((text[i] == 'C' || text[i] == 'c') &&
				((text[i + 1] == 'e' || text[i + 1] == 'E' || text[i + 1] == 'i' || text[i + 1] == 'I' || text[i + 1] == 'y' || text[i + 1] == 'Y') && text[i + 1] != ' ') &&
				isInBounds(text, i + 1)) {
				if (isUpperCase(text[i])) {
					text[i] = 'S';
				}
				else {
					text[i] = 's';
				}
				wasChanged = true;
			}
			if ((text[i] == 'C' || text[i] == 'c') && 
				!(text[i + 1] == 'e' || text[i + 1] == 'E' || text[i + 1] == 'i' || text[i + 1] == 'I' || text[i + 1] == 'y' || text[i + 1] == 'Y') &&
				isInBounds(text, i + 1)) {
				if (isUpperCase(text[i])) {
					text[i] = 'K';
				}
				else {
					text[i] = 'k';
				}
				wasChanged = true;
			}
			if ((text[i] == 'q' || text[i] == 'Q') && (text[i + 1] == 'u' || text[i + 1] == 'U') && isInBounds(text, i + 1)) {
				if (isUpperCase(text[i])) {
					text[i] = 'K';
				}
				else {
					text[i] = 'k';
				}
				if (isUpperCase(text[i + 1])) {
					text[i + 1] = 'V';
				}
				else {
					text[i + 1] = 'v';
				}
				text[i + 1] = 'v';
				wasChanged = true;
			}
			if (text[i] == 'q' || text[i] == 'Q') {
				if (isUpperCase(text[i])) {
					text[i] = 'K';
				}
				else {
					text[i] = 'k';
				}
				wasChanged = true;
			}
			if (text[i] == 'x' || text[i] == 'X') {
				if (isUpperCase(text[i])) {
					text.replace(i, 1, "Ks");
				}
				else {
					text.replace(i, 1, "ks");
				}
				wasChanged = true;
			}
			if (text[i] == 'w' || text[i] == 'W') {
				if (isUpperCase(text[i])) {
					text[i] = 'V';
				}
				else {
					text[i] = 'v';
				}
				wasChanged = true;
			}
			if ((text[i] == 'p' || text[i] == 'P') && (text[i + 1] == 'h' || text[i + 1] == 'H') && isInBounds(text, i + 1)) {
				if (isUpperCase(text[i])) {
					text.replace(i, 2, "F");
				}
				else {
					text.replace(i, 2, "f");
				}
				wasChanged = true;
			}
			if ((text[i] == 'y' || text[i] == 'Y') && (text[i + 1] == 'o' || text[i + 1] == 'O') && (text[i + 2] == 'u' || text[i + 2] == 'U') && isInBounds(text, i + 1) && isInBounds(text, i + 2)) {
				if (isUpperCase(text[i])) {
					text.replace(i, 3, "U");
				}
				else {
					text.replace(i, 3, "u");
				}
				wasChanged = true;
			}
			if ((text[i] == 'o' || text[i] == 'O') && (text[i + 1] == 'o' || text[i] == 'O') && isInBounds(text, i + 1)) {
				if (isUpperCase(text[i])) {
					text.replace(i, 2, "U");
				}
				else {
					text.replace(i, 2, "u");
				}
				wasChanged = true;
			}
			if ((text[i] == 'e' || text[i] == 'E') && (text[i + 1] == 'e' || text[i + 1] == 'E') && isInBounds(text, i + 1)) {
				if (isUpperCase(text[i])) {
					text.replace(i, 2, "I");
				}
				else {
					text.replace(i, 2, "i");
				}
				wasChanged = true;
			}
			if ((text[i] == 't' || text[i] == 'T') && (text[i + 1] == 'h' || text[i + 1] == 'H') && isInBounds(text, i + 1)) {
				if (isUpperCase(text[i])) {
					text.replace(i, 2, "Z");
				}
				else {
					text.replace(i, 2, "z");
				}
				wasChanged = true;
			}
		}
		if (!wasChanged) {
			isReady = true;
		}
	}
	return text;
}

int main() {
	std::string str;
	getline(std::cin, str);
	str = convert(str);
	std::cout << str;
	//std::regex reg2("ce");
	//str = replace(reg2, str, "se");


	//std::cout << str;
}