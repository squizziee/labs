#include <iostream>
#include <vector>
#include <cmath>

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

long long run(long long L, long long m, std::string s1, std::string s2) {
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

int main() {
	int cases;
	std::cin >> cases;
	std::vector<long long> results;
	while (cases-- > 0) {
		long long L, m;
		std::string s1, s2;
		std::cin >> L >> m >> s1 >> s2;
		results.push_back(run(L, m, s1, s2));
	}
	for (long long ans : results) {
		std::cout << ans << "\n";
	}
	return 0;
}