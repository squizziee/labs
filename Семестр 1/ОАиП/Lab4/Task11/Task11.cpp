#include <iostream>
#include <cstring>

bool isInBounds(int i, int j, int rows, int cols) {
	if ((i >= 0) && (i < rows) && (j >= 0) && (j < cols))
		return true;
	return false;
}

char getMineNum(int count) {
	switch (count) {
	case 0: return '.';
	case 1: return '1';
	case 2: return '2';
	case 3: return '3';
	case 4: return '4';
	case 5: return '5';
	case 6: return '6';
	case 7: return '7';
	case 8: return '8';
	}
	return 0;
}

void task11() {
	int n = 1, m;
	int size = sizeof(char*);
	char** arr = (char**)malloc(size);
	int rowPointer = 1;
	std::string firstLine;
	std::getline(std::cin, firstLine, '\n');
	int firstLineLength = firstLine.size();
	m = firstLineLength;
	char* temp = new char[firstLineLength + 1];
	strcpy_s(temp, sizeof temp, firstLine.c_str());
	arr[0] = (char*)malloc(m);
	for (int j = 0; j < m; j++) {
		arr[0][j] = temp[j];
	}
	do {
		std::string s;
		std::getline(std::cin, s, '\n');
		int lineLength = s.length();
		if (lineLength == 0) {
			break;
		}
		if (lineLength != firstLineLength) {
			std::cout << "Invalid input\n";
			return;
		}
		char* char_array = new char[lineLength + 1];
		strcpy_s(char_array, sizeof char_array, s.c_str());
		size += sizeof (char*);
		arr = (char**)realloc(arr, size);
		arr[rowPointer] = (char*)malloc(m);
		for (int j = 0; j < m; j++) {
			arr[rowPointer][j] = char_array[j];
		}
		rowPointer++;
		n++;
	} while (1);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			int count = 0;
			if (arr[i][j] == '.') {
				if (isInBounds(i - 1, j, n, m)) {
					if (arr[i - 1][j] == '*') {
						count++;
					}
				}
				if (isInBounds(i + 1, j, n, m)) {
					if (arr[i + 1][j] == '*') {
						count++;
					}
				}
				if (isInBounds(i - 1, j + 1, n, m)) {
					if (arr[i - 1][j + 1] == '*') {
						count++;
					}
				}
				if (isInBounds(i + 1, j + 1, n, m)) {
					if (arr[i + 1][j + 1] == '*') {
						count++;
					}
				}
				if (isInBounds(i - 1, j - 1, n, m)) {
					if (arr[i - 1][j - 1] == '*') {
						count++;
					}
				}
				if (isInBounds(i, j + 1, n, m)) {
					if (arr[i][j + 1] == '*') {
						count++;
					}
				}
				if (isInBounds(i, j - 1, n, m)) {
					if (arr[i][j - 1] == '*') {
						count++;
					}
				}
				if (isInBounds(i + 1, j - 1, n, m)) {
					if (arr[i + 1][j - 1] == '*') {
						count++;
					}
				}
				arr[i][j] = getMineNum(count);
			}
			else if (arr[i][j] == '*') {
				continue;
			}
			else {
				std::cout << "Invalid input";
				exit(69);
			}
		}
	}
	std::cout << "Output : \n";
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			printf("%7c", arr[i][j]);
		}
		std::cout << "\n";
	}
	for (int i = 0; i < n; i++) {
		free(arr[i]);
	}
	free(arr);
}

int main() {
	task11();
	return 0;
}