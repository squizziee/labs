#include <iostream>
#include <set>

int recursiveWordLength(std::string str, int left, int right) {
	if (left >= right) {
		return -1;
	}
	if (str[left] == str[right]) {
		int t1 = recursiveWordLength(str, left + 1, right);
		int t2 = recursiveWordLength(str, left, right - 1);
		return t1 > t2 ? t1 : t2;
	}
	else {
		return right - left + 1;
	}
}

int wordLengthToRight(std::string str, int left, int right) {
	if (str.size() > 10) {
		while (left < right) {
			if (str[left] == str[right]) {
				left += 1;
			}
			else {
				return right - left + 1;
			}
		}
		return -1;
	}
	else {
		return recursiveWordLength(str, left, right);
	}
}

int wordLengthToLeft(std::string str, int left, int right) {
	if (str.size() > 10) {
		while (left < right) {
			if (str[left] == str[right]) {
				right -= 1;
			}
			else {
				return left - right + 1;
			}
		}
		return -1;
	}
	else {
		return recursiveWordLength(str, left, right);
	}
}

int biggestNonPalindrome(std::string str) {
	size_t start = 0;
	size_t end = str.size() - 1;
	for (;;) {
		if (start >= end) {
			break;
		}
		if (str[start] == str[end]) {
			if (str[start + 1] != str[end]) {
				return end - start;
			}
			else if (str[start + 1] == str[end]) {
				end--;
				continue;
			}
			if (str[start] != str[end - 1]) {
				return end - start;
			}
			else if (str[start] == str[end - 1]) {
				start++;
				continue;
			}
		}
		else {
			return end + 1;
		}
	}
	return -1;
}

int __biggestNonPalindrome(std::string str) {
	std::set<char> symbols;
	for (char c : str) {
		symbols.insert(c);
	}
	if (symbols.size() <= 1) {
		return -1;
	}
	int strsize = str.size();
	int ans = 0;
	int anchor = 0;
	for (int i = 0; i < strsize; i++) {
		if (str[anchor] == str[strsize - i - 1]) {
			ans += 2;
			continue;
		}
		anchor++;
	}
	return (ans > strsize) ? strsize : strsize - 1;
}

int main()
{
	std::string str;
	std::cin >> str;
	std::cout << biggestNonPalindrome(str);
	return 0;
}