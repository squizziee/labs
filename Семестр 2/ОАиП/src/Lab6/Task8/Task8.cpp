#include <iostream>
#include <vector>

bool rec(std::vector<char> input, std::vector<char> toCreate, int pos, int i, int flag);
bool checkPrev(std::vector<char> input, std::vector<char> toCreate, int current, int pointer) {
	return rec(input, toCreate, current - 1, ++pointer, 0);
}

bool checkNext(std::vector<char> input, std::vector<char> toCreate, int current, int pointer) {
	return rec(input, toCreate, current + 1, ++pointer, 1);
}

bool done(std::vector<char> toCreate, int pointer) {
	return pointer == toCreate.size();
}

bool rec(std::vector<char> input, std::vector<char> toCreate, int current, int pointer, int flag)
{
	if (!(pointer - toCreate.size())) {
		return true;
	}
	bool check = 0;
	if (current < input.size() - 1 && input[current + 1] == toCreate[pointer] && flag)
		check = checkNext(input, toCreate, current, pointer);
	if (current > 0 && input[current - 1] == toCreate[pointer] && !check)
		check = checkPrev(input, toCreate, current, pointer);
	return check;
}

bool isPossible (std::string input, std::string toCreate)
{
	bool check = 0;
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
	while (occurence != std::string::npos)
	{
		if (check) {
			break;
		}
		check = rec(inputElements, toCreateElements, occurence, 1, 1);
		occurence = input.find(toCreate[0], ++iterator);
	}
	return check;
}

int main()
{
	int cases;
	std::string input;
	std::string toCreate;
	std::cin >> cases;
	std::vector<bool> results;
	while (cases--) {
		std::cin >> input >> toCreate;
		results.push_back(isPossible(input, toCreate));
	}
	for (bool flag : results) {
		std::cout << ( flag ? "YES" : "NO" ) << "\n";
	}
}