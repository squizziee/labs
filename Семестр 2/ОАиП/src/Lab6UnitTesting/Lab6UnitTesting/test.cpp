#include "pch.h"
#include <map>

unsigned long long binpow(unsigned long long a, unsigned long long n, unsigned long long m)
{
	if (n == 0) {
		return 1;
	}
	else if (n % 2 == 1) {
		return (binpow(a, n - 1, m) * a) % m;
	}
	else {
		return binpow((a * a) % m, n / 2, m) % m;
	}
}

long long runTask5(long long L, long long m, std::string s1, std::string s2) {
	long long midStringLength = L - (s1.size() + s2.size());
	bool sameStrings = (s1 == s2);
	long long ans = 0;
	if (midStringLength > 0) {
		if (sameStrings) {
			return binpow(26, midStringLength, m);
		}
		else {
			return 2 * binpow(26, midStringLength, m) % m;
		}
	}
	else if (midStringLength == 0) {
		if (sameStrings) {
			return 1;
		}
		else {
			return 2;
		}
	}
	else {
		std::string temp1 = s1.substr(s1.size() - (long long)fabsl(midStringLength));
		std::string temp2 = s2.substr(0, (long long)fabsl(midStringLength));

		//std::string temp3 = s2.substr(s2.size() - (long long)fabsl(midStringLength) + 1);
		//std::string temp4 = s1.substr(0, (long long)fabsl(midStringLength) - 1);
		if (temp1 == temp2) {
			return 1;
		}
		/*else if (temp1 == temp2) {
			return 1;
		}*/
		else {
			return 0;
		}
	}
	return 0;
}

int traverse(std::vector<char> input, std::vector<char> toCreate, int pos, int i, int flag);
bool checkPrev(std::vector<char> input, std::vector<char> toCreate, int current, int pointer) {
	int temp = traverse(input, toCreate, current - 1, ++pointer, 0);
	return temp;
}

bool checkNext(std::vector<char> input, std::vector<char> toCreate, int current, int pointer) {
	int temp = traverse(input, toCreate, current + 1, ++pointer, 1);
	return temp;
}

int traverse(std::vector<char> input, std::vector<char> toCreate, int current, int pointer, int flag) {
	int check = 0;
	if (!(pointer - toCreate.size())) {
		return true;
	}
	if (current < input.size() - 1 && input[current + 1] == toCreate[pointer] && flag) {
		check = checkNext(input, toCreate, current, pointer);
	}
	if (current > 0 && input[current - 1] == toCreate[pointer] && !check) {
		check = checkPrev(input, toCreate, current, pointer);
	}
	return check;
}

int runTask8(std::string input, std::string toCreate) {
	int check = 0;
	int iterator = 0;
	std::vector<char> inputElements;
	std::vector<char> toCreateElements;
	for (char c : input) {
		inputElements.push_back(c);
	}
	for (char c : toCreate) {
		toCreateElements.push_back(c);
	}
	int occurence = input.find(toCreate[0], iterator);
	while (occurence != std::string::npos) {
		if (check) {
			break;
		}
		check = traverse(inputElements, toCreateElements, occurence, 1, 1);
		occurence = input.find(toCreate[0], ++iterator);
	}
	return check;
}

long long factorial(long long n) {
	long long ans = 1;
	for (long long i = 1; i <= n; i++) {
		ans *= i;
	}
	return ans;
}

int runTask6(std::string str) {
	std::map<char, long long> counts;
	for (char c : str) {
		if (counts.find(c) == counts.end()) {
			counts.insert({ c, 1 });
		}
		else {
			long long count = counts.at(c);
			counts.at(c) = count + 1;
		}
	}
	long long tempDivident = 0;
	long long tempDivisor = 1;
	for (std::pair<char, long long> pair : counts) {
		tempDivident += pair.second;
		tempDivisor *= factorial(pair.second);
	}
	long long divident = factorial(tempDivident);
	long long divisor = tempDivisor;
	return divident / divisor;
}

long long runTask7(std::string str) {
	std::set<char> symbols;
	for (char c : str) {
		symbols.insert(c);
	}
	if (symbols.size() <= 1) {
		return -1;
	}
	int strsize = str.size();
	return (str[0] == str[strsize - 1]) ? strsize - 1 : strsize;
}

TEST(Task5Testing, Task5Test1) {
	int ans = runTask5(7, 15, "codec", "decup");
	EXPECT_EQ(ans, 1);
}

TEST(Task5Testing, Task5Test2) {
	int ans = runTask5(14, 1000, "cup", "russia");
	EXPECT_EQ(ans, 752);
}

TEST(Task5Testing, Task5Test3) {
	int ans = runTask5(7, 123, "russian", "codecup");
	EXPECT_EQ(ans, 0);
}

TEST(Task6Testing, Task6Test1) {
	int ans = runTask6("SOLO");
	EXPECT_EQ(ans, 12);
}

TEST(Task6Testing, Task6Test2) {
	int ans = runTask6("AAAA");
	EXPECT_EQ(ans, 1);
}

TEST(Task6Testing, Task6Test3) {
	int ans = runTask6("AMOGUS");
	EXPECT_EQ(ans, 720);
}

TEST(Task7Testing, Task7Test1) {
	int ans = runTask7("aboba");
	EXPECT_EQ(ans, 4);
}

TEST(Task7Testing, Task7Test2) {
	int ans = runTask7("aaaa");
	EXPECT_EQ(ans, -1);
}

TEST(Task7Testing, Task7Test3) {
	int ans = runTask7("bitches");
	EXPECT_EQ(ans, 7);
}

TEST(Task8Testing, Task8Test1) {
	int ans = runTask8("abcdef", "cdedcb");
	EXPECT_EQ(ans, true);
}

TEST(Task8Testing, Task8Test2) {
	int ans = runTask8("ab", "b");
	EXPECT_EQ(ans, true);
}

TEST(Task8Testing, Task8Test3) {
	int ans = runTask8("ba", "baa");
	EXPECT_EQ(ans, false);
}