#include <iostream>
#include <vector>
#include <cmath>

long long run(int L, int m, std::string s1, std::string s2) {
	int midStringLength = L - (s1.size() + s2.size());
	bool concatPossible = false;
	long long ans;
	if (midStringLength < 0) {
		for (int inset = 1; inset < s1.size() - 1; inset++) {
			std::string concatOne = s1.substr(0, s1.size() - inset) + s2;
			std::string concatTwo = s2.substr(0, s2.size() - inset) + s1;
			if (concatOne.substr(0, s1.size()) == s1) {
				concatPossible = true;
				if (concatOne.substr(0, s1.size() - inset) ==
					concatOne.substr(concatOne.size() - s2.size() + inset, s2.size() - inset)) {
					ans = 2;
				}
				else {
					ans = 1;
				}
				return ans;
			}
			else if (concatTwo.substr(0, s2.size()) == s2) {
				concatPossible = true;
				if (concatTwo.substr(0, s2.size() - inset) ==
					concatTwo.substr(concatTwo.size() - s1.size() + inset, s1.size() - inset)) {
					ans = 2;
				}
				else {
					ans = 1;
				}
				return ans;
			}
		}
		if (!concatPossible) {
			ans = 0;
		}
	}
	else {
		long long combinations = powl(26, midStringLength);
		ans = 2 * combinations % m;
	}
	return ans;
}

int main() {
	int cases;
	std::cin >> cases;
	std::vector<long long> results;
	while (cases-- > 0) {
		int L, m;
		std::string s1, s2;
		std::cin >> L >> m >> s1 >> s2;
		results.push_back(run(L, m, s1, s2));
	}
	for (long long ans : results) {
		std::cout << ans << "\n";
	}
	return 0;
}