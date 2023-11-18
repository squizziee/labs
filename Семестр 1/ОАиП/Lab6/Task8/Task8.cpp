#include <iostream>
#include <vector>

bool possible(std::string input, std::string toCreate) {
	size_t occurence = input.find(toCreate[0], 0);
	size_t toLeft = 0;
	size_t toRight = toCreate.size();
	bool possible = false;
	while (occurence != std::string::npos) {
		int pointer = 0;
		//std::cout << occurence << " ";
		if (occurence == input.size() - 1) {
			for (int i = occurence; ; i--) {
				if (i < 0) {
					break;
				}
				//std::cout << input[i] << " ";
				if (pointer == toCreate.size() - 1) {
					return true;
				}
				if (input[i] == toCreate[pointer]) {
					pointer++;
					continue;
				}
				else {
					pointer = 0;
					break;
				}
			}
		}
		else {
			for (int i = occurence; ; i++) {
				/*if(i >= input.size() || pointer >= toCreate.size()) {
					break;
				}*/
				//std::cout << input[i] << " ";
				if (i >= input.size()) {
					break;
				}
				if (pointer == toCreate.size() - 1) {
					//std::cout << "here";
					return true;
				}
				if (input[i] == toCreate[pointer]) {
					//std::cout << pointer << " ";
					toLeft++;
					toRight--;
					pointer++;
					continue;
				}
				if (input[i] != toCreate[pointer]) {
					for (int j = occurence + toLeft - 2; j >= occurence + toLeft - toRight - 1; j--) {
						//std::cout << input[j] << " ";
						if (pointer == toCreate.size() - 1) {
							return true;
						}
						if (input[j] == toCreate[pointer]) {
							//std::cout << input[j] << " ";
							pointer++;
							continue;
						}
						else {
							pointer = 0;
							break;
						}
					}
				}
				pointer = 0;
			}
		}
		occurence = input.find(toCreate[0], occurence + 1);
	}
	return false;
}

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